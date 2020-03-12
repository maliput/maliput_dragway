# `maliput_dragway`

Maliput_dragway is an implementation of Maliput's API that allows users to instantiate
a multilane dragway.  All lanes in the dragway are straight, parallel, and in
the same segment. The ends of each lane are connected together via a "magical
loop" that results in vehicles traveling on the Dragway's lanes instantaneously
teleporting from one end of the lane to the opposite end of the lane.

The number of lanes and their lengths, widths, and shoulder widths are all user
specifiable.

## Build

1. Setup a development workspace as described [here](https://github.com/ToyotaResearchInstitute/dsim-repos-index/tree/master/README.md).

2. Bring up your development workspace:

```sh
cd path/to/my/workspace
source ./bringup
```

3. Build maliput_dragway package and its dependencies:

  - If not building drake from source:

   ```sh
   colcon build --packages-up-to maliput_dragway
   ```

  - If building drake from source:

   ```sh
   colcon build --cmake-args -DWITH_PYTHON_VERSION=3 --packages-up-to maliput_dragway
   ```