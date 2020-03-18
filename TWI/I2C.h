#ifndef I2C_H
#define I2C_H
#define SCL PB2
#define SDA PB0
#define I2C_STATE_CHECK_ADDR 0x00
#define I2C_STATE_CHECK_MODE 0x01
#define I2C_STATE_READ_ACK 0x02
#define I2C_STATE_WRITE_ACK 0x03
#define I2C_STATE_READ_DATA 0x04
#define I2C_STATE_WRITE_DATA 0x05
#define I2C_STATE_IDLE 0x06
#define I2C_STATE_CHECK_REPLY 0x07
void I2Cinit(uint8_t I2C_addr);
#endif
