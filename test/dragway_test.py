from __future__ import print_function

import copy
import unittest

from maliput.api import (
    InertialPosition,
    LanePosition,
    LanePositionResult,
    RoadGeometry,
    RoadGeometryId,
    RoadPosition,
    Rotation
)

from maliput.math import (
    Quaternion,
    Vector3,
    Vector4
)

from maliput_dragway.dragway import create_dragway

# Instantiate and return a two-lane straight road.
def make_test_dragway(lane_width, length):
    kNumLanes = 2
    kShoulderWidth = 1.
    kHeight = 5.
    kTol = 1e-6
    kInertialToBackendFrameTranslation = Vector3(0., 0., 0.)

    rg_id = RoadGeometryId("two_lane_road")
    return create_dragway(
        road_id=rg_id, num_lanes=kNumLanes, length=length,
        lane_width=lane_width, shoulder_width=kShoulderWidth,
        maximum_height=kHeight, linear_tolerance=kTol,
        angular_tolerance=kTol,
        inertial_to_backend_frame_translation=kInertialToBackendFrameTranslation)


class TestMaliput(unittest.TestCase):
    def test_dragway_construction(self):
        """
        Evaluates the construction of a 2-lane dragway.
        """
        rg = make_test_dragway(lane_width=4., length=100.)
        self.assertEqual(rg.num_junctions(), 1)
        junction = rg.junction(0)
        self.assertEqual(junction.num_segments(), 1)
        segment = junction.segment(0)
        self.assertEqual(segment.num_lanes(), 2)
        lane_0 = segment.lane(0)
        lane_1 = segment.lane(1)

    def test_dragway_geometry(self):
        """
        Evaluates lane geometric queries of a 2-lane dragway.
        """
        kLaneWidth = 4.
        kLength = 100.
        rg = make_test_dragway(lane_width=kLaneWidth,
                               length=kLength)
        lane_0 = rg.junction(0).segment(0).lane(0)
        lane_1 = rg.junction(0).segment(0).lane(1)

        # Test that both Lanes have equal and expected lengths.
        self.assertEqual(lane_0.length(), kLength)
        self.assertEqual(lane_1.length(), kLength)
        self.assertEqual(lane_0.length(), lane_1.length())

        # Test Lane orientations for consistency.
        lane_start = LanePosition(0., 0., 0.)
        lane_end = LanePosition(lane_0.length(), 0., 0.)
        self.assertEqual(
            lane_0.GetOrientation(lane_start).quat().coeffs(),
            Vector4(1., 0., 0., 0.)
        )
        self.assertEqual(
            lane_0.GetOrientation(lane_start).quat().coeffs(),
            lane_0.GetOrientation(lane_end).quat().coeffs()
        )
        self.assertEqual(
            lane_1.GetOrientation(lane_start).quat().coeffs(),
            lane_1.GetOrientation(lane_end).quat().coeffs()
        )
        self.assertEqual(
            lane_0.GetOrientation(lane_end).quat().coeffs(),
            lane_1.GetOrientation(lane_end).quat().coeffs()
        )

        # Test the Lane <-> Geo space coordinate conversion.
        lane_pos = LanePosition(0., 0., 0.)
        inertial_pos_result = lane_0.ToInertialPosition(lane_pos)
        inertial_pos_expected = InertialPosition(0., -kLaneWidth / 2., 0.)
        self.assertEqual(inertial_pos_result.xyz(), inertial_pos_expected.xyz())

        inertial_pos = InertialPosition(1., kLaneWidth / 2., 3.)
        lane_pos_result = lane_1.ToLanePosition(inertial_pos)
        lane_pos_result_expected = \
            LanePositionResult(LanePosition(1., 0., 3.), InertialPosition(0., 0., 0.), 0.)
        self.assertEqual(lane_pos_result.lane_position.srh(),
                         lane_pos_result_expected.lane_position.srh())
        self.assertEqual(lane_pos_result.nearest_position.xyz(), inertial_pos.xyz())
        self.assertEqual(lane_pos_result.distance, lane_pos_result_expected.distance)
