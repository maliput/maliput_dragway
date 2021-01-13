// Copyright 2021 Toyota Research Institute
#include "maliput_dragway/road_network_builder.h"

#include <map>

#include "maliput/base/intersection_book.h"
#include "maliput/base/intersection_book_loader.h"
#include "maliput/base/manual_discrete_value_rule_state_provider.h"
#include "maliput/base/manual_phase_provider.h"
#include "maliput/base/manual_phase_ring_book.h"
#include "maliput/base/manual_range_value_rule_state_provider.h"
#include "maliput/base/manual_right_of_way_rule_state_provider.h"
#include "maliput/base/manual_rulebook.h"
#include "maliput/base/phase_ring_book_loader.h"
#include "maliput/base/road_rulebook_loader.h"
#include "maliput/base/traffic_light_book.h"
#include "maliput/base/traffic_light_book_loader.h"
#include "maliput/common/logger.h"
#include "maliput/common/maliput_abort.h"

#include "maliput_dragway/road_geometry.h"

namespace maliput {
namespace dragway {

std::unique_ptr<const api::RoadNetwork> BuildRoadNetwork(const RoadGeometryConfiguration& road_geometry_configuration) {
  maliput::log()->debug("Building dragway RoadNetwork.");
  auto rg = std::make_unique<dragway::RoadGeometry>(
      api::RoadGeometryId{"Dragway with " + std::to_string(road_geometry_configuration.num_lanes) + " lanes."},
      road_geometry_configuration.num_lanes, road_geometry_configuration.length, road_geometry_configuration.lane_width,
      road_geometry_configuration.shoulder_width, road_geometry_configuration.maximum_height,
      std::numeric_limits<double>::epsilon(), std::numeric_limits<double>::epsilon());

  std::unique_ptr<ManualRulebook> rulebook = std::make_unique<ManualRulebook>();
  std::unique_ptr<TrafficLightBook> traffic_light_book = std::make_unique<TrafficLightBook>();
  std::unique_ptr<api::rules::RuleRegistry> rule_registry = std::make_unique<api::rules::RuleRegistry>();
  std::unique_ptr<ManualPhaseRingBook> phase_ring_book = std::make_unique<ManualPhaseRingBook>();
  std::unique_ptr<ManualPhaseProvider> phase_provider = std::make_unique<ManualPhaseProvider>();
  std::unique_ptr<IntersectionBook> intersection_book = std::make_unique<IntersectionBook>();

  std::unique_ptr<ManualRightOfWayRuleStateProvider> right_of_way_rule_state_provider =
      std::make_unique<ManualRightOfWayRuleStateProvider>();
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
