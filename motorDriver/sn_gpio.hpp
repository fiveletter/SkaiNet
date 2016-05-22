#include <wiringPi.h>
#include <stdio.h>

/**
 * Created by Five Letter
 * THIS CLASS IS NOTHING SPECIAL!!! This class is a wrapper
 * in case we want to switch from wiringPi library or create
 * our own. All required functions are declared from wiringPi
 * as needed. This is only a subset of functions available
 */

typedef enum io_pin {
    PIN_0 = 0,
    PIN_1 = 1,
    PIN_2 = 2,
    PIN_3 = 3,
    PIN_4 = 4,
    PIN_5 = 5,
    PIN_6 = 6,
    PIN_21 = 21,
    PIN_22 = 22,
    PIN_23 = 23,
    PIN_24 = 24,
    PIN_25 = 25,
    PIN_27 = 27,
    PIN_28 = 28,
    PIN_29 = 29,
} io_pin_e;

class SN_gpio
{
    private: 
    static SN_gpio *c_instance;

    /**
     * Default constructor for GPIO class. This calls wiringPiSetup()
     * which maps the pins to wiringPi's special mapping
     * 
     * Upon initialization failure the program will crash
     */
    SN_gpio(){
        printf("CONSTRUCTOR CALLED!!!\n");
        wiringPiSetup(); 
        // Setting up first set of pins
        SN_pin_mode(PIN_0, SNOUTPUT);
        SN_pin_mode(PIN_2, SNOUTPUT); 
        SN_pin_mode(PIN_3, SNOUTPUT);
        SN_pin_mode(PIN_21, SNOUTPUT);
        SN_pin_mode(PIN_22, SNOUTPUT);
        SN_pin_mode(PIN_23, SNOUTPUT);
        SN_pin_mode(PIN_24, SNINPUT);

        // Setting up second set of pins
        SN_pin_mode(PIN_1, SNOUTPUT);
        SN_pin_mode(PIN_4, SNOUTPUT);
        SN_pin_mode(PIN_5, SNOUTPUT);
        SN_pin_mode(PIN_6, SNOUTPUT);
        SN_pin_mode(PIN_25, SNOUTPUT);
        SN_pin_mode(PIN_27, SNOUTPUT);
        SN_pin_mode(PIN_28, SNINPUT);
	SN_pin_mode(PIN_29, SNOUTPUT);
	SN_pin_set(PIN_29);
    };
 
    public:   
    typedef enum pin_mode {
        SNOUTPUT = 0,
        SNINPUT,
    } pin_mode_e;

    /** 
     * Sets the mode of the pin to INPUT or OUTPUT
     * 
     * @param pin   pin we are configuring
     * @param mode  mode we are setting, either OUTPUT or INPUT
     */
    void SN_pin_mode(io_pin_e pin, pin_mode_e mode);

    /**
     * Writes HIGH to the specified pin
     *
     * @param pin   pin to set
     */
    void SN_pin_set(io_pin_e pin, bool set = true);

    /**
     * Writes LOW to the specified pin
     * 
     * @param pin   pin to clear
     */
    void SN_pin_unset(io_pin_e pin);

    /**
     * Toggles the specified pin i.e. pin == True set False; pin == False set True
     *
     * @param pin   pin to toggle
     */
    void SN_pin_toggle(io_pin_e pin);

    /**
     * Reads the current value of the pin and returns True for pin HIGH 
     * False for pin LOW
     *
     * @param pin   pin to read
     * @return True for pin HIGH(2.8V ~ 5V); False for pin LOW(0V ~ 2.0V)
     */
    bool SN_pin_read(io_pin_e pin);


    /**
     * Returns the instance of this singleton class. 
     *
     * @return instance of SN_GPIO
     */
    static SN_gpio* instance(void)
    {
        if (!c_instance) 
            c_instance = new SN_gpio;
        return c_instance;
    };
};

