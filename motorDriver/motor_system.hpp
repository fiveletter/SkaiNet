#include <wiringPi.h>
#include <stdio.h>
#include "motor_driver.hpp"
#include "sn_motor_driver.hpp"

class Motor_system
{
    private: 
    static Motor_system *c_instance;

    static Motor_driver yaw_motor;
    static Motor_driver pitch_motor;

    static const unsigned int MAX_SPEED = 1000;		///< Maximum rotation speed in hertz
    static const unsigned float MIN_ROTATION_SEC = 4.0; ///< Minimum time for one rotation in seconds
    static const unsigned int YAW_PHYSICAL_STEPS = 200;
    static const unsigned int PITCH_PHYSICAL_STEPS = 400;

    Motor_system() {	///< Default constructor for Motor_sytem class
	set_smoothness();
     	pitch_motor(PITCH_PHYSICAL_STEPS, PIN_2, PIN_3, PIN_21, PIN_22, PIN_23, PIN_24);
	yaw_motor(YAW_PHYSICAL_STEPS, PIN_4, PIN_5, PIN_6, PIN_25, PIN_27, PIN_28);	
	current_speed = 0;
    }

    public:
    /**
     * Sets the speed for both the yaw_motor and pitch motor
     *
     * @param x_speed speed of horizontal motor
     * @param y_speed speed of vertical motor
     */
    void set_x_y_speed(float x_speed, float y_speed);

    /**
     * Checks if either system is faulted
     *
     * @return true if either motor is faulted
     */
    bool is_faulted();

    /*
    * Sets motor step size for maximum smoothness given minimum rotation time
    */
    static void set_smoothness();

    /*
    * Returns the signed speed of the horizontal motor
    *
    * @return current speed of horizontal motor
    */
    float get_x_speed();

    /*
    * Returns the signed speed of the vertical motor
    *
    * @return current speed of vertical motor
    */
    float get_y_speed();
};

