# -*- coding: utf-8 -*-
# @Author : zhux
# @Email : zhu-x21@mails.tsinghua.edu.cn

import os, time, copy, math
import numpy as np
import pybullet_data
import pybullet as p
from core import *


# Tool functions
def getJointStates(robot):
    joint_states = p.getJointStates(robot, range(p.getNumJoints(robot)))
    joint_positions = [state[0] for state in joint_states]
    joint_velocities = [state[1] for state in joint_states]
    joint_torques = [state[3] for state in joint_states]
    return np.array(joint_positions), joint_velocities, joint_torques


def torque_action_filter(action, filter_index):
    new_action = []
    for i in filter_index:
        new_action.append(action[i])
    return new_action


def step_sim(t, physicsClientId):
    """
    step the simulation
    :param t: time (in second)
    :param physicsClientId:
    :return: none
    """
    T = t * 240
    for _ in range(int(T)):
        p.stepSimulation(physicsClientId=physicsClientId)
        time.sleep(1 / 240)


initial_pos_list = [0, np.deg2rad(-60), 0, np.deg2rad(-150), 0, np.deg2rad(90), np.deg2rad(45), 0.02, 0.02]


class pandaEnv():
    initial_positions = {
        'panda_joint1': 0.0, 'panda_joint2': np.deg2rad(-60), 'panda_joint3': 0.0,
        'panda_joint4': np.deg2rad(-150), 'panda_joint5': 0.0, 'panda_joint6': np.deg2rad(90),
        'panda_joint7': np.deg2rad(45), 'panda_finger_joint1': 0.02, 'panda_finger_joint2': 0.02,
    }

    # initial_pos_list = [0, np.deg2rad(-60), 0, np.deg2rad(-150), 0, np.deg2rad(90), np.deg2rad(45), 0.02, 0.02]
    # initial_positions = {
    #     'panda_joint1': 0.0, 'panda_joint2': 0.0, 'panda_joint3': 0.0,
    #     'panda_joint4': 0.0, 'panda_joint5': 0.0, 'panda_joint6': 0.0,
    #     'panda_joint7': 0.0, 'panda_finger_joint1': 0.02, 'panda_finger_joint2': 0.02,
    # }
    # initial_pos_list = [0, 0, 0, 0, 0, 0, 0, 0.02, 0.02]

    def __init__(self, physicsClientId, base_position=(0.0, 0.0, 0.0), control_orientation=1,
                 control_eu_or_quat=0, joint_action_space=7, maxJointVel=0.52, controlMode="position"):

        self._physics_client_id = physicsClientId  # physicsClient = p.connect(p.GUI) or p.DIRECT for non-graphical
        self._use_IK = 0  # use_IK  # action space = cartesian if use_ik else joint
        self._control_orientation = control_orientation  # in cartesian action space, whether control the rotation
        self._base_position = base_position  # robot's base position

        self.joint_action_space = joint_action_space  # 7 DoF for manipulator + 9 DoF for gripper + manipulator

        self._control_eu_or_quat = control_eu_or_quat  # if control in cartesian space, use euler angle (0) or quaternion (1)
        self._control_mode = controlMode  # position or velocity or torque

        self._workspace_lim = [[0.1, 0.855], [-0.5, 0.5], [base_position[2], base_position[2] + 1.190]]
        self._eu_lim = [[-math.pi, math.pi], [-math.pi, math.pi], [-math.pi, math.pi]]
        self._jvel_lim = maxJointVel

        self.end_eff_idx = 11  # 8

        self._home_hand_pose = []

        self._num_dof = 7
        self._joint_name_to_ids = {}
        self.robot_id = None
        self._cal_screw_axis_flag = False
        self.transforms_world2joint_home_pos = None  # list of transforms from space(world) frame to each joint frame
        self.screw_axis_home_pos = None  # list of screw axis in the space frame
        self.end_eff_home_trans = None  # end effector home configuration in space frame
        self.torque_limits = []
        self.time_step = 1.0 / 240
        self.controllable_joints = [0, 1, 2, 3, 4, 5, 6]

        # bin
        self.bin_id = []

        # objects
        self._obj_init_pose = [0.4, -0.3, 0.03, 0, 0, 0, 1]
        self.obj_id = None

        self.init()

    def init(self):
        """
        init etc
        :return:
        """
        p.loadURDF(os.path.join(pybullet_data.getDataPath(), "plane.urdf"), [0, 0, 0],
                   physicsClientId=self._physics_client_id)

        # load gray bin
        # self.load_bin(bin_pose=[0.4, -0.3, 0.005 / 2], rgba_color=[0.5, 0.5, 0.5, 1])
        # load blue bin
        # self.load_bin(bin_pose=[0.4, 0.3, 0.005 / 2], rgba_color=[0, 0, 1, 1])
        # self.load_lego()
        flags = p.URDF_ENABLE_CACHED_GRAPHICS_SHAPES | p.URDF_USE_INERTIA_FROM_FILE | p.URDF_USE_SELF_COLLISION
        robot_file_path = os.path.join(os.getcwd(), "robot_model/franka_panda/panda_model.urdf")
        self.robot_id = p.loadURDF(robot_file_path,
                                   basePosition=self._base_position, useFixedBase=True, flags=flags,
                                   physicsClientId=self._physics_client_id)

        assert self.robot_id is not None, "Failed to load the panda model"
        self.reset()
        self.ll, self.ul, self.jr, self.rs = self.get_joint_ranges()
        self.transforms_world2joint_home_pos, self.screw_axis_home_pos = self.compute_screw_axis()
        self.end_eff_home_trans = self.compute_Mlist()[0]

    def set_control_mode(self, mode="position"):
        if mode == "position":
            self._control_mode = mode
        elif mode == "velocity":
            self._control_mode = mode
        elif mode == "torque":
            self._control_mode = mode
        else:
            raise NotImplementedError("Only \'position\', \'velocity\' and \'torque\' control mode is available")

    def reset(self):
        """
        reset joints to home/initial position and set joints to expected control mode
        :return: none
        """
        num_joints = p.getNumJoints(self.robot_id, physicsClientId=self._physics_client_id)
        idx = 0
        for i in range(num_joints):
            joint_info = p.getJointInfo(self.robot_id, i, physicsClientId=self._physics_client_id)
            joint_name = joint_info[1].decode("UTF-8")
            joint_type = joint_info[2]

            if joint_type is p.JOINT_REVOLUTE or joint_type is p.JOINT_PRISMATIC:
                assert joint_name in self.initial_positions.keys()

                self._joint_name_to_ids[joint_name] = i

                p.resetJointState(self.robot_id, i, self.initial_positions[joint_name],
                                  physicsClientId=self._physics_client_id)
                if self._control_mode == "torque" and p.JOINT_REVOLUTE:
                    # only apply torque control for revolute joint
                    p.setJointMotorControl2(self.robot_id,
                                            i,
                                            p.VELOCITY_CONTROL,
                                            force=0)
                else:
                    p.setJointMotorControl2(self.robot_id, i, p.POSITION_CONTROL,
                                            targetPosition=self.initial_positions[joint_name],
                                            positionGain=0.2, velocityGain=1.0,
                                            physicsClientId=self._physics_client_id)

                idx += 1

        if self._use_IK and self._control_mode == "position":
            self._home_hand_pose = [0.240, 0.0, 1.093,
                                    min(math.pi, max(-math.pi, math.pi)),
                                    min(math.pi, max(-math.pi, 0)),
                                    min(math.pi, max(-math.pi, 0))]

            self.apply_action(self._home_hand_pose)
            p.stepSimulation(physicsClientId=self._physics_client_id)
        self._cal_screw_axis_flag = True

    def load_bin(self, bin_pose=[0.48, 0.0, 0.005 / 2], rgba_color=[0.5, 0.5, 0.5, 1], x_length=0.3, y_length=0.3,
                 z_length=0.15, fix_base=True):
        baseMass = 0 if fix_base else 1

        pos1 = [x_length / 2, 0.0, z_length / 2]
        pos2 = [0.0, y_length / 2, z_length / 2]
        pos3 = [-x_length / 2, 0.0, z_length / 2]
        pos4 = [0.0, -y_length / 2, z_length / 2]
        pos5 = [0.0, 0.0, 0.0]
        meshScale = [1, 1, 1]
        # bin_pose
        self.obj_pose_lim = [[bin_pose[0] - x_length / 2, bin_pose[0] + x_length / 2],
                             [bin_pose[1] - y_length / 2, bin_pose[1] + y_length / 2],
                             [0.005, bin_pose[2] + z_length]]

        visualShapeId = p.createVisualShapeArray(shapeTypes=[p.GEOM_BOX] * 5,
                                                 halfExtents=[[0.005, y_length / 2, z_length / 2],
                                                              [x_length / 2, 0.005, z_length / 2],
                                                              [0.005, y_length / 2, z_length / 2],
                                                              [x_length / 2, 0.005, z_length / 2],
                                                              [(x_length + 0.01) / 2, (y_length + 0.01) / 2, 0.005]],
                                                 visualFramePositions=[pos1, pos2, pos3, pos4, pos5],
                                                 meshScales=[meshScale, meshScale, meshScale, meshScale, meshScale])
        collisionShapeId = p.createCollisionShapeArray(shapeTypes=[p.GEOM_BOX] * 5,
                                                       halfExtents=[[0.005, y_length / 2, z_length / 2],
                                                                    [x_length / 2, 0.005, z_length / 2],
                                                                    [0.005, y_length / 2, z_length / 2],
                                                                    [x_length / 2, 0.005, z_length / 2],
                                                                    [(x_length + 0.01) / 2, (y_length + 0.01) / 2,
                                                                     0.005]],
                                                       collisionFramePositions=[pos1, pos2, pos3, pos4, pos5],
                                                       meshScales=[meshScale, meshScale, meshScale, meshScale,
                                                                   meshScale])

        id = p.createMultiBody(baseMass=baseMass,
                               baseCollisionShapeIndex=collisionShapeId,
                               baseVisualShapeIndex=visualShapeId,
                               basePosition=bin_pose,
                               baseInertialFramePosition=[0, 0, 0],
                               useMaximalCoordinates=False,
                               physicsClientId=self._physics_client_id)
        p.changeVisualShape(id, -1, rgbaColor=rgba_color)
        self.bin_id.append(id)

    def load_lego(self):
        # Load object. Randomize its start position if requested
        # TODO: may generate at a random pose
        # self._obj_init_pose = self._sample_pose()
        self.obj_id = p.loadURDF(os.path.join(pybullet_data.getDataPath(), "lego", "lego.urdf"),
                                 basePosition=self._obj_init_pose[:3], baseOrientation=self._obj_init_pose[3:7],
                                 physicsClientId=self._physics_client_id)

    def load_env(self):
        # load gray bin
        self.load_bin(bin_pose=[0.4, -0.3, 0.005 / 2], rgba_color=[0.5, 0.5, 0.5, 1])
        # load blue bin
        self.load_bin(bin_pose=[0.4, 0.3, 0.005 / 2], rgba_color=[0, 0, 1, 1])
        self.load_lego()

    def remove_env(self):
        self.delete_object(self.obj_id)
        for bin in self.bin_id:
            self.delete_object(bin)

    def delete_object(self):
        p.removeBody(self.obj_id, physicsClientId=self._physics_client_id)

    def get_obj_info(self):
        obj_pos, obj_quaternion = p.getBasePositionAndOrientation(self.obj_id, physicsClientId=self._physics_client_id)
        return np.array(obj_pos), p.getMatrixFromQuaternion(obj_quaternion)

    def get_end_eff_home_trans(self):
        return self.end_eff_home_trans

    def get_transforms_world2joint(self):
        return self.transforms_world2joint_home_pos

    def get_screw_axis(self):
        return self.screw_axis_home_pos

    def delete_simulated_robot(self):
        p.removeBody(self.robot_id, physicsClientId=self._physics_client_id)

    def get_joint_ranges(self):
        """
        get joint limits form URDF
        :return: lower_limits, upper_limits, joint_ranges, rest_poses
        """
        lower_limits, upper_limits, joint_ranges, rest_poses = [], [], [], []

        for joint_name in self._joint_name_to_ids.keys():
            jointInfo = p.getJointInfo(self.robot_id, self._joint_name_to_ids[joint_name],
                                       physicsClientId=self._physics_client_id)

            ll = jointInfo[8]
            ul = jointInfo[9]
            jr = ul - ll
            # For simplicity, assume resting state == initial state
            rp = self.initial_positions[joint_name]
            lower_limits.append(ll)
            upper_limits.append(ul)
            joint_ranges.append(jr)
            rest_poses.append(rp)
            self.torque_limits.append(jointInfo[10])

        self.vul, self.vll = [2.62] * 7 + [0.08] * 2, [-2.62] * 7 + [-0.08] * 2

        return lower_limits, upper_limits, joint_ranges, rest_poses

    def get_joint_action_ranges(self):
        """
        get the joint ranges send to apply_action function
        has already compensate for the manmade zero adjustment of the home position
        :return:
        """
        lower_limits = [self.ll[i] - initial_pos_list[i] for i in range(self.joint_action_space)]
        upper_limits = [self.ul[i] - initial_pos_list[i] for i in range(self.joint_action_space)]
        return lower_limits, upper_limits, self.jr, self.rs

    def get_action_dim(self):
        if not self._use_IK:  # joint space control
            return self.joint_action_space

        if self._control_orientation and self._control_eu_or_quat == 0:
            return 6  # position x,y,z + roll/pitch/yaw of hand frame

        elif self._control_orientation and self._control_eu_or_quat == 1:
            return 7  # position x,y,z + quat of hand frame

        return 3  # position x,y,z

    def get_workspace(self):
        return [i[:] for i in self._workspace_lim]

    def set_workspace(self, ws):
        self._workspace_lim = [i[:] for i in ws]

    def get_rotation_lim(self):
        return [i[:] for i in self._eu_lim]

    def set_rotation_lim(self, eu):
        self._eu_lim = [i[:] for i in eu]

    def pre_grasp(self):
        self.apply_action_fingers([0.04, 0.04])

    def grasp(self, obj_id=None):
        self.apply_action_fingers([0.0, 0.0], obj_id)

    def apply_action_fingers(self, action, obj_id=None):
        # move finger joints in position control
        assert len(action) == 2, ('finger joints are 2! The number of actions you passed is ', len(action))

        idx_fingers = [self._joint_name_to_ids['panda_finger_joint1'], self._joint_name_to_ids['panda_finger_joint2']]

        # use object id to check contact force and eventually stop the finger motion
        if obj_id is not None:
            _, forces = self.check_contact_fingertips(obj_id)
            # print("contact forces {}".format(forces))

            if forces[0] >= 20.0:
                action[0] = p.getJointState(self.robot_id, idx_fingers[0], physicsClientId=self._physics_client_id)[0]

            if forces[1] >= 20.0:
                action[1] = p.getJointState(self.robot_id, idx_fingers[1], physicsClientId=self._physics_client_id)[0]

        for i, idx in enumerate(idx_fingers):
            p.setJointMotorControl2(self.robot_id,
                                    idx,
                                    p.POSITION_CONTROL,
                                    targetPosition=action[i],
                                    force=10,
                                    maxVelocity=1,
                                    physicsClientId=self._physics_client_id)

    def position_cartesian_control(self, action, max_vel=-1):
        assert len(action) == self.joint_action_space, (
            'use your_own_IK and then apply_action!', len(action))

    def position_joint_control(self, action, max_vel=-1):
        assert len(action) == self.joint_action_space, (
            'number of motor commands differs from number of motor to control', len(action))

        joint_idxs = tuple(self._joint_name_to_ids.values())
        for i, val in enumerate(action):
            motor = joint_idxs[i]
            joint_info = p.getJointInfo(self.robot_id, motor,
                                        physicsClientId=self._physics_client_id)
            if self.joint_action_space is 7 and joint_info[2] is not p.JOINT_REVOLUTE:
                continue
            new_motor_pos = min(self.ul[i], max(self.ll[i], val))
            if max_vel == -1:
                p.setJointMotorControl2(self.robot_id,
                                        motor,
                                        p.POSITION_CONTROL,
                                        targetPosition=new_motor_pos,
                                        positionGain=0.5, velocityGain=1.0,
                                        physicsClientId=self._physics_client_id, )
            else:
                p.setJointMotorControl2(self.robot_id,
                                        motor,
                                        p.POSITION_CONTROL,
                                        targetPosition=new_motor_pos,
                                        positionGain=0.5, velocityGain=1.0,
                                        physicsClientId=self._physics_client_id,
                                        maxVelocity=max_vel)

    def velocity_cartesian_control(self, action, max_vel=-1):
        raise NotImplementedError("Position velocity control not implemented!")

    def velocity_joint_control(self, action, max_vel=-1):
        assert len(action) == self.joint_action_space, (
            'number of motor commands differs from number of motor to control', len(action))

        joint_idxs = tuple(self._joint_name_to_ids.values())
        for i, val in enumerate(action):
            motor = joint_idxs[i]
            joint_info = p.getJointInfo(self.robot_id, motor,
                                        physicsClientId=self._physics_client_id)
            if self.joint_action_space is 7 and joint_info[2] is not p.JOINT_REVOLUTE:
                continue
            new_motor_vel = min(self.vul[i], max(self.vll[i], val))

            p.setJointMotorControl2(self.robot_id,
                                    motor,
                                    p.VELOCITY_CONTROL,
                                    targetVelocity=new_motor_vel,
                                    positionGain=0.5, velocityGain=1.0,
                                    physicsClientId=self._physics_client_id)

    def torque_joint_control(self, action):
        assert len(action) == self.joint_action_space, (
            'number of motor commands differs from number of motor to control', len(action))
        joint_idxs = tuple(self._joint_name_to_ids.values())
        for i, val in enumerate(action):
            motor = joint_idxs[i]
            joint_info = p.getJointInfo(self.robot_id, motor,
                                        physicsClientId=self._physics_client_id)
            if self.joint_action_space is 7 and joint_info[2] is not p.JOINT_REVOLUTE:
                continue
            new_motor_torque = min(self.torque_limits[i], max(-self.torque_limits[i], val))
            p.setJointMotorControl2(self.robot_id, motor, controlMode=p.VELOCITY_CONTROL, force=0,
                                    physicsClientId=self._physics_client_id)
            p.setJointMotorControl2(self.robot_id,
                                    motor,
                                    p.TORQUE_CONTROL,
                                    force=new_motor_torque,
                                    physicsClientId=self._physics_client_id)

    def apply_action(self, action, max_vel=-1):
        """
        function to control the robot
        :param action: input param
        :param max_vel: max vel
        :return: none
        """
        # compensate for the manmade zero adjustment of the home position
        action = [action[i] + initial_pos_list[i] for i in range(self.joint_action_space)]
        if self._control_mode == "position":
            if self._use_IK:
                # ---------------------------------- #
                # --- Cartesian position control --- #
                # ---------------------------------- #
                self.position_cartesian_control(action, max_vel)
            else:
                # ------------------------------ #
                # --- Joint position control --- #
                # ------------------------------ #
                self.position_joint_control(action, max_vel)
        elif self._control_mode == "velocity":
            if self._use_IK:
                # ---------------------------------- #
                # --- Cartesian velocity control --- #
                # ---------------------------------- #
                self.velocity_cartesian_control(action, max_vel)
            else:
                # ------------------------------ #
                # --- Joint velocity control --- #
                # ------------------------------ #
                self.velocity_joint_control(action, max_vel)
        elif self._control_mode == "torque":
            if self._use_IK:
                # ---------------------------------- #
                # --- Cartesian torque control --- #
                # ---------------------------------- #
                raise NotImplementedError("Torque control not implemented!")
            else:
                # ------------------------------ #
                # --- Joint torque control --- #
                # ------------------------------ #
                self.torque_joint_control(action)

    def check_collision(self, obj_id):
        """
        check collision
        :param obj_id: the obj need to be check
        :return: True / False
        """
        # check if there is any collision with an object
        contact_pts = p.getContactPoints(obj_id, self.robot_id, physicsClientId=self._physics_client_id)

        # check if the contact is on the fingertip(s)
        n_fingertips_contact, _ = self.check_contact_fingertips(obj_id)

        return (len(contact_pts) - n_fingertips_contact) > 0

    def check_contact_fingertips(self, obj_id):
        """
        check if there is any contact on the internal part of the fingers, to control if they are correctly touching an object
        :param obj_id:
        :return:
        """
        idx_fingers = [self._joint_name_to_ids['panda_finger_joint1'], self._joint_name_to_ids['panda_finger_joint2']]

        p0 = p.getContactPoints(obj_id, self.robot_id, linkIndexB=idx_fingers[0],
                                physicsClientId=self._physics_client_id)
        p1 = p.getContactPoints(obj_id, self.robot_id, linkIndexB=idx_fingers[1],
                                physicsClientId=self._physics_client_id)

        p0_contact = 0
        p0_f = [0]
        if len(p0) > 0:
            # get cartesian position of the finger link frame in world coordinates
            w_pos_f0 = p.getLinkState(self.robot_id, idx_fingers[0], physicsClientId=self._physics_client_id)[4:6]
            f0_pos_w = p.invertTransform(w_pos_f0[0], w_pos_f0[1])

            for pp in p0:
                # compute relative position of the contact point wrt the finger link frame
                f0_pos_pp = p.multiplyTransforms(f0_pos_w[0], f0_pos_w[1], pp[6], f0_pos_w[1])

                # check if contact in the internal part of finger
                if f0_pos_pp[0][1] <= 0.001 and f0_pos_pp[0][2] < 0.055 and pp[8] > -0.005:
                    p0_contact += 1
                    p0_f.append(pp[9])

        p0_f_mean = np.mean(p0_f)

        p1_contact = 0
        p1_f = [0]
        if len(p1) > 0:
            w_pos_f1 = p.getLinkState(self.robot_id, idx_fingers[1], physicsClientId=self._physics_client_id)[4:6]
            f1_pos_w = p.invertTransform(w_pos_f1[0], w_pos_f1[1])

            for pp in p1:
                # compute relative position of the contact point wrt the finger link frame
                f1_pos_pp = p.multiplyTransforms(f1_pos_w[0], f1_pos_w[1], pp[6], f1_pos_w[1])

                # check if contact in the internal part of finger
                if f1_pos_pp[0][1] >= -0.001 and f1_pos_pp[0][2] < 0.055 and pp[8] > -0.005:
                    p1_contact += 1
                    p1_f.append(pp[9])

        p1_f_mean = np.mean(p0_f)

        return (p0_contact > 0) + (p1_contact > 0), (p0_f_mean, p1_f_mean)

    def debug_gui(self):
        """
        Adding some debug line
        :return: none
        """
        p.addUserDebugLine([0, 0, 0], [0.1, 0, 0], [1, 0, 0], parentObjectUniqueId=self.robot_id,
                           parentLinkIndex=-1, physicsClientId=self._physics_client_id)
        p.addUserDebugLine([0, 0, 0], [0, 0.1, 0], [0, 1, 0], parentObjectUniqueId=self.robot_id,
                           parentLinkIndex=-1, physicsClientId=self._physics_client_id)
        p.addUserDebugLine([0, 0, 0], [0, 0, 0.1], [0, 0, 1], parentObjectUniqueId=self.robot_id,
                           parentLinkIndex=-1, physicsClientId=self._physics_client_id)

        p.addUserDebugLine([0, 0, 0], [0.1, 0, 0], [1, 0, 0], parentObjectUniqueId=self.robot_id,
                           parentLinkIndex=self.end_eff_idx, physicsClientId=self._physics_client_id)
        p.addUserDebugLine([0, 0, 0], [0, 0.1, 0], [0, 1, 0], parentObjectUniqueId=self.robot_id,
                           parentLinkIndex=self.end_eff_idx, physicsClientId=self._physics_client_id)
        p.addUserDebugLine([0, 0, 0], [0, 0, 0.1], [0, 0, 1], parentObjectUniqueId=self.robot_id,
                           parentLinkIndex=self.end_eff_idx, physicsClientId=self._physics_client_id)

    def compute_screw_axis(self):
        """
        IMPORTANT: only CAN call when the robot has reset!
        Calculate the screw axis of the ith joint expressed in the space frame when the manipulator is at the zero position.

        NOTE: using get_screw_axis() to get the screw axis is recommended.
        :return: (transforms_world2joint, screw_axis)
            transforms_world2joint: list of transforms from space(world) frame to each joint frame
            screw_axis: list screw axis in the space frame
        """
        transforms_world2joint = []
        screw_axis = []
        assert self._cal_screw_axis_flag is True, 'only CAN call when the robot has reset!'

        for joint_idx in range(0, p.getNumJoints(self.robot_id, physicsClientId=self._physics_client_id)):
            joint_info = p.getJointInfo(self.robot_id, joint_idx, physicsClientId=self._physics_client_id)
            joint_type = joint_info[2]
            joint_axis = np.array(joint_info[-4])
            if joint_type is not p.JOINT_REVOLUTE:
                continue
            # link_state = p.getLinkState(self.robot_id, joint_idx, computeForwardKinematics=True,
            #                              physicsClientId=self._physics_client_id)
            link_state = p.getLinkState(self.robot_id, joint_idx, physicsClientId=self._physics_client_id)
            R_w2l = np.array(p.getMatrixFromQuaternion(link_state[5])).reshape(3, 3)
            P_w2l = np.array(link_state[4])
            T_w2l = rp_to_trans(R_w2l, P_w2l)

            T_w2j = T_w2l
            transforms_world2joint.append(T_w2j)
            R_w2j, P_w2j = trans_to_rp(T_w2j)
            omg = np.dot(R_w2j, joint_axis)
            # v = np.cross(-omg, P_w2j)
            v = np.cross(P_w2j, omg)
            screw_axis.append(np.concatenate((omg, v), axis=0))
        self._cal_screw_axis_flag = False
        return transforms_world2joint, screw_axis

    def compute_Mlist(self, index=[11]):
        """
        compute the configuration of link frame i in space frame
        11 refer to the end effector
        :param index: a list of index need to compute
        :return: list of M
        """
        Mlist = []
        for i in index:
            if i is -1:
                # base_state = p.getBasePositionAndOrientation(self.robot_id, physicsClientId=self._physics_client_id)
                R_w2l = np.array(np.diag([1, 1, 1]))
                P_w2l = np.array(self._base_position)
            else:
                link_state = p.getLinkState(self.robot_id, i, physicsClientId=self._physics_client_id)
                R_w2l = np.array(p.getMatrixFromQuaternion(link_state[5])).reshape(3, 3)
                P_w2l = np.array(link_state[4])
            T_w2l = rp_to_trans(R_w2l, P_w2l)
            Mlist.append(T_w2l)
        return Mlist

    def cal_eff_trans(self):
        return self.compute_Mlist()[0]
