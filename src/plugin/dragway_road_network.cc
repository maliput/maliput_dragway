#include <memory>

#include "maliput/plugin/road_network_plugin.h"
#include "maliput_dragway/road_network_builder.h"

namespace maliput {
namespace dragway {
namespace plugin {

class DragwayRoadNetwork : public maliput::plugin::RoadNetworkPlugin {
 public:
  std::unique_ptr<const maliput::api::RoadNetwork> LoadRoadNetwork() const override {
    return maliput::dragway::BuildRoadNetwork();
  }
};

// the class factories
extern "C" std::unique_ptr<maliput::plugin::RoadNetworkPlugin> LoadMaliputRoadNetwork() {
  return std::make_unique<DragwayRoadNetwork>();
}

}  // namespace plugin
}  // namespace dragway
}  // namespace maliput
