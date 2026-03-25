from __future__ import annotations
from dataclasses import dataclass
import numpy as np


@dataclass
class HeightmapSpec:
    size: int = 224
    resolution: float = 0.002  # meters per pixel
    # bounds for the 2 plane axes in the POINT FRAME (camera_frame or base_link), meters:
    plane_min: np.ndarray = np.array([-0.2, -0.2], dtype=np.float32)  # [u_min, v_min]
    plane_max: np.ndarray = np.array([ 0.2,  0.2], dtype=np.float32)  # [u_max, v_max]

    # mapping: which coordinates of XYZ are height axis and plane axes
    # default assumes points are already in a frame where:
    #   height axis = X, plane axes = (Y,Z) like in твоём симе
    height_axis: int = 0
    plane_axes: tuple[int, int] = (1, 2)


def depth_to_xyz(
    depth: np.ndarray,
    K: np.ndarray,
    frame_optical_to_link: Tuple[np.ndarray, np.ndarray] | None = None,
) -> np.ndarray:
    """
    Unproject depth image to 3D points in camera_link (or optical if frame_optical_to_link is None).

    Args:
        depth: (H, W) float32 in meters. Invalid (0, nan, inf) produce nan in xyz.
        K: 3x3 camera matrix; K[0,0]=fx, K[1,1]=fy, K[0,2]=cx, K[1,2]=cy.
        frame_optical_to_link: Optional (R, t) with R (3,3), t (3,); P_link = R @ P_optical + t.

    Returns:
        xyz: (H, W, 3) float32 in link frame (or optical if frame_optical_to_link is None).
    """
    H, W = depth.shape
    fx = float(K[0, 0])
    fy = float(K[1, 1])
    cx = float(K[0, 2])
    cy = float(K[1, 2])

    v = np.arange(H, dtype=np.float32)
    u = np.arange(W, dtype=np.float32)
    uu, vv = np.meshgrid(u, v)

    z = np.asarray(depth, dtype=np.float32).copy()
    valid = np.isfinite(z) & (z > 0)
    z[~valid] = np.nan

    x_opt = (uu - cx) * z / fx
    y_opt = (vv - cy) * z / fy

    xyz_opt = np.stack([x_opt, y_opt, z], axis=-1)

    if frame_optical_to_link is None:
        return xyz_opt

    R, t = frame_optical_to_link
    R = np.asarray(R, dtype=np.float32)
    t = np.asarray(t, dtype=np.float32).ravel()[:3]
    # (H,W,3) @ (3,3).T -> (H,W,3): for each point apply P_link = R @ P_opt + t
    xyz_link = np.einsum("...j,ji->...i", xyz_opt, R.T) + t
    return xyz_link


def build_heightmaps(
    rgb_u8: np.ndarray,               # (H,W,3) uint8
    xyz: np.ndarray,                  # (H,W,3) float32
    spec: HeightmapSpec,
    mask_u8: np.ndarray | None = None # (H,W) uint8, 0 background, >0 object
) -> tuple[np.ndarray, np.ndarray, np.ndarray]:
    """
    Принимает на вход:
        rgb_u8 (H,W,3) uint8
        xyz (H,W,3) float32 из ф-ии depth_to_xyz
        spec — спецификации Heightmap
        mask_u8 из под Yolo — (H,W) uint8, 0 background, >0 object
    Returns:
      color_hm: (S,S,3) uint8
      height_hm: (S,S) float32
      mask_hm: (S,S) uint8
    """
    S = spec.size
    color_hm = np.zeros((S, S, 3), dtype=np.uint8)
    height_hm = np.zeros((S, S), dtype=np.float32)
    mask_hm = np.zeros((S, S), dtype=np.uint8)

    pts = xyz.reshape(-1, 3)
    rgb = rgb_u8.reshape(-1, 3)

    valid = np.isfinite(pts).all(axis=1) & (np.abs(pts).sum(axis=1) > 0)
    if mask_u8 is not None:
        m = mask_u8.reshape(-1)
    else:
        m = np.zeros(pts.shape[0], dtype=np.uint8)

    pts = pts[valid]
    rgb = rgb[valid]
    m = m[valid]

    if pts.shape[0] == 0:
        return color_hm, height_hm, mask_hm

    u_axis, v_axis = spec.plane_axes
    uv = pts[:, [u_axis, v_axis]]

    inb = (
        (uv[:, 0] >= spec.plane_min[0]) & (uv[:, 0] <= spec.plane_max[0]) &
        (uv[:, 1] >= spec.plane_min[1]) & (uv[:, 1] <= spec.plane_max[1])
    )
    pts = pts[inb]
    rgb = rgb[inb]
    m = m[inb]
    uv = uv[inb]

    if pts.shape[0] == 0:
        return color_hm, height_hm, mask_hm

    pix = np.floor((uv - spec.plane_min[None, :]) / spec.resolution).astype(np.int32)
    pix[:, 0] = np.clip(pix[:, 0], 0, S - 1)
    pix[:, 1] = np.clip(pix[:, 1], 0, S - 1)

    px = (S - 1) - pix[:, 0]
    py = (S - 1) - pix[:, 1]

    hvals = pts[:, spec.height_axis].astype(np.float32)
    linear_idx = py * S + px

    # В ячейке оставляем точку с максимальной высотой (верх объекта)
    sort_key = (linear_idx.astype(np.float64) * 1e6) + hvals
    sort_idx = np.argsort(sort_key)

    linear_idx = linear_idx[sort_idx]
    hvals = hvals[sort_idx]
    rgb = rgb[sort_idx]
    m = m[sort_idx]

    first_in_pixel = np.ones(linear_idx.shape[0], dtype=bool)
    first_in_pixel[1:] = (linear_idx[1:] != linear_idx[:-1])

    out_linear = linear_idx[first_in_pixel]
    out_rgb = rgb[first_in_pixel]
    out_depth = hvals[first_in_pixel]

    out_y = out_linear // S
    out_z = out_linear % S

    color_hm[out_y, out_z] = out_rgb
    height_hm[out_y, out_z] = out_depth
    if mask_u8 is not None:
        out_mask = m[first_in_pixel]
        mask_hm[out_y, out_z] = out_mask

    return color_hm, height_hm, mask_hm

