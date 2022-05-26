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
#include "maliput_dragway_test_utilities/fixtures.h"

#include <limits>

#include "maliput_dragway/road_geometry.h"

using maliput::api::InertialPosition;
using maliput::api::RoadGeometryId;

namespace maliput {
namespace dragway {

DragwayBasedTest::DragwayBasedTest()
    : dragway_(RoadGeometryId("my_dragway"), kNumLanes, kLength, kLaneWidth, kShoulderWidth, kMaxHeight,
               std::numeric_limits<double>::epsilon() /* linear_tolerance */,
               std::numeric_limits<double>::epsilon() /* angular_tolerance */,
               math::Vector3(0., 0., 0.) /* inertial_to_backend_frame_translation */),
      right_lane_(dragway_.ToRoadPosition(InertialPosition(0, -kLaneWidth, 0)).road_position.lane),
      center_lane_(dragway_.ToRoadPosition(InertialPosition(0, 0, 0)).road_position.lane),
      left_lane_(dragway_.ToRoadPosition(InertialPosition(0, kLaneWidth, 0)).road_position.lane) {}

void DragwayBasedTest::SetUp() {
  ASSERT_TRUE(right_lane_->to_left());
  ASSERT_TRUE(center_lane_->to_left());
  ASSERT_TRUE(center_lane_->to_right());
  ASSERT_TRUE(left_lane_->to_right());
}

}  // namespace dragway
}  // namespace maliput
