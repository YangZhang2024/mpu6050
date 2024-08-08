#include "mpu6050.h"


#define MPU6050_SMPLRT_DIV   0x19
#define MPU6050_CONFIG       0x1A
#define MPU6050_GYRO_CONFIG  0x1B
#define MPU6050_ACCEL_CONFIG 0x1C

#define MPU6050_ACCEL_XOUT_H 0x3B
#define MPU6050_ACCEL_XOUT_L 0x3C
#define MPU6050_ACCEL_YOUT_H 0x3D
#define MPU6050_ACCEL_YOUT_L 0x3E
#define MPU6050_ACCEL_ZOUT_H 0x3F
#define MPU6050_ACCEL_ZOUT_L 0x40
#define MPU6050_TEMP_OUT_H   0x41
#define MPU6050_TEMP_OUT_L   0x42
#define MPU6050_GYRO_XOUT_H  0x43
#define MPU6050_GYRO_XOUT_L  0x44
#define MPU6050_GYRO_YOUT_H  0x45
#define MPU6050_GYRO_YOUT_L  0x46
#define MPU6050_GYRO_ZOUT_H  0x47
#define MPU6050_GYRO_ZOUT_L  0x48

#define MPU6050_PWR_MGMT_1   0x6B
#define MPU6050_PWR_MGMT_2   0x6C
#define MPU6050_WHO_AM_I     0x75

void mpu6050_init(void) {
    iic_init();
    mpu6050_write_reg(MPU6050_PWR_MGMT_1, 0x01);
    mpu6050_write_reg(MPU6050_PWR_MGMT_2, 0x00);

    mpu6050_write_reg(MPU6050_SMPLRT_DIV, 0x09);
    mpu6050_write_reg(MPU6050_CONFIG, 0x06);
    mpu6050_write_reg(MPU6050_GYRO_CONFIG, 0x18);
    mpu6050_write_reg(MPU6050_ACCEL_CONFIG, 0x18);
}

void mpu_6050_get_data(MPU6050_Result *result) {
    // 优化点, 连续读 todo
    uint8_t DH = mpu6050_read_reg(MPU6050_ACCEL_XOUT_H);
    uint8_t DL = mpu6050_read_reg(MPU6050_ACCEL_XOUT_L);
    result->acc_x = (DH << 8) | DL;

    DH = mpu6050_read_reg(MPU6050_ACCEL_YOUT_H);
    DL = mpu6050_read_reg(MPU6050_ACCEL_YOUT_L);
    result->acc_y = (DH << 8) | DL;

    DH = mpu6050_read_reg(MPU6050_ACCEL_ZOUT_H);
    DL = mpu6050_read_reg(MPU6050_ACCEL_ZOUT_L);
    result->acc_z = (DH << 8) | DL;


    DH = mpu6050_read_reg(MPU6050_GYRO_XOUT_H);
    DL = mpu6050_read_reg(MPU6050_GYRO_XOUT_L);
    result->gryo_x = (DH << 8) | DL;

    DH = mpu6050_read_reg(MPU6050_GYRO_YOUT_H);
    DL = mpu6050_read_reg(MPU6050_GYRO_YOUT_L);
    result->gryo_y = (DH << 8) | DL;

    DH = mpu6050_read_reg(MPU6050_GYRO_ZOUT_H);
    DL = mpu6050_read_reg(MPU6050_GYRO_ZOUT_L);
    result->gryo_z = (DH << 8) | DL;
}

void mpu6050_write_reg(uint8_t reg_addr, uint8_t data) {
    iic_start();
    iic_send_byte(MPU6050_ADDR);
    iic_wait_ack();
    iic_send_byte(reg_addr);
    iic_wait_ack();
    iic_send_byte(data);
    iic_wait_ack();
    iic_stop();
}

uint8_t mpu6050_read_reg(uint8_t reg_addr) {
    iic_start();
    iic_send_byte(MPU6050_ADDR);
    iic_wait_ack();
    iic_send_byte(reg_addr);
    iic_wait_ack();

    iic_start();
    iic_send_byte(MPU6050_ADDR + 1);
    iic_wait_ack();
    uint8_t result = iic_read_byte(0);
    iic_stop();
    return result;
}