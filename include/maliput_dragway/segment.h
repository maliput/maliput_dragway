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
#pragma once

#include <memory>
#include <utility>
#include <vector>

#include <maliput/api/junction.h>
#include <maliput/api/lane.h>
#include <maliput/api/lane_data.h>
#include <maliput/api/segment.h>
#include <maliput/common/maliput_copyable.h>

#include "maliput_dragway/lane.h"

namespace maliput {
namespace dragway {

class Junction;

/**
  Dragway's implementation of api::Segment. It contains multiple straight
  lanes. For the lane semantics, see the class descriptions of Lane.

  The following ASCII art shows how N lanes are arranged in a segment.

  <pre>

              lane_bounds ---     X         -------- lane index 1
                            |     ^         |
     lane index n ---       |     |         |   --- lane index 0
                    |       |     |         |   |
                    V     |<->|   |         V   V
                -------------------------------------
                | | : | : | : | : | : | : | : | : | |
                | | : | : | : | : | : | : | : | : | |
                | | : | : | : | : | : | : | : | : | |
                | | : | : | : | : | : | : | : | : | |
                | | : | : | : | : | : | : | : | : | |
                | | : | : | : | : | : | : | : | : | |
  Y <-----------------------------o----------------------------->
                ^                 |             ^   ^
                |                 |             |   |
              y_max               |             |  y_min
                                  |             |
                                  V             --- y offset of lane 0

                |<--------------------------------->|
                              road_width

  </pre>

   Note that lane indices increase to the left, which matches the fact that
   within a Lane, `r` increases to the left.
*/
class Segment final : public api::Segment {
 public:
  MALIPUT_NO_COPY_NO_MOVE_NO_ASSIGN(Segment)

  /// Constructs a new dragway Segment.
  ///
  /// @param[in] junction The junction to which this Segment belongs.
  ///
  /// @param[in] num_lanes The number of lanes in the segment.
  ///
  /// @param[in] length The length of the dragway.
  ///
  /// @param[in] lane_width The width of each lane.
  ///
  /// @param[in] shoulder_width The width of the shoulders on each side of the
  /// road.
  ///
  /// @param[in] maximum_height The maximum height above the road surface.
  /// modelled by the RoadGeometry.
  Segment(Junction* junction, int num_lanes, double length, double lane_width, double shoulder_width,
          double maximum_height);

  ~Segment() final = default;

 private:
  api::SegmentId do_id() const final { return id_; }

  const api::Junction* do_junction() const final;

  int do_num_lanes() const final { return static_cast<int>(lanes_.size()); }

  const api::Lane* do_lane(int index) const final;

  const api::SegmentId id_;
  const Junction* junction_{};
  std::vector<std::unique_ptr<Lane>> lanes_;
};

}  // namespace dragway
}  // namespace maliput
