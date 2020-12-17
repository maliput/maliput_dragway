#pragma once

#include "maliput/api/road_geometry.h"
#include "maliput/api/road_network.h"

#include <memory>

namespace maliput {
namespace dragway {

/// Contains the attributes needed for building a dragway::RoadGeometry.
struct BuildProperties {
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
};

/// Builds an api::RoadNetwork based on Dragway implementation.
/// @param build_properties Holds the properties to build the RoadNetwork.
/// @return A maliput::api::RoadNetwork.
std::unique_ptr<const api::RoadNetwork> BuildRoadNetwork(const BuildProperties& build_properties = BuildProperties());

} // namespace dragway
} // namespace maliput
