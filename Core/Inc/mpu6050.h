#ifndef  MPU_6050_H
#define MPU_6050_H

#define MPU6050_ADDR 0xD0

#include "soft_iic.h"

typedef struct {
    int16_t acc_x;
    int16_t acc_y;
    int16_t acc_z;
    int16_t gryo_x;
    int16_t gryo_y;
    int16_t gryo_z;
} MPU6050_Result;


void mpu6050_init(void);

void mpu6050_write_reg(uint8_t reg_addr, uint8_t data);

uint8_t mpu6050_read_reg(uint8_t reg_addr);

void mpu_6050_get_data(MPU6050_Result *result);

#endif