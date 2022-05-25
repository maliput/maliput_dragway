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
#include "maliput_dragway/branch_point.h"

#include <optional>

#include "maliput_dragway/lane.h"

namespace maliput {
namespace dragway {

BranchPoint::BranchPoint(const api::BranchPointId& id, const Lane* lane, const api::RoadGeometry* road_geometry)
    : id_(id),
      road_geometry_(road_geometry),
      start_side_lane_end_set_(lane, api::LaneEnd::kStart),
      finish_side_lane_end_set_(lane, api::LaneEnd::kFinish) {}

const api::RoadGeometry* BranchPoint::do_road_geometry() const { return road_geometry_; }

const api::LaneEndSet* BranchPoint::DoGetConfluentBranches(const api::LaneEnd& end) const {
  if (end.end == api::LaneEnd::kStart) {
    return &start_side_lane_end_set_;
  } else {
    return &finish_side_lane_end_set_;
  }
}

const api::LaneEndSet* BranchPoint::DoGetOngoingBranches(const api::LaneEnd& end) const {
  if (end.end == api::LaneEnd::kStart) {
    return &finish_side_lane_end_set_;
  } else {
    return &start_side_lane_end_set_;
  }
}

std::optional<api::LaneEnd> BranchPoint::DoGetDefaultBranch(const api::LaneEnd& end) const {
  // The result should be an ongoing branch for the given input. Thus, a Start
  // input should yield a Finish output (since start connects to finish) and
  // vice-versa.
  //
  // Since there is only one LaneEnd per side, return it as the default.
  if (end.end == api::LaneEnd::kStart) {
    return finish_side_lane_end_set_.get(0);
  } else {
    return start_side_lane_end_set_.get(0);
  }
}

const api::LaneEndSet* BranchPoint::DoGetASide() const { return &start_side_lane_end_set_; }

const api::LaneEndSet* BranchPoint::DoGetBSide() const { return &finish_side_lane_end_set_; }

}  // namespace dragway
}  // namespace maliput
