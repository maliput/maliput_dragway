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
#include "maliput_dragway/segment.h"

#include <string>
#include <utility>

#include <maliput/api/lane.h>
#include <maliput/common/maliput_abort.h>

#include "maliput_dragway/junction.h"
#include "maliput_dragway/lane.h"

namespace maliput {
namespace dragway {

Segment::Segment(Junction* junction, int num_lanes, double length, double lane_width, double shoulder_width,
                 double maximum_height)
    : id_("Dragway_Segment_ID"), junction_(junction) {
  // To better understand the semantics of the variables defined in this method,
  // see the class description.

  const api::HBounds elevation_bounds(0., maximum_height);
  const api::RBounds lane_bounds({-lane_width / 2, lane_width / 2});
  const double road_width = num_lanes * lane_width + 2 * shoulder_width;
  const double y_min = -road_width / 2;
  const double y_max = road_width / 2;

  for (int i = 0; i < num_lanes; ++i) {
    const double y_offset = y_min + shoulder_width + i * lane_width + lane_width / 2;
    const api::RBounds segment_bounds({y_min - y_offset, y_max - y_offset});

    auto lane = std::make_unique<Lane>(this, api::LaneId("Dragway_Lane_" + std::to_string(i)), i, length, y_offset,
                                       lane_bounds, segment_bounds, elevation_bounds);
    lanes_.push_back(move(lane));
  }

  // Sets the left and right lanes of each lane.
  for (int i = 0; i < num_lanes; ++i) {
    Lane* current_lane = lanes_.at(i).get();

    if (i > 0) {
      Lane* right_lane = lanes_.at(i - 1).get();
      current_lane->set_lane_to_right(right_lane);
    }

    if (i < num_lanes - 1) {
      Lane* left_lane = lanes_.at(i + 1).get();
      current_lane->set_lane_to_left(left_lane);
    }
  }
}

const api::Junction* Segment::do_junction() const { return junction_; }

const api::Lane* Segment::do_lane(int index) const {
  MALIPUT_DEMAND(index < num_lanes());
  return lanes_.at(index).get();
}

}  // namespace dragway
}  // namespace maliput
