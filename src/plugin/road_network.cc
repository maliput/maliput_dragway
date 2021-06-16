// Copyright 2021 Toyota Research Institute
#include <algorithm>
#include <memory>
#include <string>

#include <maliput/common/maliput_throw.h>
#include <maliput/plugin/road_network_loader.h>

#include "maliput_dragway/road_network_builder.h"

namespace maliput {
namespace dragway {
namespace plugin {
namespace {

// Parses @p vector_str that should come in the following format "{X, Y, Z}"
// (white spaces could or could not be there).
// @throws maliput::common::assertion_error When @p vector_str does not follow
//         the specified format.
// @return A math::Vector3 out of @p vector_str
math::Vector3 ParseVector3(const std::string& vector_str) {
  static constexpr char kLeftBrace = '{';
  static constexpr char kRightBrace = '}';
  static constexpr char kComma = ',';

  // @{ Checks vector_str format.
  MALIPUT_THROW_UNLESS(std::count(vector_str.begin(), vector_str.end(), kLeftBrace) == 1);
  MALIPUT_THROW_UNLESS(std::count(vector_str.begin(), vector_str.end(), kRightBrace) == 1);
  MALIPUT_THROW_UNLESS(std::count(vector_str.begin(), vector_str.end(), kComma) == 2);
  // @}

  // @{ Extracts each number.
  const std::size_t first_comma_pos = vector_str.find_first_of(kComma);
  const std::size_t second_comma_pos = vector_str.find_first_of(kComma, vector_str.find_first_of(kComma) + 1);
  const std::string x_str = vector_str.substr(1, first_comma_pos - 1);
  const std::string y_str = vector_str.substr(first_comma_pos + 1, second_comma_pos - 1);
  const std::string z_str = vector_str.substr(second_comma_pos + 1, vector_str.find_first_of(kRightBrace) - 1);
  // @}

  return {std::stod(x_str), std::stod(y_str), std::stod(z_str)};
}

// Return a dragway::RoadGeometryConfiguration object out of a map of strings.
// When a property is missing it uses the default value from dragway::RoadGeometryConfiguration.
// @param parameters  A dictionary of properties to fill in a dragway::RoadGeometryConfiguration struct.
//                    Keys are the names of attributes in dragway::RoadGeometryConfiguration.
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
  it = parameters.find("inertial_to_backend_frame_translation");
  if (it != parameters.end()) {
    rg_configuration.inertial_to_backend_frame_translation = ParseVector3(it->second);
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
