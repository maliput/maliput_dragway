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

#include <limits>
#include <memory>
#include <optional>
#include <vector>

#include <maliput/api/basic_id_index.h>
#include <maliput/api/branch_point.h>
#include <maliput/api/junction.h>
#include <maliput/api/lane_data.h>
#include <maliput/api/road_geometry.h>
#include <maliput/common/maliput_copyable.h>
#include <maliput/math/vector.h>

#include "maliput_dragway/branch_point.h"
#include "maliput_dragway/junction.h"

namespace maliput {
namespace dragway {

/// Dragway's implementation of api::RoadGeometry.
///
/// To understand the characteristics of the geometry, consult the
/// dragway::Segment and dragway::Lane detailed class overview docs.
class RoadGeometry final : public api::RoadGeometry {
 public:
  MALIPUT_NO_COPY_NO_MOVE_NO_ASSIGN(RoadGeometry)

  /// Constructs a dragway RoadGeometry.
  ///
  /// @param[in] id The ID of this RoadGeometry. This can be any user-selectable
  /// value.
  ///
  /// @param[in] num_lanes The number of lanes. This must be greater than zero.
  ///
  /// @param[in] length The length of the dragway.
  ///
  /// @param[in] lane_width The width of each lane.
  ///
  /// @param[in] shoulder_width The width of the shoulders on each side of the
  /// road.
  ///
  /// @param[in] maximum_height The maximum height above the road surface
  /// modelled by the RoadGeometry.
  ///
  /// @param[in] linear_tolerance The tolerance guaranteed for linear
  /// measurements (positions).
  ///
  /// @param[in] angular_tolerance The tolerance guaranteed for angular
  /// measurements (orientations).
  ///
  /// @param[in] inertial_to_backend_frame_translation the Inertial Frame to Backend
  ///        Frame translation vector
  RoadGeometry(const api::RoadGeometryId& id, int num_lanes, double length, double lane_width, double shoulder_width,
               double maximum_height, double linear_tolerance, double angular_tolerance,
               const math::Vector3& inertial_to_backend_frame_translation);

  ~RoadGeometry() final = default;

 private:
  api::RoadGeometryId do_id() const final { return id_; }

  int do_num_junctions() const final { return 1; }

  const api::Junction* do_junction(int index) const final;

  int do_num_branch_points() const final;

  const api::BranchPoint* do_branch_point(int index) const final;

  const IdIndex& DoById() const override { return id_index_; }

  api::RoadPositionResult DoToRoadPosition(const api::InertialPosition& inertial_position,
                                           const std::optional<api::RoadPosition>& hint) const final;

  // Forwards the call to
  // maliput::geometry_base::BruteForceFindRoadPositionsStrategy().
  std::vector<api::RoadPositionResult> DoFindRoadPositions(const api::InertialPosition& inertial_position,
                                                           double radius) const final;

  double do_linear_tolerance() const final { return linear_tolerance_; }

  double do_angular_tolerance() const final { return angular_tolerance_; }

  double do_scale_length() const final { return scale_length_; }

  math::Vector3 do_inertial_to_backend_frame_translation() const override {
    return inertial_to_backend_frame_translation_;
  }

  // Returns true iff `inertial_pos` is "on" the dragway. It is on the dragway iff
  // `inertial_pos.x` and `inertial_pos.y` fall within the dragway's segment surface.
  bool IsInertialPositionOnDragway(const api::InertialPosition& inertial_pos) const;

  // Returns the index of the lane on which the provided `inertial_pos` resides. This
  // method requires that the provided `inertial_pos` be on the dragway as determined
  // by IsInertialPositionOnDragway().
  int GetLaneIndex(const api::InertialPosition& inertial_pos) const;

  const api::RoadGeometryId id_;
  const double linear_tolerance_{};
  const double angular_tolerance_{};
  const double scale_length_{};
  const math::Vector3 inertial_to_backend_frame_translation_{};
  const Junction junction_;
  api::BasicIdIndex id_index_;
};

}  // namespace dragway
}  // namespace maliput
