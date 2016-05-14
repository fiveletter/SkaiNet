#include "../sn_gpio.hpp"
#include <wiringPi.h>

SN_gpio* SN_gpio::c_instance = 0;

void SN_gpio::SN_pin_mode(io_pin_e pin, pin_mode_e mode)
{
    if (mode == SNOUTPUT)
        pinMode((int) pin, OUTPUT);
    else
        pinMode((int) pin, INPUT);   
}

void SN_gpio::SN_pin_set(io_pin_e pin)
{
    digitalWrite((int) pin, HIGH);
}

void SN_gpio::SN_pin_unset(io_pin_e pin)
{
    digitalWrite((int) pin, LOW);
}

void SN_gpio::SN_pin_toggle(io_pin_e pin)
{
    bool current_value = digitalRead((int) pin);
    if (current_value)
        digitalWrite((int) pin, LOW);
    else 
        digitalWrite((int) pin, HIGH);
}

bool SN_gpio::SN_pin_read(io_pin_e pin)
{
    return digitalRead((int) pin);
}
