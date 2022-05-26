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

#include <map>
#include <memory>
#include <optional>
#include <vector>

#include <maliput/api/branch_point.h>
#include <maliput/api/lane.h>
#include <maliput/api/road_geometry.h>
#include <maliput/common/maliput_copyable.h>

namespace maliput {
namespace dragway {

class BranchPoint;
class Lane;

/// Dragway's implementation of api::LaneEndSet. Since a dragway::Lane connects
/// to itself, this LaneEndSet only contains one api::LaneEnd.
class LaneEndSet final : public api::LaneEndSet {
 public:
  MALIPUT_NO_COPY_NO_MOVE_NO_ASSIGN(LaneEndSet)

  explicit LaneEndSet(const api::Lane* lane, api::LaneEnd::Which which_end) : end_(lane, which_end) {}

  ~LaneEndSet() override = default;

 private:
  int do_size() const override { return 1; }

  const api::LaneEnd& do_get(int) const override { return end_; }

  const api::LaneEnd end_;
};

/// Dragway's implementation of api::BranchPoint.
class BranchPoint final : public api::BranchPoint {
 public:
  MALIPUT_NO_COPY_NO_MOVE_NO_ASSIGN(BranchPoint)

  /// Constructs a fully initialized BranchPoint for a Dragway lane.
  ///
  /// @param[in] id The ID of this branch point. It can be any user-specified
  /// value.
  ///
  /// @param[in] lane A pointer to the lane to which this branch point belongs.
  /// This pointer must remain valid for the lifetime of this class's instance.
  ///
  /// @param[in] road_geometry A pointer to the %RoadGeometry to which this
  /// BranchPoint belongs. This pointer must remain valid for the lifetime of
  /// this class's instance.
  ///
  BranchPoint(const api::BranchPointId& id, const Lane* lane, const api::RoadGeometry* road_geometry);

  ~BranchPoint() final = default;

 private:
  api::BranchPointId do_id() const override { return id_; }

  const api::RoadGeometry* do_road_geometry() const override;

  const api::LaneEndSet* DoGetConfluentBranches(const api::LaneEnd& end) const override;

  const api::LaneEndSet* DoGetOngoingBranches(const api::LaneEnd& end) const override;

  std::optional<api::LaneEnd> DoGetDefaultBranch(const api::LaneEnd& end) const override;

  const api::LaneEndSet* DoGetASide() const override;

  const api::LaneEndSet* DoGetBSide() const override;

  const api::BranchPointId id_;
  const api::RoadGeometry* road_geometry_{};
  const LaneEndSet start_side_lane_end_set_;
  const LaneEndSet finish_side_lane_end_set_;
};

}  // namespace dragway
}  // namespace maliput
