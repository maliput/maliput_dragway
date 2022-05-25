// BSD 3-Clause License
//
// Copyright (c) 2022, Woven Planet. All rights reserved.
// Copyright (c) 2019-2022, Toyota Research Institute. All rights reserved.
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
#pragma once

#include <gtest/gtest.h>
#include <maliput/api/lane.h>

#include "maliput_dragway/road_geometry.h"

namespace maliput {
namespace dragway {

/// A fixture for tests that use a dragway.
class DragwayBasedTest : public ::testing::Test {
 protected:
  DragwayBasedTest();
  void SetUp() override;

  // The number of lanes was intentionally chosen to evaluate all combinations
  // of adjacent lanes, i.e., it includes a lane with just a lane to the left, a
  // lane with just a lane to the right, and a lane with lanes to both the left
  // and right. The rest of the parameters were arbitrarily chosen.
  const int kNumLanes{3};
  const double kLength{100};
  const double kLaneWidth{6};
  const double kShoulderWidth{1};
  const double kMaxHeight{5};
  const RoadGeometry dragway_;
  const api::Lane* right_lane_;
  const api::Lane* center_lane_;
  const api::Lane* left_lane_;
};

}  // namespace dragway
}  // namespace maliput
