from MotionModel import MotionModel
from Resampling import Resampling
from SensorModel import SensorModel
from MapReader import MapReader
import os
import numpy as np

def motion_test(motionmodel: MotionModel):
    motion_list = os.listdir('../data/motiondata')
    num_motions = len(motion_list)
    num_correct = 0
    for motion_dir in motion_list:
        u_t0 = np.load('../data/motiondata/'+motion_dir+'/u_t0.npy')
        u_t1 = np.load('../data/motiondata/'+motion_dir+'/u_t1.npy')
        x_t0 = np.load('../data/motiondata/'+motion_dir+'/x_t0.npy')
        x_t1 = np.load('../data/motiondata/'+motion_dir+'/x_t1.npy')
        np.random.seed(0)
        x_t1_pred = motionmodel.update(u_t0, u_t1, x_t0)
        delta_x_t1 = x_t1_pred - x_t1
        err_rate = np.abs(delta_x_t1 / x_t1)
        # print(err_rate)
        if (err_rate < 0.05).all():
            num_correct += 1
        else:
            os.mkdir('../failures/motiondata/'+motion_dir)
            np.save('../failures/motiondata/'+motion_dir+'/u_t0.npy', u_t0)
            np.save('../failures/motiondata/'+motion_dir+'/u_t1.npy', u_t1)
            np.save('../failures/motiondata/'+motion_dir+'/x_t0.npy', x_t0)
            np.save('../failures/motiondata/'+motion_dir+'/x_t1.npy', x_t1)

    return num_correct, num_motions

def sensor_test(sensormodel: SensorModel):
    sensor_list = os.listdir('../data/sensordata')
    num_sensors = len(sensor_list)
    num_correct = 0
    for sensor_dir in sensor_list:
        z_t1_arr = np.load('../data/sensordata/'+sensor_dir+'/z_t1_arr.npy')
        x_t1 = np.load('../data/sensordata/'+sensor_dir+'/x_t1.npy')
        expq = np.load('../data/sensordata/'+sensor_dir+'/expq.npy')
        np.random.seed(0)
        expq_pred = sensormodel.beam_range_finder_model(z_t1_arr, x_t1)
        delta_expq = expq_pred - expq
        err_rate = np.abs(delta_expq / expq)
        if (err_rate < 0.1).all():
            num_correct += 1
        else:
            os.mkdir('../failures/sensordata/'+sensor_dir)
            np.save('../failures/sensordata/'+sensor_dir+'/z_t1_arr.npy', z_t1_arr)
            np.save('../failures/sensordata/'+sensor_dir+'/x_t1.npy', x_t1)
            np.save('../failures/sensordata/'+sensor_dir+'/expq.npy', expq)
    
    return num_correct, num_sensors

def resample_test(resampling: Resampling):
    resample_list = os.listdir('../data/resampledata')
    num_resamples = len(resample_list)
    num_correct = 0
    for resample_dir in resample_list:
        X_bar = np.load('../data/resampledata/'+resample_dir+'/X_bar.npy')
        X_bar_resampled = np.load('../data/resampledata/'+resample_dir+'/X_bar_resampled.npy')
        np.random.seed(0)
        X_bar_pred = resampling.low_variance_sampler(X_bar)
        err = X_bar_pred - X_bar_resampled
        if np.linalg.norm(err) / np.linalg.norm(X_bar_resampled) < 0.01:
            num_correct += 1
        else:
            os.mkdir('../failures/resampledata/'+resample_dir)
            np.save('../failures/resampledata/'+resample_dir+'/X_bar.npy', X_bar)
            np.save('../failures/resampledata/'+resample_dir+'/X_bar_resampled.npy', X_bar_resampled)
    
    return num_correct, num_resamples

def main():
    src_path_map = '../data/map/wean.dat'
    map_obj = MapReader(src_path_map)
    occupancy_map = map_obj.get_map() 
    motionmodel = MotionModel()
    sensormodel = SensorModel(occupancy_map)
    resampling = Resampling()

    print('=======================================')
    print('|Test motion model...                 |')
    motion_correct, motion_num = motion_test(motionmodel)
    print('|                                     |')
    print('|Number of samples: {:5}             |'.format(motion_num))
    print('|Correct samples: {:5}               |'.format(motion_correct))
    print('|                                     |')
    print('|Grading: {:5}                       |'.format(round(motion_correct / motion_num * 10, 1)))
    print('---------------------------------------')
    
    print()

    print('=======================================')
    print('|Test sensor model...                 |')
    sensor_correct, sensor_num = sensor_test(sensormodel)
    print('|                                     |')
    print('|Number of samples: {:5}             |'.format(sensor_num))
    print('|Correct samples: {:5}               |'.format(sensor_correct))
    print('|                                     |')
    print('|Grading: {:5}                       |'.format(round(sensor_correct / sensor_num * 10, 1)))
    print('---------------------------------------')
    
    print()

    print('=======================================')
    print('|Test resampling model...             |')
    resample_correct, resample_num = resample_test(resampling)
    print('|                                     |')
    print('|Number of samples: {:5}             |'.format(resample_num))
    print('|Correct samples: {:5}               |'.format(resample_correct))
    print('|                                     |')
    print('|Grading: {:5}                       |'.format(round(resample_correct / resample_num * 10, 1)))
    print('---------------------------------------')
    
    return 0

if __name__=="__main__":
    main()