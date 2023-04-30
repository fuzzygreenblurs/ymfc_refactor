#include "i2c.h"
#include "mpu6050.h"
#include "mpu6050_register_map.h"

static uint8_t VERIFIED_MPU_ADDRESS;

uint8_t mpu6050_start(void) {
    uint8_t response;
    uint8_t request = MPU6050_ADDRESS + I2C_WRITE;
    uint8_t peripheral_address;

    response = i2c_start(request);
    peripheral_address = MPU6050_ADDRESS
    if(response != 0) {
        request = MPU6050_ADDRESS_ALTERNATE + I2C_WRITE;
        response = i2c_start(request);

        if (response != 0) {
            return response;
        }

        peripheral_address = MPU6050_ADDRESS_ALTERNATE;
    }

    // the WHO_AM_I register should corroborate the expected peripheral address in the register map
    i2c_read_from_device_register(peripheral_address, MPU6050_WHO_AM_I, &response)

    if (response == peripheral_address) {
        VERIFIED_MPU_ADDRESS = peripheral_address;
        return 0;
    } else {
        return 1;
    }

    return 2;
}

void mpu6050_init(void) {
    i2c_write_to_device_register(VERIFIED_MPU_ADDRESS, MPU6050_PWR_MGMT_1, 0x00);

    // see: https://ulrichbuschbaum.wordpress.com/2015/01/18/using-the-mpu6050s-dlpf/
    i2c_write_to_device_register(VERIFIED_MPU_ADDRESS, MPU6050_CONFIG, 0x01); //DLPF config: accelerometer 184hz bw, gyro 188hz bw
    i2c_write_to_device_register(VERIFIED_MPU_ADDRESS, MPU6050_GYRO_CONFIG, 0x08); // gyro ADC scale: 500 deg/s
    i2c_write_to_device_register(VERIFIED_MPU_ADDRESS, MPU6050_ACCEL_CONFIG, 0x00); // accel ADC scale: 2 g
    i2c_write_to_device_register(VERIFIED_MPU_ADDRESS, MPU6050_INT_ENABLE, 0x00);   // enable data ready interrupt
    i2c_write_to_device_register(VERIFIED_MPU_ADDRESS, MPU6050_SIGNAL_PATH_RESET, 0x00); // don't reset signal path
}

/*
    note: a single reading is broken up across 2 registers and pushed into a buffer as two
    consecutive entries for the X/Y/Z axes for both the gyroscope and accelerometer
*/

void canonicalized_gyro_reading(int16_t* buff) {
    /*
        combine MSB and LSB 8-bit values into one 16 bit value for each axis and persist
    */
    uint8_t tmp[2];
    gyro_X_single_reading(tmp);

    //TODO: since tmp[0] is uint8_t, will left-shifting 8 times zero-out the entry
    // how to coerce to 16bit entry? 
    buff[0] = (tmp[0] << 8) | (tmp[1]);

    gyro_Y_single_reading(tmp);
    buff[1] = (tmp[0] << 8) | (tmp[1]);

    gyro_Z_single_reading(tmp);
    buff[2] = (tmp[0] << 8) | (tmp[1]);
}


void canonicalized_accel_reading(int16_t* buff) {
    /*
        combine MSB and LSB 8-bit values into one 16 bit value for each axis and persist
    */
    uint8_t tmp[2];
    accel_X_single_reading(tmp);
    buff[0] = (tmp[0] << 8) | (tmp[1]);

    accel_Y_single_reading(tmp);
    buff[1] = (tmp[0] << 8) | (tmp[1]);

    accel_Z_single_reading(tmp);
    buff[2] = (tmp[0] << 8) | (tmp[1]);
}

void gyro_X_single_reading(uint8_t* buff) {
    i2c_read_from_device_register(VERIFIED_MPU_ADDRESS, MPU6050_GYRO_XOUT_H, buff);
    i2c_read_from_device_register(VERIFIED_MPU_ADDRESS, MPU6050_GYRO_XOUT_L, buff + 1);
}

void gyro_Y_single_reading(uint8_t* buff) {
    i2c_read_from_device_register(VERIFIED_MPU_ADDRESS, MPU6050_GYRO_YOUT_H, buff;
    i2c_read_from_device_register(VERIFIED_MPU_ADDRESS, MPU6050_GYRO_XOUT_L, buff + 1);
}

void gyro_Z_single_reading(uint8_t* buff) {
    i2c_read_from_device_register(VERIFIED_MPU_ADDRESS, MPU6050_GYRO_ZOUT_H, buff);
    i2c_read_from_device_register(VERIFIED_MPU_ADDRESS, MPU6050_GYRO_ZOUT_L, buff + 1);
}

void accel_X_single_reading(uint8_t* buff) {
    i2c_read_byte(MPU6050_ADDRESS, MPU6050_ACCEL_XOUT_H, buff);
    i2c_read_byte(MPU6050_ADDRESS, MPU6050_ACCEL_XOUT_L, buff + 1);
}

void accel_Y_single_reading(uint8_t* buff) {
    i2c_read_byte(MPU6050_ADDRESS, MPU6050_ACCEL_YOUT_H, buff);
    i2c_read_byte(MPU6050_ADDRESS, MPU6050_ACCEL_YOUT_L, buff + 1);
}

void accel_Z_single_reading(uint8_t* buff) {
    i2c_read_byte(MPU6050_ADDRESS, MPU6050_ACCEL_ZOUT_H, buff);
    i2c_read_byte(MPU6050_ADDRESS, MPU6050_ACCEL_ZOUT_L, buff + 1);
}