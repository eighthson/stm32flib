#include "stm32flib.h"

#define RCC_CR												HWREG32(0x40021000)
#define RCC_CR_HSION									BITBEND(0x40021000, 0)
#define RCC_CR_HSIRDY								BITBEND(0x40021000, 1)
#define RCC_CR_HSITRIM_OFFSET				3
#define RCC_CR_HSITRIM_MASK					(0x1F << RCC_CR_HSITRIM_OFFSET)
#define RCC_CR_HSICAL_OFFSET				8
#define RCC_CR_HSICAL_MASK					(0xFF << RCC_CR_HSICAL_OFFSET)
#define RCC_CR_HSEON									BITBEND(0x40021000, 16)
#define RCC_CR_HSERDY								BITBEND(0x40021000, 17)
#define RCC_CR_HSEBYP								BITBEND(0x40021000, 18)
#define RCC_CR_CSSON									BITBEND(0x40021000, 19)
#define RCC_CR_PLLON									BITBEND(0x40021000, 24)
#define RCC_CR_PLLRDY								BITBEND(0x40021000, 25)
#if (defined(STM32F105) || defined(STM32F107))
#define RCC_CR_PLL2ON								BITBEND(0x40021000, 26)
#define RCC_CR_PLL2RDY								BITBEND(0x40021000, 27)
#define RCC_CR_PLL3ON								BITBEND(0x40021000, 28)
#define RCC_CR_PLL3RDY								BITBEND(0x40021000, 29)
#endif
#define RCC_CFGR											HWREG32(0x40021004)
#define RCC_CFGR_SW_OFFSET					0
#define RCC_CFGR_SW_MASK						(0x03 << RCC_CFGR_SW_OFFSET)
#define RCC_CFGR_SWS_OFFSET					2
#define RCC_CFGR_SWS_MASK						(0x03 << RCC_CFGR_SWS_OFFSET)
#define RCC_CFGR_HPRE_OFFSET				4
#define RCC_CFGR_HPRE_MASK					(0x0F << RCC_CFGR_HPRE_OFFSET)
#define RCC_CFGR_PPRE1_OFFSET				8
#define RCC_CFGR_PPRE1_MASK					(0x07 << RCC_CFGR_PPRE1_OFFSET)
#define RCC_CFGR_PPRE2_OFFSET				11
#define RCC_CFGR_PPRE2_MASK					(0x07 << RCC_CFGR_PPRE2_OFFSET)
#define RCC_CFGR_ADCPRE_OFFSET			14
#define RCC_CFGR_ADCPRE_MASK				(0x03 << RCC_CFGR_ADCPRE_OFFSET)
#define RCC_CFGR_PLLSRC							BITBEND(0x40021004, 16)
#define RCC_CFGR_PLLXTPRE						BITBEND(0x40021004, 17)
#define RCC_CFGR_PLLMUL_OFFSET			18
#define RCC_CFGR_PLLMUL_MASK				(0x0F << RCC_CFGR_PLLMUL_OFFSET)
#if (defined(STM32F105) || defined(STM32F107))
#define RCC_CFGR_OTGFSPRE						BITBEND(0x40021004, 22)
#else
#define RCC_CFGR_USBPRE							BITBEND(0x40021004, 22)
#endif
#define RCC_CFGR_MCO_OFFSET					24
#if (defined(STM32F105) || defined(STM32F107))
#define RCC_CFGR_MCO_MASK						(0x0F << RCC_CFGR_MCO_OFFSET)
#else
#define RCC_CFGR_MCO_MASK						(0x07 << RCC_CFGR_MCO_OFFSET)
#endif
#define RCC_CIR												HWREG32(0x40021008)
#define RCC_CIR_LSIRDYF							BITBEND(0x40021008, 0)
#define RCC_CIR_LSERDYF							BITBEND(0x40021008, 1)
#define RCC_CIR_HSIRDYF							BITBEND(0x40021008, 2)
#define RCC_CIR_HSERDYF							BITBEND(0x40021008, 3)
#define RCC_CIR_PLLRDYF							BITBEND(0x40021008, 4)
#define RCC_CIR_CSSF									BITBEND(0x40021008, 7)
#define RCC_CIR_LSIRDYIE						BITBEND(0x40021008, 8)
#define RCC_CIR_LSERDYIE						BITBEND(0x40021008, 9)
#define RCC_CIR_HSIRDYIE						BITBEND(0x40021008, 10)
#define RCC_CIR_HSERDYIE						BITBEND(0x40021008, 11)
#define RCC_CIR_PLLRDYIE						BITBEND(0x40021008, 12)
#if defined(STM32F_CL)
#define RCC_CIR_PLL2RDYIE						BITBEND(0x40021008, 13)
#define RCC_CIR_PLL3RDYIE						BITBEND(0x40021008, 14)
#endif
#define RCC_CIR_LSIRDYC							BITBEND(0x40021008, 16)
#define RCC_CIR_LSERDYC							BITBEND(0x40021008, 17)
#define RCC_CIR_HSIRDYC							BITBEND(0x40021008, 18)
#define RCC_CIR_HSERDYC							BITBEND(0x40021008, 19)
#define RCC_CIR_PLLRDYC							BITBEND(0x40021008, 20)
#if (defined(STM32F105) || defined(STM32F107))
#define RCC_CIR_PLL2RDYC						BITBEND(0x40021008, 21)
#define RCC_CIR_PLL3RDYC						BITBEND(0x40021008, 22)
#endif
#define RCC_CIR_CSSC									BITBEND(0x40021008, 23)
#if (defined(STM32F105) || defined(STM32F107))
#define RCC_CFGR2											HWREG32(0x4002102C)
#define RCC_CFGR2_PREDIV1_OFFSET		0
#define RCC_CFGR2_PREDIV1_MASK			(0x0F << RCC_CFGR2_PREDIV1_OFFSET)
#define RCC_CFGR2_PREDIV2_OFFSET		4
#define RCC_CFGR2_PREDIV2_MASK			(0x0F << RCC_CFGR2_PREDIV2_OFFSET)
#define RCC_CFGR2_PLL2MUL_OFFSET		8
#define RCC_CFGR2_PLL2MUL_MASK			(0x0F << RCC_CFGR2_PLL2MUL_OFFSET)
#define RCC_CFGR2_PLL3MUL_OFFSET		12
#define RCC_CFGR2_PLL3MUL_MASK			(0x0F << RCC_CFGR2_PLL3MUL_OFFSET)
#define RCC_CFGR2_PREDIV1SRC				BITBEND(0x4002102C, 16)
#define RCC_CFGR2_I2S2SRC						BITBEND(0x4002102C, 17)
#define RCC_CFGR2_I2S3SRC						BITBEND(0x4002102C, 18)
#endif
#define RCC_APB1ENR_BKPEN						BITBEND(0x4002101C, 27)
#define RCC_BDCR_LSEON								BITBEND(0x40021020, 0)
#define RCC_BDCR_LSERDY							BITBEND(0x40021020, 1)
#define RCC_CSR_LSION								BITBEND(0x40021024, 0)
#define RCC_CSR_LSIRDY								BITBEND(0x40021024, 1)

int RCC_TurnOnHsi(void) {
	register uint32_t count;

	// Turn on the HSI by setting the bit HSION in RCC_CR register
	// Do DSB & ISB to ensure the operation is actually executed.
	RCC_CR_HSION = 1;
	DSB();

	// Keep checking bit HSIRDY in RCC_CR register until it is set.
	for (count = 0;; count++) {
		if (RCC_CR_HSIRDY)
			break;

		if (count >= 100000L) {
			// If the bit couldn't be set within 100,000 for-loops, turn
			// off the HSI and return -1 to indicate error.
			RCC_CR_HSION = 0;
			DSB();

			return -1;
		}
	}

	return 0;
}

void RCC_TurnOffHsi(void) {
	RCC_CR_HSION = 0;
	DSB();
}

int RCC_IsHsiTurnedOn(void) {
	return RCC_CR_HSIRDY;
}

int RCC_TrimHsi(int trim) {
	register uint32_t cr;

#if defined(DO_PARAM_CHECKING)
	if (trim < -15 || trim > 15)
		return -1;
#endif

	cr = RCC_CR;
	cr &= ~RCC_CR_HSITRIM_MASK;
	cr |= (trim + 16) << RCC_CR_HSITRIM_OFFSET;
	RCC_CR = cr;
	DSB();

	return 0;
}

int RCC_TurnOnHse(void) {
	register uint32_t count;

	if (!XTAL_FREQUENCY)
		return -1;

	// Turn on the HSE by setting the bit HSEON in RCC_CR register
	// Do DSB & ISB to ensure the operation is actually executed.
	RCC_CR_HSEON = 1;
	DSB();

	// Keep checking bit HSERDY in RCC_CR register until it is set.
	for (count = 0;; count++) {
		if (RCC_CR_HSERDY)
			break;

		if (count >= 100000L) {
			// If the bit couldn't be set within 100,000 for-loops, turn
			// off the HSE and return -1 to indicate error.
			RCC_CR_HSEON = 0;
			DSB();

			return -1;
		}
	}

	return 0;
}

void RCC_TurnOffHse(void) {
	RCC_CR_HSEON = 0;
	DSB();
}

int RCC_IsHseTurnedOn(void) {
	return RCC_CR_HSERDY;
}

int RCC_SetPll(enum_pllin pllin, enum_pllmul pllmul) {
	register uint32_t cfgr;

#if defined(DO_PARAM_CHECKING)
#if !(defined(STM32F105) || defined(STM32F107))
	if (pllmul < 0 || pllmul > 14)
		return -1;
#else
	if (!(pllmul >=2 && pllmul <= 7) && (pllmul != 13))
		return -1;
#endif
#endif

	// Check whether the PLL is working. If it is, return -1 to indicate
	// error because the bit-fields which have relationship with the PLL
	// can't be written during the PLL is working.
	if (RCC_CR_PLLON)
		return -1;

	switch (pllin) {
		case HSI_DIV_BY_2_AS_PLLIN:
			RCC_CFGR_PLLSRC = 0;
			break;

#if !(defined(STM32F105) || defined(STM32F107))
		case HSE_AS_PLLIN:
			if (!XTAL_FREQUENCY)
				return -1;

			RCC_CFGR_PLLXTPRE = 0;
			RCC_CFGR_PLLSRC = 1;
			break;

		case HSE_DIV_BY_2_AS_PLLIN:
			if (!XTAL_FREQUENCY)
				return -1;

			RCC_CFGR_PLLXTPRE = 1;
			RCC_CFGR_PLLSRC = 1;
			break;
#else
		case PREDIV1_AS_PLLIN:
			RCC_CFGR_PLLXTPRE = 0;
			RCC_CFGR_PLLSRC = 1;
			break;
#endif

		default:
			return -1;
	}

	cfgr = RCC_CFGR;
	cfgr &= ~(RCC_CFGR_PLLMUL_MASK);
	cfgr |= (pllmul << RCC_CFGR_PLLMUL_OFFSET);
	RCC_CFGR = cfgr;
	DSB();

	return 0;
}

int RCC_TurnOnPll(void) {
	register uint32_t count;

	// Turn on the PLL by setting the bit PLLON in RCC_CR register
	// Do DSB & ISB to ensure the operation is actually executed.
	RCC_CR_PLLON = 1;
	DSB();

	// Keep checking bit PLLRDY in RCC_CR register until it is set.
	for (count = 0;; count++) {
		if (RCC_CR_PLLRDY)
			break;

		// If the bit couldn't be set within 100,000 for-loops, turn
		// off the PLL and return -1 to indicate error.
		if (count >= 100000L) {
			RCC_CR_PLLON = 0;
			DSB();

			return -1;
		}
	}

	return 0;
}

void RCC_TurnOffPll(void) {
	RCC_CR_PLLON = 0;
	DSB();
}

int  RCC_IsPllTurnedOn(void) {
	return RCC_CR_PLLRDY;
}

void RCC_BypassHse(void) {
	RCC_CR_HSEBYP = 1;
	DSB();
}

void RCC_UnbypassHse(void) {
	RCC_CR_HSEBYP = 0;
	DSB();
}

int  RCC_IsHseBypassed(void) {
	return RCC_CR_HSEBYP;
}

void RCC_EnableCss(void) {
	RCC_CR_CSSON = 1;
	DSB();
}

void RCC_DisableCss(void) {
	RCC_CR_CSSON = 0;
	DSB();
}

int RCC_IsCssEnabled(void) {
	return RCC_CR_CSSON;
}

int RCC_SetAhbPsc(enum_ahbpsc psc) {
	register uint32_t cfgr;

#if defined(DO_PARAM_CHECKING)
	if (psc < AHB_PRE_1 || psc > AHB_PRE_512)
		return -1;
#endif

	cfgr = RCC_CFGR;
	cfgr &= ~RCC_CFGR_HPRE_MASK;
	cfgr |= psc << RCC_CFGR_HPRE_OFFSET;
	RCC_CFGR = cfgr;
	DSB();

	return 0;
}

int RCC_SetApb1Psc(enum_apbpsc psc) {
	register uint32_t cfgr;

#if defined(DO_PARAM_CHECKING)
	if (psc < APB_PRE_1 || psc > APB_PRE_16)
		return -1;
#endif

	cfgr = RCC_CFGR;
	cfgr &= ~RCC_CFGR_PPRE1_MASK;
	cfgr |= psc << RCC_CFGR_PPRE1_OFFSET;
	RCC_CFGR = cfgr;
	DSB();

	return 0;
}

int RCC_SetApb2Psc(enum_apbpsc psc) {
	register uint32_t cfgr;

#if defined(DO_PARAM_CHECKING)
	if (psc < APB_PRE_1 || psc > APB_PRE_16)
		return -1;
#endif

	cfgr = RCC_CFGR;
	cfgr &= ~RCC_CFGR_PPRE2_MASK;
	cfgr |= psc << RCC_CFGR_PPRE2_OFFSET;
	RCC_CFGR = cfgr;
	DSB();

	return 0;
}

int RCC_SetAdcPsc(enum_adcpsc psc) {
	register uint32_t cfgr;

#if defined(DO_PARAM_CHECKING)
	if (psc < ADC_PRE_2 || psc > ADC_PRE_8)
		return -1;
#endif

	cfgr = RCC_CFGR;
	cfgr &= ~RCC_CFGR_ADCPRE_MASK;
	cfgr |= psc << RCC_CFGR_ADCPRE_OFFSET;
	RCC_CFGR = cfgr;
	DSB();

	return 0;
}

int RCC_SetSysClk(enum_sysclk sysclk) {
	register uint32_t cfgr;

	switch (sysclk) {
		case HSI_AS_SYSCLK:
			if (!RCC_CR_HSIRDY)
				return -1;
			break;

		case HSE_AS_SYSCLK:
			if (!RCC_CR_HSERDY)
				return -1;
			break;

		case PLL_AS_SYSCLK:
			if (!RCC_CR_PLLRDY)
				return -1;
			break;

		default:
			return -1;
	}

	cfgr = RCC_CFGR;
	cfgr &= ~RCC_CFGR_SW_MASK;
	cfgr |= (sysclk << RCC_CFGR_SW_OFFSET);
	RCC_CFGR = cfgr;
	DSB();

	return 0;
}

int RCC_SetMco(enum_mco mco) {
	register uint32_t cfgr;

#if defined(DO_PARAM_CHECKING)
#if !(defined(STM32F105) || defined(STM32F107))
	if ((mco < SYSCLK_TO_MCO || mco > PLL_DIV_BY_2_TO_MCO) && mco != NONE_TO_MCO)
		return -1;
#else
	if ((mco < SYSCLK_TO_MCO || mco > PLL3_TO_MCO) && mco != NONE_TO_MCO)
		return -1;
#endif
#endif

	GPIO_EnablePort(GPIO_PA);
	if (GPIO_SetPinMode(GPIO_PA8, GPIO_AFOUT_PUSHPULL_50MHz))
		return -1;

	cfgr = RCC_CFGR;
	cfgr &= ~RCC_CFGR_MCO_MASK;
	cfgr |= (mco << RCC_CFGR_MCO_OFFSET);
	RCC_CFGR = cfgr;
	DSB();

	return 0;
}

uint32_t RCC_GetPllClk(void) {
	register uint32_t pllin, pllmul;

	if (RCC_CFGR_PLLSRC)
		pllin = XTAL_FREQUENCY;
	else
		pllin = 4000000L;

	pllmul = ((RCC_CFGR & RCC_CFGR_PLLMUL_MASK) >> RCC_CFGR_PLLMUL_OFFSET) + 2;
	if (pllmul > 16)
		pllmul = 16;

	return pllin * pllmul;
}

uint32_t RCC_GetSysClk(void) {
	switch((RCC_CFGR & RCC_CFGR_SW_MASK) >> RCC_CFGR_SW_OFFSET) {
		case HSI_AS_SYSCLK:
			return (uint32_t)8000000L;

		case HSE_AS_SYSCLK:
			return (uint32_t)XTAL_FREQUENCY;

		case PLL_AS_SYSCLK:
			return RCC_GetPllClk();
	}

	return 0;
}

uint32_t RCC_GetAhbClk(void) {
	register uint32_t psc = (RCC_CFGR & RCC_CFGR_HPRE_MASK) >> RCC_CFGR_HPRE_OFFSET;

	if (psc < 8)
		psc = 1;
	else if (psc < 12)
		psc = 1 << (psc - 7);
	else
		psc = 1 << (psc - 6);

	return RCC_GetSysClk() / psc;
}

uint32_t RCC_GetApb1Clk(void) {
	register uint32_t psc = (RCC_CFGR & RCC_CFGR_PPRE1_MASK) >> RCC_CFGR_PPRE1_OFFSET;

	if (psc < 4)
		psc = 1;
	else
		psc = 1 << (psc - 3);

	return RCC_GetAhbClk() / psc;
}

uint32_t RCC_GetApb2Clk(void) {
	register uint32_t psc = (RCC_CFGR & RCC_CFGR_PPRE2_MASK) >> RCC_CFGR_PPRE2_OFFSET;

	if (psc < 4)
		psc = 1;
	else
		psc = 1 << (psc - 3);

	return RCC_GetAhbClk() / psc;
}

uint32_t _RCC_GetAdcClk(void) {
	register uint32_t psc = (RCC_CFGR & RCC_CFGR_ADCPRE_MASK) >> RCC_CFGR_ADCPRE_OFFSET;
	psc = (psc + 1) * 2;
	return RCC_GetApb2Clk() / psc;
}

#if !(defined(STM32F105) || defined(STM32F107))
int RCC_SetUsbPsc(enum_usbpsc psc) {
	switch (psc) {
		case USB_PRE_1D5:
			RCC_CFGR_USBPRE = 0;
			break;

		case USB_PRE_1:
			RCC_CFGR_USBPRE = 1;
			break;

		default:
			return -1;
	}

	DSB();

	return 0;
}

int RCC_TurnOnLse(void) {
	register uint32_t count;

	RCC_APB1ENR_BKPEN = 1;
	DSB();

	// Turn on the HSI by setting the bit HSION in RCC_CR register
	// Do DSB & ISB to ensure the operation is actually executed.
	RCC_BDCR_LSEON = 1;
	DSB();

	// Keep checking bit HSIRDY in RCC_CR register until it is set.
	for (count = 0;; count++) {
		if (RCC_BDCR_LSERDY)
			break;

		if (count >= 10000000L) {
			// If the bit couldn't be set within 100,000 for-loops, turn
			// off the HSI and return -1 to indicate error.
			RCC_BDCR_LSEON = 0;
			DSB();

			return -1;
		}
	}

	return 0;
}

void RCC_TurnOffLse(void) {
	RCC_BDCR_LSEON = 0;
	DSB();
}

int RCC_IsLseTurnedOn(void) {
	return RCC_BDCR_LSERDY;
}

#else
int RCC_SetPrediv1(enum_prediv1in prediv1in, enum_predivpsc psc) {
#if defined(DO_PARAM_CHECKING)
	if (psc < PREDIV_1 || psc > PREDIV_16)
		return -1;
#endif

	// Check whether the PLL is working. If it is, return -1 to indicate
	// error because the bit-fields which have relationship with the PREDIV1
	// can't be written during the PLL is working.
	if (RCC_CR_PLLON)
		return -1;

	// Do actual setting.
	RCC_CFGR2_PREDIV1SRC = prediv1in;
	RCC_CFGR2 &= !RCC_CFGR2_PREDIV1_MASK;
	RCC_CFGR2 |= (psc << RCC_CFGR2_PREDIV1_OFFSET);
	DSB();

	return 0;
}

int RCC_SetPrediv2(enum_predivpsc psc) {
#if defined(DO_PARAM_CHECKING)
	if (psc < PREDIV_1 || psc > PREDIV_16)
		return -1;
#endif

	// Check whether the PLL2 or PLL3 is working. If one of them is,
	// return -1 to indicate error because the bit-fields which have
	// relationship with the PREDIV2 can't be written during the PLL2
	// or PLL3 is working.
	if (RCC_CR_PLL2ON || RCC_CR_PLL3ON)
		return -1;

	// Do actual setting.
	RCC_CFGR2 &= !RCC_CFGR2_PREDIV2_MASK;
	RCC_CFGR2 |= (psc << RCC_CFGR2_PREDIV2_OFFSET);
	DSB();

	return 0;
}

int RCC_SetPll2(enum_pll2mul mul) {
	// TODO: Add code here to check whether the arguments are validated.

	if (RCC_CR_PLL2ON)
		return -1;

	RCC_CFGR2 &= ~RCC_CFGR2_PLL2MUL_MASK;
	RCC_CFGR2 |= (mul << RCC_CFGR2_PLL2MUL_OFFSET);

	return 0;
}

int RCC_TurnOnPll2(void) {
	register uint32_t count;

	// Turn on the PLL by setting the bit PLLON in RCC_CR register
	// Do DSB & ISB to ensure the operation is actually executed.
	RCC_CR_PLL2ON = 1;
	DSB();

	// Keep checking bit PLLRDY in RCC_CR register until it is set.
	for (count = 0;; count++) {
		if (RCC_CR_PLL2RDY)
			break;

		// If the bit couldn't be set within 100,000 for-loops, turn
		// off the PLL and return -1 to indicate error.
		if (count >= 100000L) {
			RCC_CR_PLL2ON = 0;
			DSB();

			return -1;
		}
	}

	return 0;
}

void RCC_TurnOffPll2(void) {
	RCC_CR_PLL2ON = 0;
	DSB();
}

int RCC_IsPll2TurnedOn(void) {
	return RCC_CR_PLL2RDY;
}

int RCC_SetPll3(enum_pll3mul mul) {
	// TODO: Add code here to check whether the arguments are validated.

	if (RCC_CR_PLL3ON)
		return -1;

	RCC_CFGR2 &= ~RCC_CFGR2_PLL3MUL_MASK;
	RCC_CFGR2 |= (mul << RCC_CFGR2_PLL3MUL_OFFSET);

	return 0;
}

int RCC_TurnOnPll3(void) {
	register uint32_t count;

	// Turn on the PLL by setting the bit PLLON in RCC_CR register
	// Do DSB & ISB to ensure the operation is actually executed.
	RCC_CR_PLL3ON = 1;
	DSB();

	// Keep checking bit PLLRDY in RCC_CR register until it is set.
	for (count = 0;; count++) {
		if (RCC_CR_PLL3RDY)
			break;

		// If the bit couldn't be set within 100,000 for-loops, turn
		// off the PLL and return -1 to indicate error.
		if (count >= 100000L) {
			RCC_CR_PLL3ON = 0;
			DSB();

			return -1;
		}
	}

	return 0;
}

void RCC_TurnOffPll3(void) {
	RCC_CR_PLL3ON = 0;
	DSB();
}

int RCC_IsPll3TurnedOn(void) {
	return RCC_CR_PLL3RDY;
}

int RCC_SetOtgfsPsc(enum_otgfspsc psc) {
	switch (psc) {
		case OTGFS_PRE_1D5:
			RCC_CFGR_OTGFSPRE = 0;
			break;

		case OTGFS_PRE_1:
			RCC_CFGR_OTGFSPRE = 1;
			break;

		default:
			return -1;
	}

	DSB();

	return 0;
}

int RCC_SetI2s2(enum_i2sclk i2s2clk) {
	// TODO: Add code here to check whether the arguments are validated.

	RCC_CFGR2_I2S2SRC = i2s2clk;
	DSB();

	return 0;
}

int RCC_SetI2s3(enum_i2sclk i2s3clk) {
	// TODO: Add code here to check whether the arguments are validated.

	RCC_CFGR2_I2S3SRC = i2s3clk;
	DSB();

	return 0;
}

//uint32_t __attribute__((always_inline)) RCC_GetPLL2clk(void) {
//	return freq_pll2;
//}
//
//uint32_t __attribute__((always_inline)) RCC_GetPLL3clk(void) {
//	return freq_pll3;
//}
//
//uint32_t __attribute__((always_inline)) RCC_GetI2S2clk(void) {
//	return freq_i2s2;
//}
//
//uint32_t __attribute__((always_inline)) RCC_GetI2S3clk(void) {
//	return freq_i2s3;
//}
#endif
