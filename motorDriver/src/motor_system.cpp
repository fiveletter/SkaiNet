#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "../motor_system.hpp"
#include "../motor_driver.hpp"

void Motor_system::set_x_y_speed(float x_speed, float y_speed)
{
    x_speed = abs(x_speed) * Motor_system::MAX_SPEED;
    y_speed = abs(y_speed) * Motor_system::MAX_SPEED;

    if (x_speed < 0) {
	// Horizontal motor rotates counter-clockwise
	yaw_motor.rotate(Motor_driver::NEGATIVE, x_speed);
    }
    else {
	// Horizontal motor rotates clockwise
	yaw_motor.rotate(Motor_driver::POSITIVE, x_speed);
    }
    if (y_speed < 0) {
	// Vertical motor rotates counter-clockwise
	pitch_motor.rotate(Motor_driver::NEGATIVE, y_speed);
    }
    else {
	// Vertical motor rotates clockwise
	pitch_motor.rotate(Motor_driver::POSITIVE, y_speed);
    }
}

bool Motor_system::is_faulted()
{	
    // Check if either motor is faulted
    if (yaw_motor.is_faulted() || pitch_motor.is_faulted())
	return true;
    else 
	return false;
}

static void Motor_system::set_smoothness()
{
    float max_steps = Motor_system::MAX_SPEED * Motor_system::MIN_ROTATION_SEC;	///< Calculates maximum number of steps per one rotation
    
    for (int i = 1; i < 6; i++) {
	if (Motor_system::YAW_PHYSICAL_STEPS * (2 ^ i) > max_steps) {
	    yaw_motor.set_step_size((step_size_e) i - 1);	///< Send maximum valid smoothness to Motor_driver
	    break;
	}
    }

    for (int i = 1; i < 6; i++) {
	if (Motor_system::PITCH_PHYSICAL_STEPS * (2 ^ i) > max_steps) {
	    pitch_motor.set_step_size((step_size_e) i - 1);	///< Send maximum valid smoothness to Motor_driver
	    break;
	}
    }
}

float Motor_system::get_x_speed()
{
    if (yaw_motor::get_current_motion == NEGATIVE)
	return yaw_motor::get_speed * (-1 / 1000);
    else 
	return yaw_motor::get_speed / 1000;
}

float Motor_system::get_y_speed()
{
    if (pitch_motor::get_current_motion == NEGATIVE)
	return pitch_motor::get_speed * (-1 / 1000);
    else 
	return pitch_motor::get_speed / 1000;
}



