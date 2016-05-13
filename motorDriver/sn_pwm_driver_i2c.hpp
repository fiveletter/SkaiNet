#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdint.h>

/**
 * Created by Five Letter
 * THIS CLASS IS NOTHING SPECIAL!!! This class is a wrapper
 * in case we want to switch from wiringPi library or create
 * our own. All required functions are declared from wiringPi
 * as needed. This is only a subset of functions available
 */

class SN_pwm_driver_i2c
{
    private: 
    static SN_pwm_driver_i2c *c_instance;

    static const int DEVICE_ID = 0x42;
    const int file_descriptor;

    /**
     * Default constructor for I2C class. This calls wiringPiI2CSetup()
     * with argument 0x42 (Device ID for pwm driver)
     * 
     * Upon initialization failure the program will crash
     */
    SN_pwm_driver_i2c (): file_descriptor(wiringPiI2CSetup(DEVICE_ID))
    {
        // DO NOTHING
    };
 
    public:   
    /** 
     * Writes 8 bits of data to file_descriptor at specified register
     * 
     * @param reg   register to write data to
     * @param data  8 bit value 
     * @param mode  mode we are setting, either OUTPUT or INPUT
     */
    int SN_i2c_write_8bit(uint8_t reg, uint8_t data);

    /**
     * Read 8 bits of data to file_descriptor at specified register
     *
     * @param reg   register to read data from
     * @return      8 bit data received from i2c device   
     */
    uint8_t SN_i2c_read_8bit(uint8_t reg);
  
    /**
     * Returns the instance of this singleton class. 
     *
     * @return instance of SN_GPIO
     */
    static SN_pwm_driver_i2c* instance(void)
    {
        if (!c_instance) 
            printf("Holy shit PWM not intialized!! Will do it now!!\n");
            c_instance = new SN_pwm_driver_i2c;
        return c_instance;
    };
};

