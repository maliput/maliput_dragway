#include <memory>

#include "maliput/plugin/road_network_plugin.h"
#include "maliput_dragway/road_network_builder.h"

namespace maliput {
namespace dragway {
namespace plugin {
namespace {

maliput::dragway::BuildProperties GetPropertiesFromStringMap(const std::map<std::string, std::string> parameters) {
  BuildProperties properties{};
  auto it = parameters.find("num_lanes");
  if (it != parameters.end()) {
    properties.num_lanes = std::stoi(it->second);
  }
  it = parameters.find("length");
  if (it != parameters.end()) {
    properties.length = std::stod(it->second);
  }
  it = parameters.find("lane_width");
  if (it != parameters.end()) {
    properties.lane_width = std::stod(it->second);
  }
  it = parameters.find("shoulder_width");
  if (it != parameters.end()) {
    properties.shoulder_width = std::stod(it->second);
  }
  it = parameters.find("maximum_height");
  if (it != parameters.end()) {
    properties.maximum_height = std::stod(it->second);
  }
  return properties;
}

}  // namespace

class DragwayRoadNetwork : public maliput::plugin::RoadNetworkPlugin {
 public:
  std::unique_ptr<const maliput::api::RoadNetwork> LoadRoadNetwork(
      const std::map<std::string, std::string> parameters) const override {
    return maliput::dragway::BuildRoadNetwork(GetPropertiesFromStringMap(parameters));
  }
};

// the class factories
extern "C" std::unique_ptr<maliput::plugin::RoadNetworkPlugin> LoadMaliputRoadNetwork() {
  return std::make_unique<DragwayRoadNetwork>();
}

}  // namespace plugin
}  // namespace dragway
}  // namespace maliput
