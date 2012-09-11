#ifndef __RCC_H__
#define __RCC_H__

typedef enum {
	HSI_AS_SYSCLK = 0,
	HSE_AS_SYSCLK = 1,
	PLL_AS_SYSCLK = 2,
} enum_sysclk;

typedef enum {
	AHB_PRE_1 = 0,
	AHB_PRE_2 = 8,
	AHB_PRE_4 = 9,
	AHB_PRE_8 = 10,
	AHB_PRE_16 = 11,
	AHB_PRE_64 = 12,
	AHB_PRE_128 = 13,
	AHB_PRE_256 = 14,
	AHB_PRE_512 = 15,
} enum_ahbpsc;

typedef enum {
	APB_PRE_1 = 0,
	APB_PRE_2 = 4,
	APB_PRE_4 = 5,
	APB_PRE_8 = 6,
	APB_PRE_16 = 7,
} enum_apbpsc;

typedef enum {
	ADC_PRE_2 = 0,
	ADC_PRE_4 = 1,
	ADC_PRE_6 = 2,
	ADC_PRE_8 = 3,
} enum_adcpsc;

#if !(defined(STM32F105) || defined(STM32F107))
typedef enum {
	HSI_DIV_BY_2_AS_PLLIN = 0,
	HSE_AS_PLLIN = 1,
	HSE_DIV_BY_2_AS_PLLIN = 3,
} enum_pllin;

typedef enum {
	PLL_MUL_2 = 0,
	PLL_MUL_3 = 1,
	PLL_MUL_4 = 2,
	PLL_MUL_5 = 3,
	PLL_MUL_6 = 4,
	PLL_MUL_7 = 5,
	PLL_MUL_8 = 6,
	PLL_MUL_9 = 7,
	PLL_MUL_10 = 8,
	PLL_MUL_11 = 9,
	PLL_MUL_12 = 10,
	PLL_MUL_13 = 11,
	PLL_MUL_14 = 12,
	PLL_MUL_15 = 13,
	PLL_MUL_16 = 14,
} enum_pllmul;

typedef enum {
	NONE_TO_MCO = 0,
	SYSCLK_TO_MCO = 4,
	HSI_TO_MCO = 5,
	HSE_TO_MCO = 6,
	PLL_DIV_BY_2_TO_MCO = 7,
} enum_mco;
#else
typedef enum {
	HSI_DIV_BY_2_AS_PLLIN = 0,
	PREDIV1_AS_PLLIN = 1,
} enum_pllin;

typedef enum {
	PLL_MUL_2 = 0,
	PLL_MUL_3 = 1,
	PLL_MUL_4 = 2,
	PLL_MUL_5 = 3,
	PLL_MUL_6 = 4,
	PLL_MUL_7 = 5,
	PLL_MUL_8 = 6,
	PLL_MUL_9 = 7,
	PLL_MUL_10 = 8,
	PLL_MUL_11 = 9,
	PLL_MUL_12 = 10,
	PLL_MUL_13 = 11,
	PLL_MUL_14 = 12,
	PLL_MUL_6D5 = 13,
	PLL_MUL_16 = 14,
} enum_pllmul;

typedef enum {
	PREDIV_1 = 0,
	PREDIV_2 = 1,
	PREDIV_3 = 2,
	PREDIV_4 = 3,
	PREDIV_5 = 4,
	PREDIV_6 = 5,
	PREDIV_7 = 6,
	PREDIV_8 = 7,
	PREDIV_9 = 8,
	PREDIV_10 = 9,
	PREDIV_11 = 10,
	PREDIV_12 = 11,
	PREDIV_13 = 12,
	PREDIV_14 = 13,
	PREDIV_15 = 14,
	PREDIV_16 = 15,
} enum_predivpsc;

typedef enum {
	PLL2_x8 = 6,
	PLL2_x9 = 7,
	PLL2_x10 = 8,
	PLL2_x11 = 9,
	PLL2_x12 = 10,
	PLL2_x13 = 11,
	PLL2_x14 = 12,
	PLL2_x16 = 14,
	PLL2_x20 = 15,
} enum_pll2mul;

typedef enum {
	PLL3_x8 = 6,
	PLL3_x9 = 7,
	PLL3_x10 = 8,
	PLL3_x11 = 9,
	PLL3_x12 = 10,
	PLL3_x13 = 11,
	PLL3_x14 = 12,
	PLL3_x16 = 14,
	PLL3_x20 = 15,
} enum_pll3mul;

typedef enum {
	OTGFS_PRE_1D5 = 0,
	OTGFS_PRE_1 = 1,
} enum_otgfspsc;

typedef enum {
	HSE_AS_PREDIV1IN = 0,
	PLL2_AS_PREDIV1IN = 1,
} enum_prediv1in;

typedef enum {
	NONE_TO_MCO = 0,
	SYSCLK_TO_MCO = 4,
	HSI_TO_MCO = 5,
	HSE_TO_MCO = 6,
	PLL_DIV_BY_2_TO_MCO = 7,
	PLL2_TO_MCO = 8,
	PLL3_DIV_BY_2_TO_MCO = 9,
	XT1_TO_MCO = 10,
	PLL3_TO_MCO = 11,
} enum_mco;
#endif

typedef enum {
	USB_PRE_1D5 = 0,
	USB_PRE_1 = 1,
} enum_usbpsc;

typedef enum {
	SYSCLK_AS_I2SCLK = 0,
	Pll3_AS_I2SCLK = 1,
} enum_i2sclk;

#ifdef __cplusplus
extern "C" {
#endif
int RCC_TurnOnHsi(void);
void RCC_TurnOffHsi(void);
int RCC_IsHsiTurnedOn(void);
int RCC_TrimHsi(int trim);
int RCC_TurnOnHse(void);
void RCC_TurnOffHse(void);
int RCC_IsHseTurnedOn(void);
void RCC_BypassHse(void);
void RCC_UnbypassHse(void);
int RCC_IsHseBypassed(void);
int RCC_SetPll(enum_pllin pllin, enum_pllmul pllmul);
int RCC_TurnOnPll(void);
void RCC_TurnOffPll(void);
int RCC_IsPllTurnedOn(void);
void RCC_EnableCss(void);
void RCC_DisableCss(void);
int RCC_IsCssEnabled(void);
int RCC_SetAhbPsc(enum_ahbpsc psc);
int RCC_SetApb1Psc(enum_apbpsc psc);
int RCC_SetApb2Psc(enum_apbpsc psc);
int RCC_SetAdcPsc(enum_adcpsc psc);
int RCC_SetSysClk(enum_sysclk sysclk);
int RCC_SetMco(enum_mco mco);
uint32_t RCC_GetPllClk(void);
uint32_t RCC_GetSysClk(void);
uint32_t RCC_GetAhbClk(void);
uint32_t RCC_GetApb1Clk(void);
uint32_t RCC_GetApb2Clk(void);
uint32_t RCC_GetAdcClk(void);
int RCC_TurnOnLse(void);
void RCC_TurnOffLse(void);
int RCC_IsLseTurnedOn(void);
#if !(defined(STM32F105) || defined(STM32F107))
int RCC_SetUSBPsc(enum_usbpsc psc);
#else
int RCC_SetPrediv1(enum_prediv1in prediv1in, enum_predivpsc psc);
int RCC_SetPrediv2(enum_predivpsc psc);
int RCC_SetPll2(enum_pll2mul mul);
int RCC_TurnOnPll2(void);
void RCC_TurnOffPll2(void);
int RCC_IsPll2TurnedOn(void);
int RCC_SetPll3(enum_pll3mul mul);
int RCC_TurnOnPll3(void);
void RCC_TurnOffPll3(void);
int RCC_IsPll3TurnedOn(void);
int RCC_SetI2s2(enum_i2sclk i2s2clk);
int RCC_SetI2s3(enum_i2sclk i2s3clk);
int RCC_SetOtgfspsc(enum_otgfspsc psc);
uint32_t RCC_GetPll2Clk(void);
uint32_t RCC_GetPll3Clk(void);
uint32_t RCC_GetI2S2Clk(void);
uint32_t RCC_GetI2S3Clk(void);
#endif
#ifdef __cplusplus
}
#endif

#endif // __RCC_H__
