#include <stdio.h>
#include <stdint.h>
#include "sn_pwm_driver_i2c.hpp"

/**
 * Created by Five Letter
 * THIS CLASS IS NOTHING SPECIAL!!! This class is a wrapper
 * in case we want to switch from wiringPi library or create
 * our own. All required functions are declared from wiringPi
 * as needed. This is only a subset of functions available
 */

typedef enum pwm_pin {
    PWM_0 = 0,
    PWM_1,
} pwm_pin_e;

class SN_pwm_driver
{
    private: 
    static SN_pwm_driver *c_instance;
    const SN_pwm_driver_i2c* i2c_inst; 
    
    static const uint16_t MAX_DUTY_CYCLE = 0x0FFF;
    static const uint16_t MIN_DUTY_CYCLE = 0x0000;
    static const unsigned int MAX_FREQUENCY  = 1526;
    static const unsigned int MIN_FREQUENCY  = 25;

    uint16_t current_duty_cycle;
    unsigned int current_frequency;
   
    /**
     * Default constructor for PWM class.
     */
    SN_pwm_driver(): i2c_inst(SN_pwm_driver_i2c::instance())
    {
        current_duty_cycle = 0;
        current_frequency = 0;
        set_frequency(10);
        set_duty_cycle(PWM_0,0x0200);
        set_duty_cycle(PWM_1,0x0200);
    };

    /**
     * Reset pwm driver when frequency or duty cycle is changed
     *
     * @return true if reset succesfull false if error occurred
     */
    bool reset_driver();

    public:  
    /**
     * Returns the current duty cycle of the system
     *
     *
     * @return current duty cycle
     */ 
    uint16_t get_current_duty_cycle(void);

    /**
     * Returns the current frequency of the system
     *
     * @return current duty cycle
     */ 
    unsigned int get_current_frequency(void);

    /** 
     * Set frequency of the PWM driver
     * 
     * @param freq  frequency to write
     * @return mode  true if frequency successfully set
     */
    bool set_frequency(unsigned int frequency);

     /** 
     * Set duty cycle of the PWM driver
     * 
     * @param duty  frequency to write
     * @return mode  true if frequency successfully set
     */
    bool set_duty_cycle(pwm_pin_e pin,uint16_t duty_cycle);

    /**
     * Returns the instance of this singleton class. 
     *
     * @return instance of SN_PWM
     */
    static SN_pwm_driver* instance(void)
    {
        if (!c_instance) 
            c_instance = new SN_pwm_driver();
        return c_instance;
    };
};

