// BSD 3-Clause License
//
// Copyright (c) 2022, Woven Planet. All rights reserved.
// Copyright (c) 2019-2022, Toyota Research Institute. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// Copyright 2021 Toyota Research Institute
#pragma once

namespace maliput {
namespace dragway {

/// @defgroup road_geometry_configuration_keys RoadGeometry configuration builder keys
///
/// Parameters used during the RoadGeometry building process.
///
/// When parameters are omitted the default value will be used.
///
/// Example of use:
/// @code{cpp}
/// #include <maliput_dragway/params.h>
/// #include <maliput_dragway/road_network_builder.h>
/// // ...
/// const std::map<std::string, std::string> builder_configuration {
///   {maliput::dragway::kNumLanes, "4"},
///   {maliput::dragway::kLength, "150"},
///   {maliput::dragway::kLaneWidth, "3"},
/// };
/// auto road_network = maliput::dragway::BuildRoadNetwork(builder_configuration)();
/// @endcode
///
/// @{

/// Number of lanes.
///   - Default: @e "2"
static constexpr char const* kNumLanes{"num_lanes"};
/// Length of the dragway.
///   - Default: @e "10"
static constexpr char const* kLength{"length"};
/// Width of the lanes.
///   - Default: @e "3.7"
static constexpr char const* kLaneWidth{"lane_width"};
/// Width of the shoulders of the road.
///   - Default: @e "3."
static constexpr char const* kShoulderWidth{"shoulder_width"};
/// Maximum height above the road surface.
///   - Default: @e "5.2"
static constexpr char const* kMaximumHeight{"maximum_height"};
/// Translation from maliput to maliput_osm inertial frame.
/// The format of the 3-dimensional vector that is expected to be passed
/// should be {X, Y, Z}. Same format as maliput::math::Vector3 is
/// serialized.
///   - Default: @e "{0., 0., 0.}"
static constexpr char const* kInertialToBackendFrameTranslation{"inertial_to_backend_frame_translation"};

/// @}

}  // namespace dragway
}  // namespace maliput
