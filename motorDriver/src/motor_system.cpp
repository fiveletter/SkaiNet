#include <stdio.h>
#include <stdlib.h>
#include "../motor_system.hpp"
#include <math.h>

Motor_system* Motor_system::c_instance = 0;

void Motor_system::set_x_y_speed(float x_speed, float y_speed)
{
    if (x_speed < 0) {
	    // Horizontal motor rotates counter-clockwise
	    yaw_motor->rotate(Motor_driver::NEGATIVE, abs(x_speed * Motor_system::MAX_SPEED));
	printf("Setting negative rotation yaw\n");
    }
    else {
	    // Horizontal motor rotates clockwise
	    yaw_motor->rotate(Motor_driver::POSITIVE, abs(x_speed * Motor_system::MAX_SPEED));
	printf("Setting postive rotation yaw\n");   
 }
    if (y_speed < 0) {
	    // Vertical motor rotates counter-clockwise
	    pitch_motor->rotate(Motor_driver::NEGATIVE, abs(y_speed * Motor_system::MAX_SPEED));
  	printf("Setting negative pitch\n");
	  }
    else {
	    // Vertical motor rotates clockwise
	    pitch_motor->rotate(Motor_driver::POSITIVE, abs(y_speed * Motor_system::MAX_SPEED));
    printf("Setting positive pitch\n");
	}
}

void Motor_system::power_off()
{
    pitch_motor->power_off();
    yaw_motor->power_off();
}

bool Motor_system::is_faulted()
{	
    // Check if either motor is faulted
    return yaw_motor->is_faulted() || pitch_motor->is_faulted();
}

void Motor_system::set_smoothness()
{
    float max_steps = Motor_system::MAX_SPEED * Motor_system::MIN_ROTATION_SEC;	///< Calculates maximum number of steps per one rotation
    
    for (int i = 1; i < 6; i++) {
        if (Motor_system::YAW_PHYSICAL_STEPS * pow(2, i) > max_steps) {
	    yaw_motor->set_step_size(static_cast<Motor_driver::step_size_e>( i - 1));	///< Send maximum valid smoothness to Motor_driver
	    break;
	}
    }

    for (int i = 1; i < 6; i++) {
	if (Motor_system::PITCH_PHYSICAL_STEPS * pow(2, i) > max_steps) {
	    pitch_motor->set_step_size(static_cast<Motor_driver::step_size_e>( i - 1));	///< Send maximum valid smoothness to Motor_driver
	    break;
	}
    }
}

float Motor_system::get_x_speed()
{
    if (yaw_motor->get_current_motion() == Motor_driver::NEGATIVE)
	return (float)yaw_motor->get_speed() * (-1 / 1000);
    else 
	return (float)yaw_motor->get_speed() / 1000;
}

float Motor_system::get_y_speed()
{
    if (pitch_motor->get_current_motion() == Motor_driver::NEGATIVE)
	return (float) pitch_motor->get_speed() * (-1 / 1000);
    else 
	return (float) pitch_motor->get_speed() / 1000;
}

