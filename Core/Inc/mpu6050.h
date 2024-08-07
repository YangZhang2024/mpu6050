#ifndef  MPU_6050_H
#define MPU_6050_H

#define MPU6050_ADDR 0xD0

#include "soft_iic.h"

void mpu6050_init(void);

void mpu6050_write_reg(uint8_t reg_addr, uint8_t data);

uint8_t mpu6050_read_reg(uint8_t reg_addr);

#endif