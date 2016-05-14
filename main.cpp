#include <stdio.h>
#include <stdint.h>
#include "motorDriver/sn_gpio.hpp"
#include "motorDriver/sn_pwm_driver.hpp"

int main(void)
{   
    unsigned int frequency = 1000;
    SN_pwm_driver* pwm_driver_inst = SN_pwm_driver::instance();
    uint16_t current_duty_cycle = pwm_driver_inst->get_current_duty_cycle();
    unsigned int current_frequency = pwm_driver_inst->get_current_frequency();

    printf("Current duty cycle: %x\nCurrent frequency: %x\n", current_duty_cycle, current_frequency);
    printf("Starting GPIO oscilation\n");

    SN_gpio* gpio_inst = SN_gpio::instance();

    for (int i = 0; i < 10; i++) {
        if ( i > 0)
            frequency -= 100;
        pwm_driver_inst->set_frequency(frequency);
        current_frequency = pwm_driver_inst->get_current_frequency();
        printf("Changed frequency to: %d\n", current_frequency);
        printf("Setting GPIO pins\n");
        gpio_inst->SN_pin_set(SN_gpio::PIN_2);
        gpio_inst->SN_pin_set(SN_gpio::PIN_3);
        gpio_inst->SN_pin_set(SN_gpio::PIN_21);
        gpio_inst->SN_pin_set(SN_gpio::PIN_22);
        gpio_inst->SN_pin_set(SN_gpio::PIN_23);
        gpio_inst->SN_pin_set(SN_gpio::PIN_24);

        delay(500);

        printf("Unsetting GPIO pins\n");
        gpio_inst->SN_pin_unset(SN_gpio::PIN_2);
        gpio_inst->SN_pin_unset(SN_gpio::PIN_3);
        gpio_inst->SN_pin_unset(SN_gpio::PIN_21);
        gpio_inst->SN_pin_unset(SN_gpio::PIN_22);
        gpio_inst->SN_pin_unset(SN_gpio::PIN_23);
        gpio_inst->SN_pin_unset(SN_gpio::PIN_24); 
        
        delay(500);
    }
    
    return 0;
}
