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
#include "maliput_dragway/road_network_builder.h"

#include <map>

#include <maliput/base/intersection_book.h>
#include <maliput/base/intersection_book_loader.h>
#include <maliput/base/manual_discrete_value_rule_state_provider.h>
#include <maliput/base/manual_phase_provider.h>
#include <maliput/base/manual_phase_ring_book.h>
#include <maliput/base/manual_range_value_rule_state_provider.h>
#include <maliput/base/manual_right_of_way_rule_state_provider.h>
#include <maliput/base/manual_rulebook.h>
#include <maliput/base/phase_ring_book_loader.h>
#include <maliput/base/road_rulebook_loader.h>
#include <maliput/base/traffic_light_book.h>
#include <maliput/base/traffic_light_book_loader.h>
#include <maliput/common/logger.h>
#include <maliput/common/maliput_abort.h>
#include <maliput/math/vector.h>

#include "maliput_dragway/params.h"
#include "maliput_dragway/road_geometry.h"

namespace maliput {
namespace dragway {

RoadGeometryConfiguration RoadGeometryConfiguration::FromMap(const std::map<std::string, std::string>& parameters) {
  RoadGeometryConfiguration rg_configuration{};
  auto it = parameters.find(kNumLanes);
  if (it != parameters.end()) {
    rg_configuration.num_lanes = std::stoi(it->second);
  }
  it = parameters.find(kLength);
  if (it != parameters.end()) {
    rg_configuration.length = std::stod(it->second);
  }
  it = parameters.find(kLaneWidth);
  if (it != parameters.end()) {
    rg_configuration.lane_width = std::stod(it->second);
  }
  it = parameters.find(kShoulderWidth);
  if (it != parameters.end()) {
    rg_configuration.shoulder_width = std::stod(it->second);
  }
  it = parameters.find(kMaximumHeight);
  if (it != parameters.end()) {
    rg_configuration.maximum_height = std::stod(it->second);
  }
  it = parameters.find(kInertialToBackendFrameTranslation);
  if (it != parameters.end()) {
    rg_configuration.inertial_to_backend_frame_translation = maliput::math::Vector3::FromStr(it->second);
  }
  return rg_configuration;
}

std::map<std::string, std::string> RoadGeometryConfiguration::ToStringMap() const {
  std::map<std::string, std::string> parameters;
  parameters[kNumLanes] = std::to_string(num_lanes);
  parameters[kLength] = std::to_string(length);
  parameters[kLaneWidth] = std::to_string(lane_width);
  parameters[kShoulderWidth] = std::to_string(shoulder_width);
  parameters[kMaximumHeight] = std::to_string(maximum_height);
  parameters[kInertialToBackendFrameTranslation] = inertial_to_backend_frame_translation.to_str();
  return parameters;
}

std::unique_ptr<api::RoadNetwork> BuildRoadNetwork(const RoadGeometryConfiguration& road_geometry_configuration) {
  maliput::log()->debug("Building dragway RoadNetwork.");
  auto rg = std::make_unique<dragway::RoadGeometry>(
      api::RoadGeometryId{"Dragway with " + std::to_string(road_geometry_configuration.num_lanes) + " lanes."},
      road_geometry_configuration.num_lanes, road_geometry_configuration.length, road_geometry_configuration.lane_width,
      road_geometry_configuration.shoulder_width, road_geometry_configuration.maximum_height,
      std::numeric_limits<double>::epsilon(), std::numeric_limits<double>::epsilon(),
      road_geometry_configuration.inertial_to_backend_frame_translation);

  std::unique_ptr<ManualRulebook> rulebook = std::make_unique<ManualRulebook>();
  std::unique_ptr<TrafficLightBook> traffic_light_book = std::make_unique<TrafficLightBook>();
  std::unique_ptr<api::rules::RuleRegistry> rule_registry = std::make_unique<api::rules::RuleRegistry>();
  std::unique_ptr<ManualPhaseRingBook> phase_ring_book = std::make_unique<ManualPhaseRingBook>();
  std::unique_ptr<ManualPhaseProvider> phase_provider = std::make_unique<ManualPhaseProvider>();
  std::unique_ptr<IntersectionBook> intersection_book = std::make_unique<IntersectionBook>(rg.get());

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
  std::unique_ptr<ManualRightOfWayRuleStateProvider> right_of_way_rule_state_provider =
      std::make_unique<ManualRightOfWayRuleStateProvider>();
#pragma GCC diagnostic pop
  std::unique_ptr<ManualDiscreteValueRuleStateProvider> discrete_value_rule_state_provider =
      std::make_unique<ManualDiscreteValueRuleStateProvider>(rulebook.get());
  std::unique_ptr<ManualRangeValueRuleStateProvider> range_value_rule_state_provider =
      std::make_unique<ManualRangeValueRuleStateProvider>(rulebook.get());
  return std::make_unique<api::RoadNetwork>(std::move(rg), std::move(rulebook), std::move(traffic_light_book),
                                            std::move(intersection_book), std::move(phase_ring_book),
                                            std::move(right_of_way_rule_state_provider), std::move(phase_provider),
                                            std::move(rule_registry), std::move(discrete_value_rule_state_provider),
                                            std::move(range_value_rule_state_provider));
}

}  // namespace dragway
}  // namespace maliput
