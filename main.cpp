#include <stdio.h>
#include <stdint.h>
#include "motorDriver/sn_gpio.hpp"
#include "motorDriver/sn_pwm_driver.hpp"

int main(void)
{
    
    
    
    /*
    SN_pwm_driver_i2c* pwm_i2c_inst = SN_pwm_driver_i2c::instance();
    int return_code = pwm_i2c_inst->SN_i2c_write_8bit(0x06,0x00);
    return_code = pwm_i2c_inst->SN_i2c_write_8bit(0x07, 0x00);
    return_code = pwm_i2c_inst->SN_i2c_write_8bit(0x08, 0x00);
    return_code = pwm_i2c_inst->SN_i2c_write_8bit(0x09, 0x08);
    return_code = pwm_i2c_inst->SN_i2c_write_8bit(0x00, 0x80);

    uint8_t data = pwm_i2c_inst->SN_i2c_read(0x09);
    printf("PWM DRIVER\nReturn code: %x\nread 0x09: %x\n", return_code,data);


    SN_Gpio* gpio_inst = SN_Gpio::instance();
    gpio_inst->SN_pin_mode(SN_Gpio::PIN_2, SN_Gpio::SNOUTPUT);
    gpio_inst->SN_pin_mode(SN_Gpio::PIN_3, SN_Gpio::SNOUTPUT);
    gpio_inst->SN_pin_mode(SN_Gpio::PIN_21, SN_Gpio::SNOUTPUT);
    gpio_inst->SN_pin_mode(SN_Gpio::PIN_22, SN_Gpio::SNOUTPUT);
    gpio_inst->SN_pin_mode(SN_Gpio::PIN_23, SN_Gpio::SNOUTPUT);
    gpio_inst->SN_pin_mode(SN_Gpio::PIN_24, SN_Gpio::SNOUTPUT);
   
    for (int i = 0; i < 10; i++) {
        gpio_inst->SN_pin_set(SN_Gpio::PIN_2);
        gpio_inst->SN_pin_set(SN_Gpio::PIN_3);
        gpio_inst->SN_pin_set(SN_Gpio::PIN_21);
        gpio_inst->SN_pin_set(SN_Gpio::PIN_22);
        gpio_inst->SN_pin_set(SN_Gpio::PIN_23);
        gpio_inst->SN_pin_set(SN_Gpio::PIN_24);

        delay(500);

        gpio_inst->SN_pin_unset(SN_Gpio::PIN_2);
        gpio_inst->SN_pin_unset(SN_Gpio::PIN_3);
        gpio_inst->SN_pin_unset(SN_Gpio::PIN_21);
        gpio_inst->SN_pin_unset(SN_Gpio::PIN_22);
        gpio_inst->SN_pin_unset(SN_Gpio::PIN_23);
        gpio_inst->SN_pin_unset(SN_Gpio::PIN_24); 
        
        delay(500);
    }
    int pin2_read = gpio_inst->SN_pin_read(SN_Gpio::PIN_2);
    printf("hello world!!! PIN 2 READ: %d\n", pin2_read);		
	*/
    
    return 0;
}
