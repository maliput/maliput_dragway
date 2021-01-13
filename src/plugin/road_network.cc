// Copyright 2021 Toyota Research Institute
#include <memory>

#include "maliput/plugin/road_network_loader.h"
#include "maliput_dragway/road_network_builder.h"

namespace maliput {
namespace dragway {
namespace plugin {
namespace {

// Return a dragway::RoadGeometryConfiguration object out of a map of strings.
// When a property is missing it uses the default value from dragway::RoadGeometryConfiguration.
// @param parameters A map of string.
// @returns A dragway::RoadGeometryConfiguration.
maliput::dragway::RoadGeometryConfiguration GetPropertiesFromStringMap(
    const std::map<std::string, std::string>& parameters) {
  RoadGeometryConfiguration rg_configuration{};
  auto it = parameters.find("num_lanes");
  if (it != parameters.end()) {
    rg_configuration.num_lanes = std::stoi(it->second);
  }
  it = parameters.find("length");
  if (it != parameters.end()) {
    rg_configuration.length = std::stod(it->second);
  }
  it = parameters.find("lane_width");
  if (it != parameters.end()) {
    rg_configuration.lane_width = std::stod(it->second);
  }
  it = parameters.find("shoulder_width");
  if (it != parameters.end()) {
    rg_configuration.shoulder_width = std::stod(it->second);
  }
  it = parameters.find("maximum_height");
  if (it != parameters.end()) {
    rg_configuration.maximum_height = std::stod(it->second);
  }
  return rg_configuration;
}

// Implementation of a maliput::plugin::RoadNetworkLoader using dragway backend.
class RoadNetworkLoader : public maliput::plugin::RoadNetworkLoader {
 public:
  std::unique_ptr<const maliput::api::RoadNetwork> operator()(
      const std::map<std::string, std::string>& properties) const override {
    return maliput::dragway::BuildRoadNetwork(GetPropertiesFromStringMap(properties));
  }
};

}  // namespace

REGISTER_ROAD_NETWORK_LOADER_PLUGIN("maliput_dragway", RoadNetworkLoader);

}  // namespace plugin
}  // namespace dragway
}  // namespace maliput
