# Multi-Object Plan

## Goal
Support scenes with multiple visible objects while keeping the current grasp model and execution path.

## Current Pipeline
1. YOLO detects objects on RGB input.
2. The detected object masks are merged into one union mask.
3. The union mask is projected into `mask_hm`.
4. `model_forward.py` builds a `Q-map` and selects one global best grasp pixel.
5. That pixel is reconstructed into 3D and executed by the robot.

## Current Limitation
- YOLO can separate objects, but the pipeline merges them into one allowed region.
- Grasp selection is global over the whole combined scene.
- The system answers "where is the best grasp in the scene?" instead of "where is the best grasp on the chosen object?"

## MVP Approach
1. Keep instance-level YOLO results instead of only a union mask.
2. Select one target object by a simple rule.
3. Build a mask only for that object.
4. Project only that selected-object mask into heightmap space.
5. Run the existing grasp model unchanged on the cleaned scene.

## Why This Approach First
- Minimal changes to the existing pipeline.
- No retraining required for the first iteration.
- Keeps the current single-object grasp model and motion logic.
- Easier to debug than multi-object grasp scoring per object.

## Code Entry Points

### YOLO / mask handling
- `src/grasp_inference_pkg/grasp_inference_pkg/grasp_node.py`
- Key method:
  - `_segment_union_mask(...)`

### Heightmap build and mask projection
- `src/grasp_inference_pkg/grasp_inference_pkg/grasp_node.py`
- Key methods:
  - `_on_pcd_mask_source(...)`
  - `_on_pcd(...)`
  - `_publish_heightmaps(...)`

### Grasp selection
- `src/grasp_inference_pkg/grasp_inference_pkg/model_forward.py`
- Key method:
  - `_on_heightmaps(...)`

## Likely MVP Implementation Shape
- Add a new "selected object" mask path in `grasp_node.py`.
- Keep union-mask behavior available as fallback.
- For initial testing, select the target object by a simple deterministic rule:
  - first valid non-background instance
  - or leftmost/rightmost instance
  - or highest-confidence instance of a chosen class

## Current MVP Status
- `grasp_node.py` now supports:
  - `seg_mask_mode = "union"` or `"selected"`
  - `seg_selection_rule = "highest_conf" | "leftmost" | "rightmost" | "first"`
  - `seg_target_class = "<class_name>"` for exact class filtering
- Active launch currently uses:
  - `seg_mask_mode = "selected"`
  - `seg_selection_rule = "highest_conf"`
  - `seg_target_class = ""`
- This means only one non-background YOLO instance is forwarded into the heightmap path.

## Current Test Set
- `water_bottle_plain`
- canned product candidate: corn can
- small juice carton / box-like product

## Immediate Test Goal
1. Put three products in one camera frame.
2. Confirm YOLO sees several instances on `~/debug/yolo_mask_on_image_raw`.
3. Confirm only one instance survives into `/heightmap_node/heightmap/mask`.
4. Confirm `q_canvas` and `object_center` are now computed on the cleaned single-object scene.
5. After that, switch selection from generic `highest_conf` to either:
   - a fixed `seg_target_class`
   - or a deterministic spatial rule like `leftmost/rightmost`


## Future Extensions
- Per-object grasp scoring instead of pre-selecting one object first.
- Selection by WMS/SKU metadata.
- Multi-view observation before grasp.
- Full scene fusion from several camera poses.
