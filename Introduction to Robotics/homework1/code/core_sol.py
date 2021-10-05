from __future__ import print_function

import numpy as np

'''
basic util function
'''


def near_zero(z):
    """Determines whether a scalar is small enough to be treated as zero

    :param z: A scalar input to check
    :return: True if z is close to zero, false otherwise

    Example Input:
        z = -1e-7
    Output:
        True
    """
    return abs(z) < 1e-6


def normalize(V):
    """Normalizes a vector

    :param V: A vector
    :return: A unit vector pointing in the same direction as z

    Example Input:
        V = np.array([1, 2, 3])
    Output:
        np.array([0.26726124, 0.53452248, 0.80178373])
    """
    return V / np.linalg.norm(V)


'''
Chapter 3
'''


def rot_inv(R):
    """Inverts a rotation matrix

    :param R: A rotation matrix
    :return: The inverse of R

    Example Input:
        R = np.array([[0, 0, 1],
                      [1, 0, 0],
                      [0, 1, 0]])
    Output:
        np.array([[0, 1, 0],
                  [0, 0, 1],
                  [1, 0, 0]])
    """
    return np.array(R).T


def vec_to_so3(omg):
    """Converts a 3-vector to an so(3) representation

    :param omg: A 3-vector
    :return: The skew symmetric representation of omg

    Example Input:
        omg = np.array([1, 2, 3])
    Output:
        np.array([[ 0, -3,  2],
                  [ 3,  0, -1],
                  [-2,  1,  0]])
    """
    return np.array([[0, -omg[2], omg[1]],
                     [omg[2], 0, -omg[0]],
                     [-omg[1], omg[0], 0]])


def so3_to_vec(so3mat):
    """Converts an so(3) representation to a 3-vector

    :param so3mat: A 3x3 skew-symmetric matrix
    :return: The 3-vector corresponding to so3mat

    Example Input:
        so3mat = np.array([[ 0, -3,  2],
                           [ 3,  0, -1],
                           [-2,  1,  0]])
    Output:
        np.array([1, 2, 3])
    """
    return np.array([so3mat[2][1], so3mat[0][2], so3mat[1][0]])


def axis_ang3(expc3):
    """Converts a 3-vector of exponential coordinates for rotation into
    axis-angle form

    :param expc3: A 3-vector of exponential coordinates for rotation
    :return omghat: A unit rotation axis
    :return theta: The corresponding rotation angle

    Example Input:
        expc3 = np.array([1, 2, 3])
    Output:
        (np.array([0.26726124, 0.53452248, 0.80178373]), 3.7416573867739413)
    """
    return (normalize(expc3), np.linalg.norm(expc3))


def matrix_exp3(so3mat):
    """Computes the matrix exponential of a matrix in so(3)

    :param so3mat: A 3x3 skew-symmetric matrix
    :return: The matrix exponential of so3mat

    Example Input:
        so3mat = np.array([[ 0, -3,  2],
                           [ 3,  0, -1],
                           [-2,  1,  0]])
    Output:
        np.array([[-0.69492056,  0.71352099,  0.08929286],
                  [-0.19200697, -0.30378504,  0.93319235],
                  [ 0.69297817,  0.6313497 ,  0.34810748]])
    """
    omgtheta = so3_to_vec(so3mat)
    if near_zero(np.linalg.norm(omgtheta)):
        return np.eye(3)
    else:
        theta = axis_ang3(omgtheta)[1]
        omgmat = so3mat / theta
        return np.eye(3) + np.sin(theta) * omgmat \
               + (1 - np.cos(theta)) * np.dot(omgmat, omgmat)


def matrix_log3(R):
    """Computes the matrix logarithm of a rotation matrix

    :param R: A 3x3 rotation matrix
    :return: The matrix logarithm of R

    Example Input:
        R = np.array([[0, 0, 1],
                      [1, 0, 0],
                      [0, 1, 0]])
    Output:
        np.array([[          0, -1.20919958,  1.20919958],
                  [ 1.20919958,           0, -1.20919958],
                  [-1.20919958,  1.20919958,           0]])
    """
    acosinput = (np.trace(R) - 1) / 2.0
    if acosinput >= 1:
        return np.zeros((3, 3))
    elif acosinput <= -1:
        if not near_zero(1 + R[2][2]):
            omg = (1.0 / np.sqrt(2 * (1 + R[2][2]))) \
                  * np.array([R[0][2], R[1][2], 1 + R[2][2]])
        elif not near_zero(1 + R[1][1]):
            omg = (1.0 / np.sqrt(2 * (1 + R[1][1]))) \
                  * np.array([R[0][1], 1 + R[1][1], R[2][1]])
        else:
            omg = (1.0 / np.sqrt(2 * (1 + R[0][0]))) \
                  * np.array([1 + R[0][0], R[1][0], R[2][0]])
        return vec_to_so3(np.pi * omg)
    else:
        theta = np.arccos(acosinput)
        return theta / 2.0 / np.sin(theta) * (R - np.array(R).T)


def rp_to_trans(R, p):
    """Converts a rotation matrix and a position vector into homogeneous
    transformation matrix

    :param R: A 3x3 rotation matrix
    :param p: A 3-vector
    :return: A homogeneous transformation matrix corresponding to the inputs

    Example Input:
        R = np.array([[1, 0,  0],
                      [0, 0, -1],
                      [0, 1,  0]])
        p = np.array([1, 2, 5])
    Output:
        np.array([[1, 0,  0, 1],
                  [0, 0, -1, 2],
                  [0, 1,  0, 5],
                  [0, 0,  0, 1]])
    """
    return np.r_[np.c_[R, p], [[0, 0, 0, 1]]]


def trans_to_rp(T):
    """Converts a homogeneous transformation matrix into a rotation matrix
    and position vector

    :param T: A homogeneous transformation matrix
    :return R: The corresponding rotation matrix,
    :return p: The corresponding position vector.

    Example Input:
        T = np.array([[1, 0,  0, 0],
                      [0, 0, -1, 0],
                      [0, 1,  0, 3],
                      [0, 0,  0, 1]])
    Output:
        (np.array([[1, 0,  0],
                   [0, 0, -1],
                   [0, 1,  0]]),
         np.array([0, 0, 3]))
    """
    T = np.array(T)
    return T[0: 3, 0: 3], T[0: 3, 3]


def trans_inv(T):
    """Inverts a homogeneous transformation matrix

    :param T: A homogeneous transformation matrix
    :return: The inverse of T
    Uses the structure of transformation matrices to avoid taking a matrix
    inverse, for efficiency.

    Example input:
        T = np.array([[1, 0,  0, 0],
                      [0, 0, -1, 0],
                      [0, 1,  0, 3],
                      [0, 0,  0, 1]])
    Output:
        np.array([[1,  0, 0,  0],
                  [0,  0, 1, -3],
                  [0, -1, 0,  0],
                  [0,  0, 0,  1]])
    """
    R, p = trans_to_rp(T)
    Rt = np.array(R).T
    return np.r_[np.c_[Rt, -np.dot(Rt, p)], [[0, 0, 0, 1]]]


def vec_to_se3(V):
    """Converts a spatial velocity vector into a 4x4 matrix in se3

    :param V: A 6-vector representing a spatial velocity
    :return: The 4x4 se3 representation of V

    Example Input:
        V = np.array([1, 2, 3, 4, 5, 6])
    Output:
        np.array([[ 0, -3,  2, 4],
                  [ 3,  0, -1, 5],
                  [-2,  1,  0, 6],
                  [ 0,  0,  0, 0]])
    """
    return np.r_[np.c_[vec_to_so3([V[0], V[1], V[2]]), [V[3], V[4], V[5]]],
                 np.zeros((1, 4))]


def se3_to_vec(se3mat):
    """ Converts an se3 matrix into a spatial velocity vector

    :param se3mat: A 4x4 matrix in se3
    :return: The spatial velocity 6-vector corresponding to se3mat

    Example Input:
        se3mat = np.array([[ 0, -3,  2, 4],
                           [ 3,  0, -1, 5],
                           [-2,  1,  0, 6],
                           [ 0,  0,  0, 0]])
    Output:
        np.array([1, 2, 3, 4, 5, 6])
    """
    return np.r_[[se3mat[2][1], se3mat[0][2], se3mat[1][0]],
                 [se3mat[0][3], se3mat[1][3], se3mat[2][3]]]


def adjoint(T):
    """Computes the adjoint representation of a homogeneous transformation
    matrix

    :param T: A homogeneous transformation matrix
    :return: The 6x6 adjoint representation [AdT] of T

    Example Input:
        T = np.array([[1, 0,  0, 0],
                      [0, 0, -1, 0],
                      [0, 1,  0, 3],
                      [0, 0,  0, 1]])
    Output:
        np.array([[1, 0,  0, 0, 0,  0],
                  [0, 0, -1, 0, 0,  0],
                  [0, 1,  0, 0, 0,  0],
                  [0, 0,  3, 1, 0,  0],
                  [3, 0,  0, 0, 0, -1],
                  [0, 0,  0, 0, 1,  0]])
    """
    R, p = trans_to_rp(T)
    return np.r_[np.c_[R, np.zeros((3, 3))],
                 np.c_[np.dot(vec_to_so3(p), R), R]]


def screw_to_axis(q, s, h):
    """Takes a parametric description of a screw axis and converts it to a
    normalized screw axis

    :param q: A point lying on the screw axis
    :param s: A unit vector in the direction of the screw axis
    :param h: The pitch of the screw axis
    :return: A normalized screw axis described by the inputs

    Example Input:
        q = np.array([3, 0, 0])
        s = np.array([0, 0, 1])
        h = 2
    Output:
        np.array([0, 0, 1, 0, -3, 2])
    """
    return np.r_[s, np.cross(q, s) + np.dot(h, s)]


def axis_ang6(expc6):
    """Converts a 6-vector of exponential coordinates into screw axis-angle
    form

    :param expc6: A 6-vector of exponential coordinates for rigid-body motion
                  S*theta
    :return S: The corresponding normalized screw axis
    :return theta: The distance traveled along/about S

    Example Input:
        expc6 = np.array([1, 0, 0, 1, 2, 3])
    Output:
        (np.array([1.0, 0.0, 0.0, 1.0, 2.0, 3.0]), 1.0)
    """
    theta = np.linalg.norm([expc6[0], expc6[1], expc6[2]])
    if near_zero(theta):
        theta = np.linalg.norm([expc6[3], expc6[4], expc6[5]])
    return (np.array(expc6 / theta), theta)


def matrix_exp6(se3mat):
    """Computes the matrix exponential of an se3 representation of
    exponential coordinates

    :param se3mat: A matrix in se3
    :return: The matrix exponential of se3mat

    Example Input:
        se3mat = np.array([[0,          0,           0,          0],
                           [0,          0, -1.57079632, 2.35619449],
                           [0, 1.57079632,           0, 2.35619449],
                           [0,          0,           0,          0]])
    Output:
        np.array([[1.0, 0.0,  0.0, 0.0],
                  [0.0, 0.0, -1.0, 0.0],
                  [0.0, 1.0,  0.0, 3.0],
                  [  0,   0,    0,   1]])
    """
    se3mat = np.array(se3mat)
    omgtheta = so3_to_vec(se3mat[0: 3, 0: 3])
    if near_zero(np.linalg.norm(omgtheta)):
        return np.r_[np.c_[np.eye(3), se3mat[0: 3, 3]], [[0, 0, 0, 1]]]
    else:
        theta = axis_ang3(omgtheta)[1]
        omgmat = se3mat[0: 3, 0: 3] / theta
        return np.r_[np.c_[matrix_exp3(se3mat[0: 3, 0: 3]),
                           np.dot(np.eye(3) * theta \
                                  + (1 - np.cos(theta)) * omgmat \
                                  + (theta - np.sin(theta)) \
                                  * np.dot(omgmat, omgmat),
                                  se3mat[0: 3, 3]) / theta],
                     [[0, 0, 0, 1]]]


def matrix_log6(T):
    """Computes the matrix logarithm of a homogeneous transformation matrix

    :param R: A matrix in SE3
    :return: The matrix logarithm of R

    Example Input:
        T = np.array([[1, 0,  0, 0],
                      [0, 0, -1, 0],
                      [0, 1,  0, 3],
                      [0, 0,  0, 1]])
    Output:
        np.array([[0,          0,           0,           0]
                  [0,          0, -1.57079633,  2.35619449]
                  [0, 1.57079633,           0,  2.35619449]
                  [0,          0,           0,           0]])
    """
    R, p = trans_to_rp(T)
    omgmat = matrix_log3(R)
    if np.array_equal(omgmat, np.zeros((3, 3))):
        return np.r_[np.c_[np.zeros((3, 3)),
                           [T[0][3], T[1][3], T[2][3]]],
                     [[0, 0, 0, 0]]]
    else:
        theta = np.arccos((np.trace(R) - 1) / 2.0)
        return np.r_[np.c_[omgmat,
                           np.dot(np.eye(3) - omgmat / 2.0 \
                                  + (1.0 / theta - 1.0 / np.tan(theta / 2.0) / 2) \
                                  * np.dot(omgmat, omgmat) / theta, [T[0][3],
                                                                     T[1][3],
                                                                     T[2][3]])],
                     [[0, 0, 0, 0]]]


'''
*** CHAPTER 4: FORWARD KINEMATICS ***
'''


def FK_in_body(M, Blist, thetalist):
    """Computes forward kinematics in the body frame for an open chain robot

    :param M: The home configuration (position and orientation) of the end-
              effector
    :param Blist: The joint screw axes in the end-effector frame when the
                  manipulator is at the home position, in the format of a
                  matrix with axes as the columns
    :param thetalist: A list of joint coordinates
    :return: A homogeneous transformation matrix representing the end-
             effector frame when the joints are at the specified coordinates
             (i.t.o Body Frame)

    Example Input:
        M = np.array([[-1, 0,  0, 0],
                      [ 0, 1,  0, 6],
                      [ 0, 0, -1, 2],
                      [ 0, 0,  0, 1]])
        Blist = np.array([[0, 0, -1, 2, 0,   0],
                          [0, 0,  0, 0, 1,   0],
                          [0, 0,  1, 0, 0, 0.1]]).T
        thetalist = np.array([np.pi / 2.0, 3, np.pi])
    Output:
        np.array([[0, 1,  0,         -5],
                  [1, 0,  0,          4],
                  [0, 0, -1, 1.68584073],
                  [0, 0,  0,          1]])
    """
    T = np.array(M)
    for i in range(len(thetalist)):
        T = np.dot(T, matrix_exp6(vec_to_se3(np.array(Blist)[:, i] \
                                             * thetalist[i])))
    return T


def FK_in_space(M, Slist, thetalist):
    """Computes forward kinematics in the space frame for an open chain robot

    :param M: The home configuration (position and orientation) of the end-
              effector
    :param Slist: The joint screw axes in the space frame when the
                  manipulator is at the home position, in the format of a
                  matrix with axes as the columns
    :param thetalist: A list of joint coordinates
    :return: A homogeneous transformation matrix representing the end-
             effector frame when the joints are at the specified coordinates
             (i.t.o Space Frame)

    Example Input:
        M = np.array([[-1, 0,  0, 0],
                      [ 0, 1,  0, 6],
                      [ 0, 0, -1, 2],
                      [ 0, 0,  0, 1]])
        Slist = np.array([[0, 0,  1,  4, 0,    0],
                          [0, 0,  0,  0, 1,    0],
                          [0, 0, -1, -6, 0, -0.1]]).T
        thetalist = np.array([np.pi / 2.0, 3, np.pi])
    Output:
        np.array([[0, 1,  0,         -5],
                  [1, 0,  0,          4],
                  [0, 0, -1, 1.68584073],
                  [0, 0,  0,          1]])
    """
    T = np.array(M)
    for i in range(len(thetalist) - 1, -1, -1):
        T = np.dot(matrix_exp6(vec_to_se3(np.array(Slist)[:, i] \
                                          * thetalist[i])), T)
    return T
