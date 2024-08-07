#include "mpu6050.h"


void mpu6050_init(void) {
    iic_init();
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