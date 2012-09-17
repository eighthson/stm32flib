#ifndef __AFIO_H__
#define __AFIO_H__

typedef enum {
	SPI1REMAP_PA4_PA5_PA6_PA7 = 0,
	SPI1REMAP_PA15_PB3_PB4_PB5 = 1,
} enum_spi1_remap;

typedef enum {
	I2C1REMAP_PB6_PB7 = 0,
	I2C1REMAP_PB8_PB9 = 1,
} enum_i2c1_remap;

typedef enum {
	USART1REMAP_PA9_PA10 = 0,
	USART1REMAP_PB6_PB7 = 1,
} enum_usart1_remap;

typedef enum {
	USART2REMAP_PA0_PA1_PA2_PA3_PA4 = 0,
	USART2REMAP_PD3_PD4_PD5_PD6_PD7 = 1,
} enum_usart2_remap;

typedef enum {
	USART3REMAP_PB10_PB11_PB12_PB13_PB14 = 0,
	USART3REMAP_PC10_PC11_PC12_PB13_PB14 = 1,
	USART3REMAP_PD8_PD9_PD10_PD11_PD12 = 3,
} enum_usart3_remap;

typedef enum {
	TIM1REMAP_PA12_PA8_PA9_PA10_PA11_PB12_PB13_PB14_PB15 = 0,
	TIM1REMAP_PA12_PA8_PA9_PA10_PA11_PA6_PA7_PB0_PB1 = 1,
	TIM1REMAP_PE7_PE9_PE11_PE13_PE14_PE15_PE8_PE10_PE12 = 3,
} enum_tim1_remap;

typedef enum {
	TIM2REMAP_PA0_PA1_PA2_PA3 = 0,
	TIM2REMAP_PA15_PB3_PA2_PA3 = 1,
	TIM2REMAP_PA0_PA1_PB10_PB11 = 2,
	TIM2REMAP_PA15_PB3_PB10_PB11 = 3,
} enum_tim2_remap;

#if (defined(STM32F105) || defined(STM32F107))
#endif

#ifdef __cplusplus
extern "C" {
#endif

void AFIO_Enable(void);
void AFIO_Disable(void);
int AFIO_IsEnabled(void);

#ifdef __cplusplus
}
#endif

#endif // __AFIO_H__
