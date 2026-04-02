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


## Future Extensions
- Per-object grasp scoring instead of pre-selecting one object first.
- Selection by WMS/SKU metadata.
- Multi-view observation before grasp.
- Full scene fusion from several camera poses.
