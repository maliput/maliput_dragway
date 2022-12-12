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
#include <algorithm>
#include <memory>
#include <string>

#include <maliput/common/maliput_throw.h>
#include <maliput/math/vector.h>
#include <maliput/plugin/road_network_loader.h>

#include "maliput_dragway/road_network_builder.h"

namespace maliput {
namespace dragway {
namespace plugin {

// Implementation of a maliput::plugin::RoadNetworkLoader using dragway backend.
class RoadNetworkLoader : public maliput::plugin::RoadNetworkLoader {
 public:
  std::unique_ptr<maliput::api::RoadNetwork> operator()(
      const std::map<std::string, std::string>& properties) const override {
    return maliput::dragway::BuildRoadNetwork(RoadGeometryConfiguration::FromMap(properties));
  }

  std::map<std::string, std::string> GetDefaultParameters() const override {
    return RoadGeometryConfiguration{}.ToStringMap();
  }
};

REGISTER_ROAD_NETWORK_LOADER_PLUGIN("maliput_dragway", RoadNetworkLoader);

}  // namespace plugin
}  // namespace dragway
}  // namespace maliput
