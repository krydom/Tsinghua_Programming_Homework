# -*- coding: utf-8 -*-
# @Author : zhux
# @Email : zhu-x21@mails.tsinghua.edu.cn

import os, time, copy, math
import numpy as np
import pybullet_data
import pybullet as p
from core import *
from robot_env import *


# Some test func
def FK_test(robot, physicsClientId):
    print("\n---Start FK Demo---")
    robot.set_control_mode("position")
    screw_axis = robot.get_screw_axis()
    M = robot.get_end_eff_home_trans()

    # u can also play around with those joint values

    # NOTE: need to minus the initial pos because the "zero point" for each joint may not be the ture 0
    action_test1 = [0.7, 0.9, -0.0950477, -0.7, 0, 0.5, 0.5]
    action_test1 = [action_test1[i] - initial_pos_list[i] for i in range(7)]

    # action_test2: The initial joint value has been subtracted
    action_test2 = [0.1, 0.1, -0.12950477, 0.3, 0, 0.3, 0.3]

    # apply the action and step the simulation
    # Note1: call robot.get_joint_action_ranges() can get the action's limit(this considered the man-made zero point)
    # Note2: call robot.get_joint_ranges() get the true joint limits
    robot.apply_action(action_test1, max_vel=1)
    step_sim(2, physicsClientId)

    # do Forward Kinematics
    M_fk = FK_in_space(M, np.array(screw_axis).T, np.array(action_test1))
    print("---Forward Kinematics res---")
    print(M_fk)
    # get the robot's end effector pose from the simulation
    M_eff = robot.cal_eff_trans()
    print("---true eff pos---")
    print(M_eff)
    print("---the above result need to be close enough---")
    print("--finish FK_test---\n")


def test_panda(physicsClientId, controlMode="position"):
    # create robot
    robot = pandaEnv(physicsClientId, controlMode=controlMode)
    p.setGravity(0, 0, -9.8, physicsClientId=physicsClientId)

    robot.debug_gui()
    robot.pre_grasp()

    for _ in range(120):
        p.stepSimulation(physicsClientId=physicsClientId)
        time.sleep(1 / 240)
    # pos, vel, torque = getJointStates(robot.robot_id)

    FK_test(robot, physicsClientId)
    while (1):
        p.stepSimulation(physicsClientId)


if __name__ == '__main__':
    physicsClientId = p.connect(p.GUI)
    p.configureDebugVisualizer(p.COV_ENABLE_RGB_BUFFER_PREVIEW, 0, physicsClientId=physicsClientId)
    p.configureDebugVisualizer(p.COV_ENABLE_DEPTH_BUFFER_PREVIEW, 0, physicsClientId=physicsClientId)
    p.configureDebugVisualizer(p.COV_ENABLE_SEGMENTATION_MARK_PREVIEW, 0, physicsClientId=physicsClientId)
    test_panda(physicsClientId, controlMode="position")

