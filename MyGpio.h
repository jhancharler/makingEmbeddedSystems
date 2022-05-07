#ifndef MY_GPIO_H_INCLUDED
#define MY_GPIO_H_INCLUDED

#include <stdint.h>

typedef struct
{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
} GPIO_typedef;

typedef enum
{
	GPIO_HIGH = 1,
	GPIO_LOW = 0
} GPIO_State_e;
#define IS_GPIO_STATE(state) (((state) == GPIO_HIGH) || ((state) == GPIO_LOW))

typedef enum
{
	GPIO_PIN_0,
	GPIO_PIN_1,
	GPIO_PIN_2,
	GPIO_PIN_3,
	GPIO_PIN_4,
	GPIO_PIN_5,
	GPIO_PIN_6,
	GPIO_PIN_7,
	GPIO_PIN_8,
	GPIO_PIN_9,
	GPIO_PIN_10,
	GPIO_PIN_11,
	GPIO_PIN_12,
	GPIO_PIN_13,
	GPIO_PIN_14,
	GPIO_PIN_15,
	GPIO_PINS_TOTAL
} gpio_pins_e;
#define IS_GPIO_PIN(pin) ((pin) < GPIO_PINS_TOTAL)

typedef enum
{
	GPIO_MODE_INPUT,
	GPIO_MODE_OUTPUT,
	GPIO_MODE_ALT,
	GPIO_MODE_ANALOG
} MODER_e;
#define IS_GPIO_MODE(mode) ((mode) >= GPIO_MODE_INPUT) || ((mode) <= GPIO_MODE_ANALOG))

#define GPIOA_BASE	(0x40020000)
#define GPIOD_BASE	(0x40020C00)

#define GPIOA			((GPIO_typedef*)(GPIOA_BASE))
#define GPIOD			((GPIO_typedef*)(GPIOD_BASE))

void initGPIO(GPIO_typedef* gpio_port, gpio_pins_e pin, MODER_e mode);
void enableGPIO(GPIO_typedef* gpio, gpio_pins_e gpioPin, GPIO_State_e enable);
void toggleGPIO(GPIO_typedef* gpio, gpio_pins_e gpioPin);

GPIO_State_e readGPIO(GPIO_typedef* gpio, gpio_pins_e gpioPin);

#endif
