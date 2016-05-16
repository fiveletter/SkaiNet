#include "../sn_pwm_driver.hpp"
#include <wiringPiI2C.h>
#include <math.h>
#include <stdio.h>

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

uint16_t SN_pwm_driver::get_current_duty_cycle()
{
    return this->current_duty_cycle;
}

unsigned int SN_pwm_driver::get_current_frequency()
{
    return this->current_frequency;
}

bool SN_pwm_driver::set_frequency(unsigned int frequency)
{
    const uint8_t MODE_1_ADDR = 0x00;
    const uint8_t PRESCALER_ADDR = 0xFE;
    const uint8_t SLEEP_BIT_SET = 0x10;
    uint8_t prescaler = 0x1E;
    
    unsigned int clamped_frequency = fmax(frequency, SN_pwm_driver::MIN_FREQUENCY);
    clamped_frequency = fmin(clamped_frequency, SN_pwm_driver::MAX_FREQUENCY);   
    prescaler = round((25000000 / (4096 * clamped_frequency)));
    this->current_frequency = clamped_frequency;

    SN_pwm_driver::i2c_inst->SN_i2c_write_8bit(MODE_1_ADDR, SLEEP_BIT_SET);         ///< Set sleep mode to change prescaler 
    SN_pwm_driver::i2c_inst->SN_i2c_write_8bit(PRESCALER_ADDR, prescaler);    ///< Set prescaler register with new calculated value
    SN_pwm_driver::i2c_inst->SN_i2c_write_8bit(MODE_1_ADDR, 0x00);         ///< Unset sleep mode bit
    
    return SN_pwm_driver::reset_driver();
}

bool SN_pwm_driver::set_duty_cycle(pwm_pin_e pin, uint16_t duty_cycle)
{
    const uint8_t BASE_PWM_0_ADDR = 0x08;
    const uint8_t BASE_PWM_1_ADDR = 0x0C;

    this->current_duty_cycle = duty_cycle;
    if (pin == PWM_0) {   
        // Set duty cycle for PWM pin 0
        SN_pwm_driver::i2c_inst->SN_i2c_write_8bit(BASE_PWM_0_ADDR, duty_cycle);
        SN_pwm_driver::i2c_inst->SN_i2c_write_8bit(BASE_PWM_0_ADDR + 1, duty_cycle >> 8);
    } else {
        // Set duty cycle for PWM pin 1
        SN_pwm_driver::i2c_inst->SN_i2c_write_8bit(BASE_PWM_1_ADDR, duty_cycle);
        SN_pwm_driver::i2c_inst->SN_i2c_write_8bit(BASE_PWM_1_ADDR + 1, duty_cycle >> 8);
    }   
    return SN_pwm_driver::reset_driver();   
}
