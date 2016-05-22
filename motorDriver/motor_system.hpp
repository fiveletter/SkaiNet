#include <wiringPi.h>
#include <stdio.h>
#include "motor_driver.hpp"

class Motor_system
{
    private: 
    static Motor_system *c_instance;

    static const unsigned int MAX_SPEED = 1000;		///< Maximum rotation speed in hertz
    static const float MIN_ROTATION_SEC = 4.0; ///< Minimum time for one rotation in seconds
    static const unsigned int YAW_PHYSICAL_STEPS = 200;
    static const unsigned int PITCH_PHYSICAL_STEPS = 400;

    Motor_driver* yaw_motor;
    Motor_driver* pitch_motor;  

    Motor_system() {	///< Default constructor for Motor_sytem class
        printf("Called default constructor of motor system!!!\n");
        pitch_motor = new Motor_driver(PITCH_PHYSICAL_STEPS, PWM_0, PIN_2, PIN_3, PIN_21, PIN_22, PIN_23, PIN_24, PIN_0);
        yaw_motor   = new Motor_driver(YAW_PHYSICAL_STEPS, PWM_1, PIN_4, PIN_5, PIN_6, PIN_25, PIN_27, PIN_28, PIN_1);

        set_smoothness();
    }

    ~Motor_system() {
    	set_x_y_speed(0.0, 0.0);
    	power_off();
    }

    public:
    void power_off(void);

    void power_on(void);

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
    void set_smoothness();

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
    
    /** Returns the instance of this singleton class
     *
     * @return instance of Motor_system
     */
    static Motor_system* instance(void)
    {
        if (!c_instance)
            c_instance = new Motor_system();
        return c_instance;
    };

};
