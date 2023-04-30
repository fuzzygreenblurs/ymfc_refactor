#ifndef MPU6050
#define MPU6050

extern uint8_t mpu6050_start(void);
extern void mpu6050_init(void);
extern void canonicalized_gyro_reading(int16_t* buff);
extern void canonicalized_accel_reading(int16_t* buff);

void read_gyro_X(uint8_t* buff);
void read_gyro_Y(uint8_t* buff);
void read_gyro_Z(uint8_t* buff);
void read_accel_X(uint8_t* buff);
void read_accel_Y(uint8_t* buff);
void read_accel_Z(uint8_t* buff);

#endif