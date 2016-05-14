#include "../sn_pwm_driver_i2c.hpp"
#include <wiringPiI2C.h>

SN_pwm_driver_i2c* SN_pwm_driver_i2c::c_instance = 0;

int SN_pwm_driver_i2c::SN_i2c_write_8bit(uint8_t reg, uint8_t data) const
{
    return wiringPiI2CWriteReg8(SN_pwm_driver_i2c::file_descriptor, reg, data);
}

uint8_t SN_pwm_driver_i2c::SN_i2c_read_8bit(uint8_t reg) const
{
    return wiringPiI2CReadReg8(SN_pwm_driver_i2c::file_descriptor, reg);   
}
