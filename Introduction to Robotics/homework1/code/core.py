from __future__ import print_function

import numpy as np


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
RIGID-BODY MOTIONS
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

    '''-----------------------'''
    '''----Your Code HERE:----'''
    '''-----------------------'''

    return R.T


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

    '''-----------------------'''
    '''----Your Code HERE:----'''
    '''-----------------------'''

    return np.array([[0, -omg[2], omg[1]], [omg[2], 0, -omg[0]], [-omg[1], omg[0], 0]])


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

    '''-----------------------'''
    '''----Your Code HERE:----'''
    '''-----------------------'''

    return np.array([so3mat[2, 1], so3mat[0, 2], so3mat[1, 0]])


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

    '''-----------------------'''
    '''----Your Code HERE:----'''
    '''-----------------------'''

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

    '''-----------------------'''
    '''----Your Code HERE:----'''
    '''-----------------------'''

    tmp = np.linalg.eig(so3mat)
    P = tmp[1]
    P_inv = np.linalg.inv(P)
    D = np.dot(np.dot(P_inv, so3mat), P)
    for i in range(D.shape[0]):
        D[i, i] = np.exp(D[i, i])
    ans = np.dot(np.dot(P, D), P_inv)
    return np.real(ans)


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

    '''-----------------------'''
    '''----Your Code HERE:----'''
    '''-----------------------'''

    tmp = np.linalg.eig(R)
    P = tmp[1]
    P_inv = np.linalg.inv(P)
    D = np.dot(np.dot(P_inv, R), P)
    for i in range(D.shape[0]):
        D[i, i] = np.log(D[i, i])
    ans = np.dot(np.dot(P, D), P_inv)
    return np.real(ans)


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

    '''-----------------------'''
    '''----Your Code HERE:----'''
    '''-----------------------'''

    return np.array([[R[0, 0], R[0, 1], R[0, 2], p[0]],
                     [R[1, 0], R[1, 1], R[1, 2], p[1]],
                     [R[2, 0], R[2, 1], R[2, 2], p[2]],
                     [0, 0, 0, 1]])


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

    '''-----------------------'''
    '''----Your Code HERE:----'''
    '''-----------------------'''

    R = T[0:3, 0:3]
    p = T[0:3, 3]
    return (R, p)


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

    '''-----------------------'''
    '''----Your Code HERE:----'''
    '''-----------------------'''

    (R, p) = trans_to_rp(T)
    return rp_to_trans(R.T, -np.dot(R.T, p))


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

    '''-----------------------'''
    '''----Your Code HERE:----'''
    '''-----------------------'''

    p1 = V[0:3]
    p2 = V[3:6]
    tmp = rp_to_trans(vec_to_so3(p1), p2)
    tmp[3, 3] = 0
    return tmp


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

    '''-----------------------'''
    '''----Your Code HERE:----'''
    '''-----------------------'''

    (R, p2) = trans_to_rp(se3mat)
    p1 = so3_to_vec(R)
    return np.hstack((p1, p2))


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

    '''-----------------------'''
    '''----Your Code HERE:----'''
    '''-----------------------'''

    (R, p) = trans_to_rp(T)
    pR = np.dot(vec_to_so3(p), R)
    zero = np.zeros_like(R)
    return np.vstack((np.hstack((R, zero)),np.hstack((pR, R))))


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

    '''-----------------------'''
    '''----Your Code HERE:----'''
    '''-----------------------'''

    v = np.array([q[1] * s[2] - q[2] * s[1], q[2] * s[0] - q[0] * s[2], q[0] * s[1] - q[1] * s[0]]) + h * s
    return np.hstack((s, v))


def axis_ang6(expc6):
    """Converts a 6-vector of exponential coordinates into screw axis-angle
    form

    :param expc6: A 6-vector of exponential coordinates for rigid-body motion
                  S*theta
    :return S: The corresponding d screw axis
    :return theta: The distance traveled along/about S

    Example Input:
        expc6 = np.array([1, 0, 0, 1, 2, 3])
    Output:
        (np.array([1.0, 0.0, 0.0, 1.0, 2.0, 3.0]), 1.0)
    """

    '''-----------------------'''
    '''----Your Code HERE:----'''
    '''-----------------------'''

    theta = np.linalg.norm(expc6[0:3])
    if (near_zero(theta)):
        theta = np.linalg.norm(expc6[3:6])
    return (expc6 / theta, theta)


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

    '''-----------------------'''
    '''----Your Code HERE:----'''
    '''-----------------------'''

    return matrix_exp3(se3mat)


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

    '''-----------------------'''
    '''----Your Code HERE:----'''
    '''-----------------------'''

    return matrix_log3(T)


'''
*** FORWARD KINEMATICS ***
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
             in body frame

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

    '''-----------------------'''
    '''----Your Code HERE:----'''
    '''-----------------------'''

    T = []
    for i in range(Blist.shape[1]):
        theta = thetalist[i]
        w = vec_to_so3(Blist[0:3, i])
        R = matrix_exp3(w * theta)
        G = np.identity(3) * theta + w * (1 - np.cos(theta)) + np.dot(w, w) * (theta - np.sin(theta))
        p = np.dot(G, Blist[3:6, i])
        T.append(rp_to_trans(R, p))
    ans = M
    for i in range(len(T)):
        ans = np.dot(ans, T[i])
    return ans


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
             in space frame

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

    '''-----------------------'''
    '''----Your Code HERE:----'''
    '''-----------------------'''

    T = []
    for i in range(Slist.shape[1]):
        theta = thetalist[i]
        w = vec_to_so3(Slist[0:3, i])
        R = matrix_exp3(w * theta)
        G = np.identity(3) * theta + w * (1 - np.cos(theta)) + np.dot(w, w) * (theta - np.sin(theta))
        p = np.dot(G, Slist[3:6, i])
        T.append(rp_to_trans(R, p))
    ans = T[0]
    for i in range(1, len(T)):
        ans = np.dot(ans, T[i])
    return np.dot(ans, M)

