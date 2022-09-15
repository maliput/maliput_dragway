^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package maliput_dragway
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

0.1.3 (2022-09-14)
------------------
* Matches with changes in Maliput: Lane::ToLanePosition. (`#76 <https://github.com/maliput/maliput_dragway/issues/76>`_)
* Adds triage workflow. (`#75 <https://github.com/maliput/maliput_dragway/issues/75>`_)
* Improves README. (`#74 <https://github.com/maliput/maliput_dragway/issues/74>`_)
* Contributors: Franco Cipollone

0.1.2 (2022-07-01)
------------------
* Fixes environment hooks. (`#73 <https://github.com/maliput/maliput_dragway/issues/73>`_)
* Contributors: Franco Cipollone

0.1.1 (2022-06-21)
------------------
* add missing dependency on python3-dev to get python.h (`#72 <https://github.com/maliput/maliput_dragway/issues/72>`_)
  * add missing dependency on python3-dev to get python.h
  * Compiles test utilities when BUILD_TESTING flag is on, to match gtest dependency.
  Co-authored-by: Franco Cipollone <franco.c@ekumenlabs.com>
* Contributors: Tully Foote

0.1.0 (2022-06-16)
------------------
* Updates package.xml
* Suppresses old-rule-api-related deprecation warnings. (`#71 <https://github.com/maliput/maliput_dragway/issues/71>`_)
* Uses doc_depend label. (`#70 <https://github.com/maliput/maliput_dragway/issues/70>`_)
* Fixes include folder installation. (`#69 <https://github.com/maliput/maliput_dragway/issues/69>`_)
* Depends on pybind11-dev package via rosdep. (`#68 <https://github.com/maliput/maliput_dragway/issues/68>`_)
* Uses ros-action-ci in build.yaml workflow. (`#67 <https://github.com/maliput/maliput_dragway/issues/67>`_)
* Updates license. (`#66 <https://github.com/maliput/maliput_dragway/issues/66>`_)
* Uses ament_export_targets. (`#65 <https://github.com/maliput/maliput_dragway/issues/65>`_)
* Removes dashing support. (`#64 <https://github.com/maliput/maliput_dragway/issues/64>`_)
* Passes the RoadGeometry to the IntersectionBook constructor. (`#63 <https://github.com/maliput/maliput_dragway/issues/63>`_)
* Adds BUILD_DOCS flag as opt-in flag (`#62 <https://github.com/maliput/maliput_dragway/issues/62>`_)
* Adds CI badges (`#61 <https://github.com/maliput/maliput_dragway/issues/61>`_)
* Replaces push by workflow_dispatch event in gcc build. (`#60 <https://github.com/maliput/maliput_dragway/issues/60>`_)
* Pairs with maliput::plugin::RoadNetworkLoader functor change. (`#59 <https://github.com/maliput/maliput_dragway/issues/59>`_)
* Fixes MALIPUT_PLUGIN_PATH new path. (`#58 <https://github.com/maliput/maliput_dragway/issues/58>`_)
* Improves use of maliput plugin architecture. (`#57 <https://github.com/maliput/maliput_dragway/issues/57>`_)
* Enable doxygen verification. (`#56 <https://github.com/maliput/maliput_dragway/issues/56>`_)
* Removes tests of the maliput::api bindings and simplifies the dragway tests (`#55 <https://github.com/maliput/maliput_dragway/issues/55>`_)
* Set up linker properly when using clang in CI. (`#54 <https://github.com/maliput/maliput_dragway/issues/54>`_)
* Remove references to GnuInstallDir vars. (`#53 <https://github.com/maliput/maliput_dragway/issues/53>`_)
* Enable foxy (`#51 <https://github.com/maliput/maliput_dragway/issues/51>`_)
* Fix include style part 2: reorder, fix newlines (`#50 <https://github.com/maliput/maliput_dragway/issues/50>`_)
* Fix include style part 1: use <> for maliput, pybind11 includes (`#49 <https://github.com/maliput/maliput_dragway/issues/49>`_)
* Use newer revision of pybind11 (`#47 <https://github.com/maliput/maliput_dragway/issues/47>`_)
* rosdep update --include-eol-distros (`#48 <https://github.com/maliput/maliput_dragway/issues/48>`_)
* Upgrade ros-tooling to v0.2.1 (`#46 <https://github.com/maliput/maliput_dragway/issues/46>`_)
* Uses maliput_documentation instead of maliput-documentation. (`#45 <https://github.com/maliput/maliput_dragway/issues/45>`_)
* Switches ament_cmake_doxygen to main. (`#44 <https://github.com/maliput/maliput_dragway/issues/44>`_)
* Optimizes scan-build run in CI. (`#43 <https://github.com/maliput/maliput_dragway/issues/43>`_)
* Add changelog template (`#42 <https://github.com/maliput/maliput_dragway/issues/42>`_)
* Makes CI to clone maliput_py repository. (`#41 <https://github.com/maliput/maliput_dragway/issues/41>`_)
* Points to maliput-documentation for workspace installation. (`#40 <https://github.com/maliput/maliput_dragway/issues/40>`_)
* Adds scan build workflow on specific label (`#38 <https://github.com/maliput/maliput_dragway/issues/38>`_)
* Trigger sanitizers workflow if label is added (`#37 <https://github.com/maliput/maliput_dragway/issues/37>`_)
* Fix clang build because an attribute was passed in before it was initialized. (`#36 <https://github.com/maliput/maliput_dragway/issues/36>`_)
* Implements inertial_to_backend_frame_translation (`#35 <https://github.com/maliput/maliput_dragway/issues/35>`_)
* Moves disabled workflows to a different folder. (`#34 <https://github.com/maliput/maliput_dragway/issues/34>`_)
* Refer to a specific clang version and use lld linker. (`#33 <https://github.com/maliput/maliput_dragway/issues/33>`_)
* Matches with plugin extern C methods refactor. (`#31 <https://github.com/maliput/maliput_dragway/issues/31>`_)
* Update ros-tooling version in CI. (`#32 <https://github.com/maliput/maliput_dragway/issues/32>`_)
* Fixes ubsan behavior in CI. (`#29 <https://github.com/maliput/maliput_dragway/issues/29>`_)
* Fixes plugin test failure when running ubsan. (`#30 <https://github.com/maliput/maliput_dragway/issues/30>`_)
* Removes Jenkins configuration. (`#27 <https://github.com/maliput/maliput_dragway/issues/27>`_)
* Append library dirs to plugin test. (`#26 <https://github.com/maliput/maliput_dragway/issues/26>`_)
* Adds tests for RoadNetworkLoader dragway plugin. (`#25 <https://github.com/maliput/maliput_dragway/issues/25>`_)
* Implements a maliput RoadNetworLoader plugin (`#24 <https://github.com/maliput/maliput_dragway/issues/24>`_)
* Changes occurences of GeoPosition to InertialPosition. (`#23 <https://github.com/maliput/maliput_dragway/issues/23>`_)
* Matches with maliput bindings migration. (`#22 <https://github.com/maliput/maliput_dragway/issues/22>`_)
* Don't pass self to ament_target_dependencies (`#20 <https://github.com/maliput/maliput_dragway/issues/20>`_)
* Unifies cmake install paths. (`#21 <https://github.com/maliput/maliput_dragway/issues/21>`_)
* Uses namespaces in cmake targets. (`#19 <https://github.com/maliput/maliput_dragway/issues/19>`_)
* Use maliput::test_utilities and try same branch name in actions (`#18 <https://github.com/maliput/maliput_dragway/issues/18>`_)
* Fixes Github Actions ROS tools installation (`#17 <https://github.com/maliput/maliput_dragway/issues/17>`_)
* Adds scan_build job to Github Actions. (`#16 <https://github.com/maliput/maliput_dragway/issues/16>`_)
* Adds clang8, asan, ubsan and tsan to Github Actions. (`#15 <https://github.com/maliput/maliput_dragway/issues/15>`_)
* Updates package.xml (`#13 <https://github.com/maliput/maliput_dragway/issues/13>`_)
* Adds a changelog. (`#14 <https://github.com/maliput/maliput_dragway/issues/14>`_)
* Updates package.xml
* Fixes sanitizers variable. (`#11 <https://github.com/maliput/maliput_dragway/issues/11>`_)
* Actions: use ubuntu:18.04 container (`#10 <https://github.com/maliput/maliput_dragway/issues/10>`_)
* Use GitHub Actions CI to build and test with gcc (`#9 <https://github.com/maliput/maliput_dragway/issues/9>`_)
* Adds scan-build to jenkins configuration. (`#8 <https://github.com/maliput/maliput_dragway/issues/8>`_)
* Parallelizes CI.
* Adds Undefined Behavior Sanitizer.
* Adds Address Sanitizer.
* Enables clang compilation. (`#4 <https://github.com/maliput/maliput_dragway/issues/4>`_)
* Updates compilation flags for gcc and clang. (`#3 <https://github.com/maliput/maliput_dragway/issues/3>`_)
* Fix LICENSE attribution. (`#2 <https://github.com/maliput/maliput_dragway/issues/2>`_)
* Merge pull request `#1 <https://github.com/maliput/maliput_dragway/issues/1>`_ from ToyotaResearchInstitute/francocipollone/move_dragway_to_a_repo
* Change remaining names from dragway to maliput_dragway.
* Adapts files and add missing files to the repository.
* Move dragway_to_urdf to maliput-integration (`#305 <https://github.com/maliput/maliput_dragway/issues/305>`_)
* Remove drake from maliput core. (`#236 <https://github.com/maliput/maliput_dragway/issues/236>`_)
* Use pybind11 version available in the workspace. (`#283 <https://github.com/maliput/maliput_dragway/issues/283>`_)
* Adds fmt as dependency. (`#283 <https://github.com/maliput/maliput_dragway/issues/283>`_)
* Remove the use of numpy package. (`#283 <https://github.com/maliput/maliput_dragway/issues/283>`_)
* Implements Quaternion. (`#264 <https://github.com/maliput/maliput_dragway/issues/264>`_)
* Replace drake::saturate by std::clamp in dragway.
* Implements logger to replace spd_log. (`#236 <https://github.com/maliput/maliput_dragway/issues/236>`_)
* Matrix library implementation. (`#237 <https://github.com/maliput/maliput_dragway/issues/237>`_)
* Vector library implementation. (`#237 <https://github.com/maliput/maliput_dragway/issues/237>`_)
* Replaces drake::VectorN<double> by maliput::math::VectorN. (`#251 <https://github.com/maliput/maliput_dragway/issues/251>`_)
* Lane: remove position type AutoDiff instantiations (`#250 <https://github.com/maliput/maliput_dragway/issues/250>`_)
* lane: remove position type symbolic instantiations (`#249 <https://github.com/maliput/maliput_dragway/issues/249>`_)
* Migrates drake_copyable.h. (`#240 <https://github.com/maliput/maliput_dragway/issues/240>`_)
* Migrates drake::unused(). (`#241 <https://github.com/maliput/maliput_dragway/issues/241>`_)
* Adjust to a new drake version.
* Upgrade to c++17.
* Build documentation by default. (`#206 <https://github.com/maliput/maliput_dragway/issues/206>`_)
* Use ament_cmake_doxygen to generate C++ documentation.  (`#165 <https://github.com/maliput/maliput_dragway/issues/165>`_)
* Modifies return value of Lane::ToLanePosition() (`#163 <https://github.com/maliput/maliput_dragway/issues/163>`_)
* Modifies ToRoadPosition to return a RoadPositionResult. (`#160 <https://github.com/maliput/maliput_dragway/issues/160>`_)
* Moves Lane::driveable_bounds() to Lane::segment_bounds(). (`#154 <https://github.com/maliput/maliput_dragway/issues/154>`_)
* Add pybind11-dev as a package.xml dependency. (`#144 <https://github.com/maliput/maliput_dragway/issues/144>`_)
* Provides support for no-spdlog-based logger. (`#136 <https://github.com/maliput/maliput_dragway/issues/136>`_)
* Add cmake clang format (`#113 <https://github.com/maliput/maliput_dragway/issues/113>`_)
* Add auto clang formatting check to colcon test (`#98 <https://github.com/maliput/maliput_dragway/issues/98>`_)
* Reformat to obey TRI style (`#87 <https://github.com/maliput/maliput_dragway/issues/87>`_)
* Logger support in maliput (`#89 <https://github.com/maliput/maliput_dragway/issues/89>`_)
* Migrates DRAKE_THROW_UNLESS to MALIPUT_THROW_UNLESS (`#74 <https://github.com/maliput/maliput_dragway/issues/74>`_)
* Replaces DRAKE\_*-aborts by MALIPUT\_* (`#73 <https://github.com/maliput/maliput_dragway/issues/73>`_)
* Updates radius constraint in FindRoadPositions (`#70 <https://github.com/maliput/maliput_dragway/issues/70>`_)
* Adds missing dragway target link libraries. (`#69 <https://github.com/maliput/maliput_dragway/issues/69>`_)
* Adds dragway::RoadGeometry::FindRoadPositions() (`#59 <https://github.com/maliput/maliput_dragway/issues/59>`_)
* Adds RoadGeometry::FindRoadPositions() (`#58 <https://github.com/maliput/maliput_dragway/issues/58>`_)
* Removed redundant maliput dir
* Create maliput ament packages
* Documentation fixes
* More documentation and markup fixes
* Express characteristic scale length concept in api::RoadGeometry (`#9306 <https://github.com/maliput/maliput_dragway/issues/9306>`_)
* Add an IdIndex interface to maliput::api::RoadGeometry.
* Port all of Drake to use getcwd instead of setAsCurrent
* Re-apply "Add drake_cc_package_library and library_lint"
* Increase Valgrind timeouts to 20x
* Revert "Add drake_cc_package_library and library_lint"
* Add drake_cc_package_library and library_lint
* Fix //drake label names in automotive/maliput/dragway
* Repair a few more drake subdir paths in docs
* Add symbolic support to Maliput lane
* Use system gflags
* Run tools/dev/6996-move
* Initial commit
* Contributors: Agustin Alba Chicar, Brian, Daniel Stonier, Drake Refactor Bot, Franco, Franco Cipollone, Geoffrey Biggs, Jamie Snape, Jeremy Nimmer, John, John Shepherd, Matt Marjanovic, Matt Marjanović, Michel Hidalgo, Soonho Kong, Steve Peters, Steven Peters
