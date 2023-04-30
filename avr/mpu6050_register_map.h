#ifndef MPU6050_REGISTER_MAP
#define MPU6050_REGISTER_MAP

/*
Register map source doc: https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf
*/

#define MPU6050_ADDRESS             0x68
#define MPU6050_ADDRESS_ALTERNATE   0x69
#define MPU6050_WHO_AM_I            0x75
#define MPU6050_PWR_MGMT_1          0x6B
#define MPU6050_CONFIG              0x1A
#define MPU6050_GYRO_CONFIG         0x1B
#define MPU6050_ACCEL_CONFIG        0x1C
#define MPU6050_INT_ENABLE          0x38
#define MPU6050_SIGNAL_PATH_RESET   0x68

#define MPU6050_GYRO_XOUT_H         0x43
#define MPU6050_GYRO_XOUT_L         0x44
#define MPU6050_GYRO_YOUT_H         0x45
#define MPU6050_GYRO_YOUT_L         0x46
#define MPU6050_GYRO_ZOUT_H         0x47
#define MPU6050_GYRO_ZOUT_L         0x48

#define MPU6050_ACCEL_XOUT_H        0x3B
#define MPU6050_ACCEL_XOUT_L        0x3C
#define MPU6050_ACCEL_YOUT_H        0x3D
#define MPU6050_ACCEL_YOUT_L        0x3E
#define MPU6050_ACCEL_ZOUT_H        0x3F
#define MPU6050_ACCEL_ZOUT_L        0x40

#endif