#include <memory>

#include "maliput_dragway/road_network_builder.h"
#include "maliput/plugin/road_network_plugin.h"


namespace maliput {
namespace plugin {

class DragwayRoadNetwork : public RoadNetworkPlugin {
 public:
  std::unique_ptr<const maliput::api::RoadNetwork> LoadRoadNetwork() const override {
    return maliput::dragway::BuildRoadNetwork();
  }
};

// the class factories
extern "C" std::unique_ptr<RoadNetworkPlugin> LoadMaliputRoadNetwork() { return std::make_unique<DragwayRoadNetwork>(); }

}  // namespace plugin
}  // namespace maliput
