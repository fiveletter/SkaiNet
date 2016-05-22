#include <stdio.h>
#include "sn_gpio.hpp"
#include "sn_pwm_driver.hpp"

/**
 * Created by Five Letter
 * THIS CLASS IS NOTHING SPECIAL!!! This class is a wrapper
 * in case we want to switch from wiringPi library or create
 * our own. All required functions are declared from wiringPi
 * as needed. This is only a subset of functions available
 */

class Motor_driver
{
    public:   
    typedef enum step_size{
        STEP_1 = 0, ///< MODE2:MODE1:MODE0  000
        STEP_1_2,   ///< MODE2:MODE1:MODE0  001
        STEP_1_4,   ///< MODE2:MODE1:MODE0  010
        STEP_1_8,   ///< MODE2:MODE1:MODE0  011
        STEP_1_16,  ///< MODE2:MODE1:MODE0  100
        STEP_1_32,  ///< MODE2:MODE1:MODE0  101
    } step_size_e;
    
    typedef enum motion {
        NEGATIVE,
        POSITIVE,
        HOLD,
    } motion_e;

    /**
     * Default constructor for GPIO class. This calls wiringPiSetup()
     * which maps the pins to wiringPi's special mapping
     * 
     * Upon initialization failure the program will crash
     */
    Motor_driver(unsigned int hardware_steps, pwm_pin_e pin, io_pin m0, io_pin m1, io_pin m2, 
                                              io_pin d, io_pin rst, io_pin flt, io_pin sleep):
        PWM_PIN(pin),
        PHYSICAL_STEPS_PER_ROTATION(hardware_steps){
        
        current_steps_per_rotation = hardware_steps;
        current_step_size = STEP_1;
        current_motion = HOLD;
        current_speed = 0;

        // Set control pins
        pin_ctrl.motor0 = m0;
        pin_ctrl.motor1 = m1; 
        pin_ctrl.motor2 = m2; 
        pin_ctrl.dir    = d;
        pin_ctrl.reset  = rst;
        pin_ctrl.fault  = flt;
        pin_ctrl.sleep  = sleep;
        
        SN_gpio* gpio_inst = SN_gpio::instance();
        
        gpio_inst->SN_pin_set(rst);
    };

    bool is_faulted(void);

    unsigned int get_speed(void);
   
    /**
     * Returns the current steps per rotation
     *
     * @return unsigned int of steps per rotation
     */
    void power_off(void);

     /**
     * Returns the current steps per rotation
     *
     * @return unsigned int of steps per rotation
     */
    void power_on(void);

    unsigned int get_current_steps_per_rotation(void);

    /**
     * Returns the physical steps per rotation.
     * Physical steps per rotation refers to the number of
     * full steps for one full rotation
     *
     * @return unsigned int of steps per rotation
     */
    unsigned int get_physical_steps_per_rotation(void);

    /**
     * Returns the current motion of the motor
     *
     * @return motion the motor is moving in
     */
    motion_e get_current_motion(void); 
    
    /**
     * Returns the step size the motor is currently set to
     *
     * @return step size of the motor
     */ 
    step_size_e get_current_step_size(void);

    /**
     * Sets the rotation of the motor can either be
     * NEGATIVE, POSITIVE, or HOLD
     *
     * @param motion    specifies the type of motion
     * @param speed     Sets the speed of the motor, 0 <= speed >= 1000
     */
    void rotate(motion_e motion, int speed);
    
    /** 
     * Sets the step size of the motor
     *
     * @param step_size_e step size for motor
     */
    void set_step_size(step_size_e step_size);

    /** 
     * Print out the control pins, will remove
     * 
     */
    void print_pins(void)
    {
        printf("Motor 0 pin: %d\n", pin_ctrl.motor0);
        printf("Motor 1 pin: %d\n", pin_ctrl.motor1);
        printf("Motor 2 pin: %d\n", pin_ctrl.motor2);
        printf("Dir pin: %d\n", pin_ctrl.dir);
        printf("Fault pin: %d\n", pin_ctrl.fault);
        printf("Reset pin: %d\n", pin_ctrl.reset);
        printf("Sleep pin: %d\n", pin_ctrl.sleep);
    }
    private: 
    typedef struct pin_ctrl {
        io_pin motor0;
        io_pin motor1;
        io_pin motor2;
        io_pin dir;
        io_pin reset;
        io_pin fault;
        io_pin sleep;
    } pin_ctrl_s;
   
    // Class Properties 
    const pwm_pin_e PWM_PIN;
    pin_ctrl_s pin_ctrl;
    const unsigned int PHYSICAL_STEPS_PER_ROTATION;
    unsigned int current_steps_per_rotation;
    step_size_e current_step_size;    
    motion_e current_motion;
    unsigned int current_speed;
    /**
     * Sets the direction of the motor positive or negative
     *
     * @param motion    direction to move
     */ 
    void set_dir(motion_e motion);
    
    /**
     * Holds the current position motor is at, used for speed == 0
     *
     */
    void hold_position(void);


};

