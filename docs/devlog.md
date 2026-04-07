# Dev Log

## 2026-04-02

### Context
- Project: `grasp_dev_env_v2`
- Active runtime:
  - `scripts/launch_grasp.sh`
  - `src/grasp_inference_pkg/launch/grasp_inference_jaka.launch.py`
  - `src/grasp_inference_pkg/grasp_inference_pkg/gripper_exec_jaka.py`
- Current stable grasp setup:
  - `apply_model_to_camera_rotation = False`
  - grasp path uses `IK + joint_move`
  - `hm_resolution = 0.001`
  - `plane_min = [-0.186, -0.085]`
  - `plane_max = [0.038, 0.139]`

### Confirmed Findings
- The main early failure was not bad grasp-pixel choice, but bad `pixel -> 3D` reconstruction in `model_forward.py`.
- `q_canvas` selected a correct pixel on the object before the 3D reconstruction fix.
- Disabling `model_to_camera_rotation` was a major fix.
- Wide workspace experiments with `plane span = 0.448` degraded `q_canvas` and grasp quality before robot motion.
- Current pipeline grasps reliably, but only in a narrow effective workspace.

### Current Branch of Work
- Focus: multi-object selection without retraining.
- Agreed MVP direction:
  1. YOLO detects multiple objects.
  2. We choose one required object.
  3. We keep only that object's mask.
  4. Everything else is masked out.
  5. Current grasp model runs on the cleaned single-object scene.

### Code Areas of Interest
- YOLO and mask generation:
  - `src/grasp_inference_pkg/grasp_inference_pkg/grasp_node.py`
- Grasp inference and 3D reconstruction:
  - `src/grasp_inference_pkg/grasp_inference_pkg/model_forward.py`

### Notes for Next Steps
- Preserve the current single-object working path as fallback.
- Avoid changing motion/execution while building the multi-object MVP.
- First implementation target is the union-mask path in `grasp_node.py`.
## 2026-04-03
Goal:
- start the YOLO multi-object MVP without touching the current grasp model

Decision:
- use the simplest path first:
  - YOLO detects several objects
  - choose one target instance
  - pass only that instance mask into the heightmap path
  - keep `model_forward.py` unchanged for now

Test objects:
- water bottle
- corn can
- small juice box

What changed:
- added single-object selection mode in `grasp_node.py`
- added launch parameters:
  - `seg_mask_mode`
  - `seg_selection_rule`
  - `seg_target_class`
- active launch now uses:
  - `seg_mask_mode = selected`
  - `seg_selection_rule = highest_conf`
  - `seg_target_class = ""`

Expected result:
- `~/debug/yolo_mask_on_image_raw` still shows the detected scene
- `/heightmap_node/heightmap/mask` should contain only one selected object
- `q_canvas` should be built from a cleaned single-object scene instead of a union mask
