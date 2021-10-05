import numpy as np
import pdb
import random
class Resampling:

    """
    References: Thrun, Sebastian, Wolfram Burgard, and Dieter Fox. Probabilistic robotics. MIT press, 2005.
    [Chapter 4.3]
    """

    def __init__(self):
        """
        TODO : Initialize resampling process parameters here
        """
    def low_variance_sampler(self, X_bar):
        """
        param[in] X_bar : [num_particles x 4] sized array containing [x, y, theta, wt] values for all particles
        param[out] X_bar_resampled : [num_particles x 4] sized array containing [x, y, theta, wt] values for resampled set of particles
        """

        X_bar_resampled = []
        
        """
        TODO : Add your code here
        """

        X_bar[:, 3] = X_bar[:, 3] / np.sum(X_bar[:, 3])
        M = X_bar.shape[0]
        r = np.random.uniform(0, 1 / M)
        c = X_bar[0][3]
        i = 0
        for m in range(M):
            U = r + m * 1 / M
            while (U > c):
                i += 1
                c += X_bar[i][3]
            X_bar_resampled.append(X_bar[i])

        X_bar_resampled = np.asarray(X_bar_resampled)
        
        return X_bar_resampled

if __name__ == "__main__":
    pass