#ifndef _GPIO_H_
#define _GPIO_H_

#include <global.h>


//enum gpio_direction
//{
//	gpio_input=0,
//	gpio_output
//};
//
//enum gpio_pin
//{
//	gpio_pin0=0,
//	gpio_pin1,
//	gpio_pin2,
//	gpio_pin3,
//	gpio_pin4,
//	gpio_pin5,
//	gpio_pin6,
//	gpio_pin7,
//	gpio_pin8,
//	gpio_pin9,
//	gpio_pin10,
//	gpio_pin11,
//	gpio_pin12,
//	gpio_pin13,
//	gpio_pin14,
//	gpio_pin15,
//};

void gpio_init(void);
void gpioHDDAledBlink(byte enable);
void gpioGPIO5LEDEnable(byte enable);
void gpioGPIO14ledBlink(byte enable);
void gpioGPIO7LEDEnable(byte enable);
//void gpio_set_pin_direction(enum gpio_pin, enum gpio_direction);
//void gpio_set_pin_data(enum gpio_pin, int val /* 0 or 1 */);
void gpio_set_pin_direction(byte, byte);
void gpio_set_pin_data(byte, byte /* 0 or 1 */);
byte bGpioIICreadG781(void);
byte bGpioMinTemp(void);
byte bGpioMaxTemp(void);
extern byte bGpioIICreadTempure(void);
extern byte bGpioIICSMARTTempure(void);
#endif

