#include "../sn_gpio.hpp"
#include <wiringPi.h>

#ifdef __cplusplus
extern "C"{
#endif

void SN_Gpio::SN_pin_mode(io_pin_e pin, pin_mode_e mode)
{
    pinMode((int) pin, (int) mode);   
}

void SN_Gpio::SN_pin_set(io_pin_e pin)
{
    digitalWrite((int) pin, 1);
}

void SN_Gpio::SN_pin_unset(io_pin_e pin)
{
    digitalWrite((int) pin, 0);
}

void SN_Gpio::SN_pin_toggle(io_pin_e pin)
{
    bool current_value = digitalRead((int) pin);
    digitalWrite((int) pin, !current_value);
}

bool SN_Gpio::SN_pin_read(io_pin_e pin)
{
    return digitalRead((int) pin);
}
#ifdef __cplusplus
}
#endif
