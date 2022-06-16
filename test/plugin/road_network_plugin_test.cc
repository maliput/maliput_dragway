// BSD 3-Clause License
//
// Copyright (c) 2022, Woven Planet. All rights reserved.
// Copyright (c) 2021-2022, Toyota Research Institute. All rights reserved.
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
#include <stdlib.h>

#include <map>
#include <memory>
#include <string>

#include <gtest/gtest.h>
#include <maliput/api/junction.h>
#include <maliput/api/lane.h>
#include <maliput/api/lane_data.h>
#include <maliput/api/road_geometry.h>
#include <maliput/api/road_network.h>
#include <maliput/api/segment.h>
#include <maliput/plugin/maliput_plugin.h>
#include <maliput/plugin/maliput_plugin_manager.h>
#include <maliput/plugin/maliput_plugin_type.h>
#include <maliput/plugin/road_network_loader.h>
#include <maliput/test_utilities/maliput_math_compare.h>
#include <maliput/test_utilities/maliput_types_compare.h>

namespace maliput {
namespace dragway {
namespace {

GTEST_TEST(RoadNetworkLoader, VerifyRoadNetworkPlugin) {
  setenv("MALIPUT_PLUGIN_PATH", DEF_ROAD_NETWORK_PLUGIN, 1);
  const plugin::MaliputPlugin::Id kDragwayPluginId{"maliput_dragway"};
  static constexpr double kTolerance{1e-15};
  const std::map<std::string, std::string> rg_dragway_properties{
      {"num_lanes", "2"},      {"length", "10"},          {"lane_width", "3.7"},
      {"shoulder_width", "3"}, {"maximum_height", "5.2"}, {"inertial_to_backend_frame_translation", "{1, 2.5, -4.7}"}};

  // Check MaliputPlugin existence.
  plugin::MaliputPluginManager manager{};
  const plugin::MaliputPlugin* rn_plugin{manager.GetPlugin(kDragwayPluginId)};
  ASSERT_NE(nullptr, rn_plugin);

  // Check dragway plugin is obtained.
  EXPECT_EQ(kDragwayPluginId.string(), rn_plugin->GetId());
  EXPECT_EQ(plugin::MaliputPluginType::kRoadNetworkLoader, rn_plugin->GetType());

  plugin::RoadNetworkLoaderPtr rn_loader_ptr{nullptr};
  EXPECT_NO_THROW(rn_loader_ptr = rn_plugin->ExecuteSymbol<plugin::RoadNetworkLoaderPtr>(
                      plugin::RoadNetworkLoader::GetEntryPoint()));
  ASSERT_NE(nullptr, rn_loader_ptr);

  std::unique_ptr<maliput::plugin::RoadNetworkLoader> rn_loader{
      reinterpret_cast<plugin::RoadNetworkLoader*>(rn_loader_ptr)};
  // Check dragway RoadNetwork is constructible.
  std::unique_ptr<const api::RoadNetwork> rn;
  EXPECT_NO_THROW(rn = (*rn_loader)(rg_dragway_properties));
  ASSERT_NE(nullptr, rn);
  const api::RoadGeometry* dragway_rg = rn->road_geometry();
  EXPECT_NE(nullptr, dragway_rg);
  EXPECT_TRUE(math::test::CompareVectors(math::Vector3{1., 2.5, -4.7},
                                         dragway_rg->inertial_to_backend_frame_translation(), kTolerance));
  const api::Junction* junction = dragway_rg->junction(0);
  ASSERT_NE(nullptr, junction);
  const api::Segment* segment = junction->segment(0);
  ASSERT_NE(nullptr, segment);
  EXPECT_EQ(2, segment->num_lanes());
  const api::Lane* lane = segment->lane(0);
  ASSERT_NE(nullptr, lane);
  EXPECT_EQ(10., lane->length());
  EXPECT_TRUE(api::test::IsRBoundsClose(api::RBounds(-3.7 / 2, 3.7 / 2), lane->lane_bounds(0.), kTolerance));
  EXPECT_TRUE(
      api::test::IsRBoundsClose(api::RBounds(-3.7 / 2 - 3., 3.7 / 2 + 3.7 + 3.), lane->segment_bounds(0.), kTolerance));
  EXPECT_TRUE(api::test::IsHBoundsClose(api::HBounds(0., 5.2), lane->elevation_bounds(0., 0.), kTolerance));
}

}  // namespace
}  // namespace dragway
}  // namespace maliput
