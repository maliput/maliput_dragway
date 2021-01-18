#include <gtest/gtest.h>

#include <map>
#include <memory>
#include <string>

#include "maliput/plugin/maliput_plugin.h"
#include "maliput/plugin/maliput_plugin_manager.h"
#include "maliput/plugin/maliput_plugin_type.h"
#include "maliput/plugin/road_network_loader.h"
#include "maliput_dragway/road_geometry.h"

namespace maliput {
namespace dragway {
namespace {

GTEST_TEST(RoadNetworkLoader, VerifyRoadNetworkPlugin) {
  const plugin::MaliputPlugin::Id kDragwayPluginId{"maliput_dragway"};
  const std::map<std::string, std::string> rg_dragway_properties{
      {"num_lanes", "2"}, {"length", "10"}, {"lane_width", "3.7"}, {"shoulder_width", "3"}, {"maximum_height", "5.2"},
  };

  // Check MaliputPlugin existence.
  plugin::MaliputPluginManager manager{};
  plugin::MaliputPlugin const* rn_plugin{nullptr};
  EXPECT_NO_THROW(rn_plugin = manager.GetPlugin(kDragwayPluginId));
  ASSERT_NE(nullptr, rn_plugin);

  // Check dragway plugin is obtained.
  std::unique_ptr<maliput::plugin::RoadNetworkLoader> rn_loader{nullptr};
  if (rn_plugin != nullptr) {
    // Without checking rn_plugin nullptrness the scan-build failed in this line.
    EXPECT_EQ(kDragwayPluginId.string(), rn_plugin->GetId());
    EXPECT_EQ(plugin::MaliputPluginType::kRoadNetworkLoader, rn_plugin->GetType());
    EXPECT_NO_THROW(rn_loader = rn_plugin->ExecuteSymbol<std::unique_ptr<plugin::RoadNetworkLoader>>(
                        plugin::RoadNetworkLoader::GetEntryPoint()));
  }
  ASSERT_NE(nullptr, rn_loader);

  // Check dragway RoadNetwork is constructible.
  std::unique_ptr<const maliput::api::RoadNetwork> rn{nullptr};
  EXPECT_NO_THROW(rn = (*rn_loader)(rg_dragway_properties));
  ASSERT_NE(nullptr, rn);
  auto dragway_rg = dynamic_cast<const RoadGeometry*>(rn->road_geometry());
  EXPECT_NE(nullptr, dragway_rg);
}

}  // namespace
}  // namespace dragway
}  // namespace maliput
