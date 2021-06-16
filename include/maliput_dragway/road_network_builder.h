// Copyright 2021 Toyota Research Institute
#pragma once

#include <memory>

#include <maliput/api/road_geometry.h>
#include <maliput/api/road_network.h>

namespace maliput {
namespace dragway {

/// Contains the attributes needed for building a dragway::RoadGeometry.
struct RoadGeometryConfiguration {
  /// Number of lanes.
  int num_lanes{2};
  /// Length of the lanes.
  double length{10};
  /// Width of the lanes.
  double lane_width{3.7};
  /// Width of the shoulders of the road.
  double shoulder_width{3.};
  /// Maximum height above the road surface.
  double maximum_height{5.2};
  /// Inertial to Backend Frame translation.
  math::Vector3 inertial_to_backend_frame_translation{0., 0., 0.};
};

/// Builds an api::RoadNetwork based on Dragway implementation.
/// @param road_geometry_configuration Holds the properties to build the RoadNetwork.
/// @return A maliput::api::RoadNetwork.
std::unique_ptr<const api::RoadNetwork> BuildRoadNetwork(const RoadGeometryConfiguration& road_geometry_configuration);

}  // namespace dragway
}  // namespace maliput
