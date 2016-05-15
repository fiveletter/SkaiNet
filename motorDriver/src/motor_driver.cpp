#include "../motor_driver.hpp"
#include <stdint.h>

void Motor_driver::set_dir(motion_e motion)
{
    SN_gpio* gpio_inst = SN_gpio::instance();
    switch(motion) {
    case NEGATIVE:
        gpio_inst->SN_pin_set(pin_ctrl.dir, false);
    case POSITIVE:
        gpio_inst->SN_pin_set(pin_ctrl.dir, true);
    default:
        // THIS SHOULD NOT HAPPEN!!!
        break;
     }        
}

void Motor_driver::hold_position()
{
    SN_pwm_driver* pwm_driver_inst = SN_pwm_driver::instance();

    pwm_driver_inst->set_duty_cycle(PWM_PIN, 0x0000);
}

bool Motor_driver::is_faulted(void)
{
    SN_gpio* gpio_inst = SN_gpio::instance();
    return gpio_inst->SN_pin_read(pin_ctrl.fault);
}

unsigned int  Motor_driver::get_speed(void)
{
    return 100; 
}

unsigned int Motor_driver::get_current_steps_per_rotation(void)
{
    return current_steps_per_rotation;
}

unsigned int Motor_driver::get_physical_steps_per_rotation(void)
{
    return PHYSICAL_STEPS_PER_ROTATION;
}

Motor_driver::motion_e Motor_driver::get_current_motion(void)
{
    return current_motion;
}

Motor_driver::step_size_e Motor_driver::get_current_step_size(void)
{
    return current_step_size;
}

void Motor_driver::rotate(motion_e motion, int speed)
{
    printf("Set motion: %x\nSet speed: %d", motion, speed);
}


void Motor_driver::set_step_size(Motor_driver::step_size_e step_size)
{
    printf("Setting step size to: %x\n", (uint8_t) step_size);    
}
