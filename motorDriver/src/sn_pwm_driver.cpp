#include "../sn_pwm_driver_i2c.hpp"
#include <wiringPiI2C.h>

SN_pwm_driver* SN_pwm_driver::c_instance = 0;

bool SN_pwm_driver::reset_driver()
{
    const uint8_t RESET_BIT_SET = 0x80;
    const uint8_t MODE_1_ADDR = 0x00;
    SN_pwm_driver::i2c_inst->SN_i2c_write_8bit(MODE_1_ADDR, RESET_BIT_SET);
    uint8_t read_data = SN_pwm_driver::i2c_inst->SN_i2c_read_8bit(MODE_1_ADDR);
    
    if (read_data & RESET_BIT_SET) ///< Check if reset bit is still set
       return false;
    
    return true; 

}
bool SN_pwm_driver::set_frequency(int frequency)
{
    const uint8_t MODE_1_ADDR = 0x00;
    const uint8_t PRESCALER_ADDR = 0xFE;
    const uint8_t SLEEP_BIT_SET = 0x10;
    uint8_t prescaler = 0x1E;
    
    SN_pwm_driver::current_frequency = frequency;

    SN_pwm_driver::i2c_inst->SN_i2c_write_8bit(MODE_1_ADDR, SLEEP_BIT_SET);         ///< Set sleep mode to change prescaler (?) forget if its set or unset...
    /*
    DELETE THIS COMMENT IN PLACE OF PRESCALER CALCULATION
    */
    SN_pwm_driver::i2c_inst->SN_i2c_write_8bit(PRESCALER_ADDR, prescaler);    ///< Set prescaler register with new calculated value
    SN_pwm_driver::i2c_inst->SN_i2c_write_8bit(MODE_1_ADDR, 0x00);         ///< Unset sleep mode bit
    
    return SN_pwm_driver::reset_driver();
}

bool SN_pwm_driver::set_duty_cycle(uint16_t duty_cycle)
{
    const uint8_t BASE_PWM_0_ADDR = 0x08;
    const uint8_t BASE_PWM_1_ADDR = 0x0C;

    SN_pwm_driver::current_duty_cycle = duty_cycle;
    
    // Set duty cycle for PWM pin 0
    SN_pwm_driver::i2c_inst->SN_i2c_write_8bit(BASE_PWM_0_ADDR, duty_cycle);
    SN_pwm_driver::i2c_inst->SN_i2c>write_8bit(BASE_PWM_0_ADDR + 1, duty_cycle >> 8);
    
    // Set duty cycle for PWM pin 1
    SN_pwm_driver::i2c_inst->SN_i2c_write_8bit(BASE_PWM_1_ADDR, duty_cycle);
    SN_pwm_driver::i2c_inst->SN_i2c>write_8bit(BASE_PWM_1_ADDR + 1, duty_cycle >> 8);
    
    return SN_pwm_driver::reset_driver();   
}
