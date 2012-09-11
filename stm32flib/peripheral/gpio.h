#ifndef __GPIO_H__
#define __GPIO_H__

typedef enum {
	GPIO_PA = 0,
	GPIO_PB = 1,
	GPIO_PC = 2,
	GPIO_PD = 3,
	GPIO_PE = 4,
	GPIO_PF = 5,
	GPIO_PG = 6,
} enum_gpio_port;

typedef enum {
	GPIO_PA0 = (GPIO_PA << 4) | 0,
	GPIO_PA1 = (GPIO_PA << 4) | 1,
	GPIO_PA2 = (GPIO_PA << 4) | 2,
	GPIO_PA3 = (GPIO_PA << 4) | 3,
	GPIO_PA4 = (GPIO_PA << 4) | 4,
	GPIO_PA5 = (GPIO_PA << 4) | 5,
	GPIO_PA6 = (GPIO_PA << 4) | 6,
	GPIO_PA7 = (GPIO_PA << 4) | 7,
	GPIO_PA8 = (GPIO_PA << 4) | 8,
	GPIO_PA9 = (GPIO_PA << 4) | 9,
	GPIO_PA10 = (GPIO_PA << 4) | 10,
	GPIO_PA11 = (GPIO_PA << 4) | 11,
	GPIO_PA12 = (GPIO_PA << 4) | 12,
	GPIO_PA13 = (GPIO_PA << 4) | 13,
	GPIO_PA14 = (GPIO_PA << 4) | 14,
	GPIO_PA15 = (GPIO_PA << 4) | 15,
	GPIO_PB0 = (GPIO_PB << 4) | 0,
	GPIO_PB1 = (GPIO_PB << 4) | 1,
	GPIO_PB2 = (GPIO_PB << 4) | 2,
	GPIO_PB3 = (GPIO_PB << 4) | 3,
	GPIO_PB4 = (GPIO_PB << 4) | 4,
	GPIO_PB5 = (GPIO_PB << 4) | 5,
	GPIO_PB6 = (GPIO_PB << 4) | 6,
	GPIO_PB7 = (GPIO_PB << 4) | 7,
	GPIO_PB8 = (GPIO_PB << 4) | 8,
	GPIO_PB9 = (GPIO_PB << 4) | 9,
	GPIO_PB10 = (GPIO_PB << 4) | 10,
	GPIO_PB11 = (GPIO_PB << 4) | 11,
	GPIO_PB12 = (GPIO_PB << 4) | 12,
	GPIO_PB13 = (GPIO_PB << 4) | 13,
	GPIO_PB14 = (GPIO_PB << 4) | 14,
	GPIO_PB15 = (GPIO_PB << 4) | 15,
	GPIO_PC0 = (GPIO_PC << 4) | 0,
	GPIO_PC1 = (GPIO_PC << 4) | 1,
	GPIO_PC2 = (GPIO_PC << 4) | 2,
	GPIO_PC3 = (GPIO_PC << 4) | 3,
	GPIO_PC4 = (GPIO_PC << 4) | 4,
	GPIO_PC5 = (GPIO_PC << 4) | 5,
	GPIO_PC6 = (GPIO_PC << 4) | 6,
	GPIO_PC7 = (GPIO_PC << 4) | 7,
	GPIO_PC8 = (GPIO_PC << 4) | 8,
	GPIO_PC9 = (GPIO_PC << 4) | 9,
	GPIO_PC10 = (GPIO_PC << 4) | 10,
	GPIO_PC11 = (GPIO_PC << 4) | 11,
	GPIO_PC12 = (GPIO_PC << 4) | 12,
	GPIO_PC13 = (GPIO_PC << 4) | 13,
	GPIO_PC14 = (GPIO_PC << 4) | 14,
	GPIO_PC15 = (GPIO_PC << 4) | 15,
	GPIO_PD0 = (GPIO_PD << 4) | 0,
	GPIO_PD1 = (GPIO_PD << 4) | 1,
	GPIO_PD2 = (GPIO_PD << 4) | 2,
	GPIO_PD3 = (GPIO_PD << 4) | 3,
	GPIO_PD4 = (GPIO_PD << 4) | 4,
	GPIO_PD5 = (GPIO_PD << 4) | 5,
	GPIO_PD6 = (GPIO_PD << 4) | 6,
	GPIO_PD7 = (GPIO_PD << 4) | 7,
	GPIO_PD8 = (GPIO_PD << 4) | 8,
	GPIO_PD9 = (GPIO_PD << 4) | 9,
	GPIO_PD10 = (GPIO_PD << 4) | 10,
	GPIO_PD11 = (GPIO_PD << 4) | 11,
	GPIO_PD12 = (GPIO_PD << 4) | 12,
	GPIO_PD13 = (GPIO_PD << 4) | 13,
	GPIO_PD14 = (GPIO_PD << 4) | 14,
	GPIO_PD15 = (GPIO_PD << 4) | 15,
	GPIO_PE0 = (GPIO_PE << 4) | 0,
	GPIO_PE1 = (GPIO_PE << 4) | 1,
	GPIO_PE2 = (GPIO_PE << 4) | 2,
	GPIO_PE3 = (GPIO_PE << 4) | 3,
	GPIO_PE4 = (GPIO_PE << 4) | 4,
	GPIO_PE5 = (GPIO_PE << 4) | 5,
	GPIO_PE6 = (GPIO_PE << 4) | 6,
	GPIO_PE7 = (GPIO_PE << 4) | 7,
	GPIO_PE8 = (GPIO_PE << 4) | 8,
	GPIO_PE9 = (GPIO_PE << 4) | 9,
	GPIO_PE10 = (GPIO_PE << 4) | 10,
	GPIO_PE11 = (GPIO_PE << 4) | 11,
	GPIO_PE12 = (GPIO_PE << 4) | 12,
	GPIO_PE13 = (GPIO_PE << 4) | 13,
	GPIO_PE14 = (GPIO_PE << 4) | 14,
	GPIO_PE15 = (GPIO_PE << 4) | 15,
	GPIO_PF0 = (GPIO_PF << 4) | 0,
	GPIO_PF1 = (GPIO_PF << 4) | 1,
	GPIO_PF2 = (GPIO_PF << 4) | 2,
	GPIO_PF3 = (GPIO_PF << 4) | 3,
	GPIO_PF4 = (GPIO_PF << 4) | 4,
	GPIO_PF5 = (GPIO_PF << 4) | 5,
	GPIO_PF6 = (GPIO_PF << 4) | 6,
	GPIO_PF7 = (GPIO_PF << 4) | 7,
	GPIO_PF8 = (GPIO_PF << 4) | 8,
	GPIO_PF9 = (GPIO_PF << 4) | 9,
	GPIO_PF10 = (GPIO_PF << 4) | 10,
	GPIO_PF11 = (GPIO_PF << 4) | 11,
	GPIO_PF12 = (GPIO_PF << 4) | 12,
	GPIO_PF13 = (GPIO_PF << 4) | 13,
	GPIO_PF14 = (GPIO_PF << 4) | 14,
	GPIO_PF15 = (GPIO_PF << 4) | 15,
	GPIO_PG0 = (GPIO_PG << 4) | 0,
	GPIO_PG1 = (GPIO_PG << 4) | 1,
	GPIO_PG2 = (GPIO_PG << 4) | 2,
	GPIO_PG3 = (GPIO_PG << 4) | 3,
	GPIO_PG4 = (GPIO_PG << 4) | 4,
	GPIO_PG5 = (GPIO_PG << 4) | 5,
	GPIO_PG6 = (GPIO_PG << 4) | 6,
	GPIO_PG7 = (GPIO_PG << 4) | 7,
	GPIO_PG8 = (GPIO_PG << 4) | 8,
	GPIO_PG9 = (GPIO_PG << 4) | 9,
	GPIO_PG10 = (GPIO_PG << 4) | 10,
	GPIO_PG11 = (GPIO_PG << 4) | 11,
	GPIO_PG12 = (GPIO_PG << 4) | 12,
	GPIO_PG13 = (GPIO_PG << 4) | 13,
	GPIO_PG14 = (GPIO_PG << 4) | 14,
	GPIO_PG15 = (GPIO_PG << 4) | 15,
} enum_gpio_pin;

typedef enum {
	GPIO_OUT_PUSHPULL_10MHz = 1,
	GPIO_OUT_PUSHPULL_2MHz = 2,
	GPIO_OUT_PUSHPULL_50MHz = 3,
	GPIO_OUT_OPENDRAIN_10MHz = 5,
	GPIO_OUT_OPENDRAIN_2MHz = 6,
	GPIO_OUT_OPENDRAIN_50MHz = 7,
	GPIO_AFOUT_PUSHPULL_10MHz = 9,
	GPIO_AFOUT_PUSHPULL_2MHz = 10,
	GPIO_AFOUT_PUSHPULL_50MHz = 11,
	GPIO_AFOUT_OPENDRAIN_10MHz = 13,
	GPIO_AFOUT_OPENDRAIN_2MHz = 14,
	GPIO_AFOUT_OPENDRAIN_50MHz = 15,
	GPIO_IN_ANALOG = 0,
	GPIO_IN_FLOAT = 4,
	GPIO_IN_PULLDOWN = 16,
	GPIO_IN_PULLUP = 17,
} enum_gpio_pin_mode;

typedef enum {
	GPIO_PIN_STAT_LOW = 0,
	GPIO_PIN_STAT_HIGH = 1,
} enum_gpio_pin_stat;

#define GPIO_PORT(pin)							((pin)  >> 4)
#define GPIO_PIN_NUMBER(pin)			((pin) & 0x0f)

#ifdef __cplusplus
extern "C" {
#endif

int GPIO_EnablePort(enum_gpio_port port);
int GPIO_DisablePort(enum_gpio_port port);
int GPIO_IsPortEnabled(enum_gpio_port port);
int GPIO_SetPinMode(enum_gpio_pin pin, enum_gpio_pin_mode mode);
int GPIO_GetPinMode(enum_gpio_pin pin);
int GPIO_LockPinMode(enum_gpio_pin pin);
int GPIO_PinOut(enum_gpio_pin pin, enum_gpio_pin_stat stat);
int GPIO_PinOutHigh(enum_gpio_pin pin);
int GPIO_PinOutLow(enum_gpio_pin pin);
int GPIO_PinInvert(enum_gpio_pin pin);
int GPIO_GetPinStat(enum_gpio_pin pin);

#ifdef __cplusplus
}
#endif

#endif // __GPIO_H__
