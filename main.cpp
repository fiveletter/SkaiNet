#include <stdio.h>
#include <stdint.h>
#include "motorDriver/motor_system.hpp"

int main(void)
{  
   Motor_system* motor_sys_inst = Motor_system::instance();
   printf("Is system faulted: %s\n", motor_sys_inst->is_faulted() ? "Yes" : "No");
   printf("Current x speed: %f", motor_sys_inst->get_x_speed());
   return 0;
} 
    /*
    Motor_driver driver1(400, PWM_0, PIN_2, PIN_3, PIN_21, PIN_22, PIN_23, PIN_24);
    driver1.print_pins();

    printf("Physical steps per rotation: %d\n", driver1.get_physical_steps_per_rotation());
    printf("Current steps per rotation: %d\n", driver1.get_current_steps_per_rotation());
    printf("Current motion: %x\n", driver1.get_current_motion());
    printf("Current step size: %x\n", driver1.get_current_step_size());
    
    driver1.set_step_size(Motor_driver::STEP_1_2);
    driver1.rotate(Motor_driver::NEGATIVE, 500);

    printf("Physical steps per rotation: %d\n", driver1.get_physical_steps_per_rotation());
    printf("Current steps per rotation: %d\n", driver1.get_current_steps_per_rotation());
    printf("Current motion: %x\n", driver1.get_current_motion());
    printf("Current step size: %x\n", driver1.get_current_step_size());
    
    
    unsigned int frequency = 1000;
    SN_pwm_driver* pwm_driver_inst = SN_pwm_driver::instance();
    uint16_t current_duty_cycle = pwm_driver_inst->get_current_duty_cycle();
    unsigned int current_frequency = pwm_driver_inst->get_current_frequency();

    printf("Current duty cycle: %x\nCurrent frequency: %x\n", current_duty_cycle, current_frequency);
    printf("Starting GPIO oscilation\n");

    SN_gpio* gpio_inst = SN_gpio::instance();

    // Setup pins
    gpio_inst->SN_pin_mode(PIN_2, SN_gpio::SNOUTPUT);  
    gpio_inst->SN_pin_mode(PIN_3, SN_gpio::SNOUTPUT);
    gpio_inst->SN_pin_mode(PIN_21, SN_gpio::SNOUTPUT);
    gpio_inst->SN_pin_mode(PIN_22, SN_gpio::SNOUTPUT);
    gpio_inst->SN_pin_mode(PIN_23, SN_gpio::SNOUTPUT);
    gpio_inst->SN_pin_mode(PIN_24, SN_gpio::SNOUTPUT);

    for (int i = 0; i < 10; i++) {
        if ( i > 0)
            frequency -= 100;
        pwm_driver_inst->set_frequency(frequency);
        current_frequency = pwm_driver_inst->get_current_frequency();
        printf("Changed frequency to: %d\n", current_frequency);
        printf("Setting GPIO pins: %d, %d, %d\n", PIN_2, PIN_3, PIN_4);
        gpio_inst->SN_pin_set(PIN_2);
        gpio_inst->SN_pin_set(PIN_3);
        gpio_inst->SN_pin_set(PIN_21);
        gpio_inst->SN_pin_set(PIN_22);
        gpio_inst->SN_pin_set(PIN_23);
        gpio_inst->SN_pin_set(PIN_24);

        delay(500);

        printf("Unsetting GPIO pins\n");
        gpio_inst->SN_pin_unset(PIN_2);
        gpio_inst->SN_pin_unset(PIN_3);
        gpio_inst->SN_pin_unset(PIN_21);
        gpio_inst->SN_pin_unset(PIN_22);
        gpio_inst->SN_pin_unset(PIN_23);
        gpio_inst->SN_pin_unset(PIN_24); 
        
        delay(500);
    }
    */   
