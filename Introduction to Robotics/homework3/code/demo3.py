# -*- coding: utf-8 -*-
# @Author : zhux
# @Email : zhu-x21@mails.tsinghua.edu.cn

import os, time, copy, math
import numpy as np
import pybullet_data
import pybullet as p
from core import *
from robot_env import *

# for pick and place demo, use PICK_PLACE

# CONTROLLER = "PID"
CONTROLLER = "COMPUTE_TORQUE"


def control_test(robot, physicsClientId):
    robot.set_control_mode("torque")
    robot.reset()

    screw_axis = robot.get_screw_axis()
    M = robot.get_end_eff_home_trans()
    R = np.array(p.getMatrixFromQuaternion(p.getQuaternionFromEuler((3.1415926, 0, 0)))).reshape(3, 3)
    thetalist0 = [0] * 7
    end_pose = [0.4, 0.3, 0.55]
    P = np.array(end_pose)
    T = rp_to_trans(R, P)
    thetalist1, state = IK_in_space(np.array(screw_axis).T, M, T, thetalist0, 0.001, 0.0005)

    if CONTROLLER == "PID":
        kps = [400, 400, 400, 400, 400, 400, 400]
        kds = [40, 40, 40, 40, 40, 40, 40]
        kis = [0] * 7
        robot.joint_PID_control((np.array(initial_pos_list[0:-2]) + np.array(thetalist0)),
                                (np.array(initial_pos_list[0:-2]) + np.array(thetalist1)), kps, kds, kis)
    elif CONTROLLER == "COMPUTE_TORQUE":
        robot.computedTorqueControl2((np.array(initial_pos_list[0:-2]) + np.array(thetalist0)),
                                     (np.array(initial_pos_list[0:-2]) + np.array(thetalist1)))

    M = robot.cal_eff_trans()
    print(M)
    print("\nyou should find that M is close to your desired pose")
    print("finish control_test()")
    return M


def test_panda(physicsClientId, controlMode="position"):
    # create robot
    robot = pandaEnv(physicsClientId, controlMode=controlMode)
    p.setGravity(0, 0, -9.8, physicsClientId=physicsClientId)

    robot.debug_gui()
    robot.pre_grasp()

    for _ in range(120):
        p.stepSimulation(physicsClientId=physicsClientId)
        time.sleep(1 / 240)

    control_test(robot, physicsClientId)
    p.disconnect()


if __name__ == '__main__':
    physicsClientId = p.connect(p.GUI)
    p.configureDebugVisualizer(p.COV_ENABLE_RGB_BUFFER_PREVIEW, 0, physicsClientId=physicsClientId)
    p.configureDebugVisualizer(p.COV_ENABLE_DEPTH_BUFFER_PREVIEW, 0, physicsClientId=physicsClientId)
    p.configureDebugVisualizer(p.COV_ENABLE_SEGMENTATION_MARK_PREVIEW, 0, physicsClientId=physicsClientId)
    test_panda(physicsClientId, controlMode="position")
