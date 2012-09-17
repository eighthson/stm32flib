#include "stm32flib.h"

#define RCC_CR												0x40021000
#define RCC_CR_HSION									0
#define RCC_CR_HSIRDY									1
#define RCC_CR_HSITRIM_0							3
#define RCC_CR_HSITRIM_1							3
#define RCC_CR_HSITRIM_2							3
#define RCC_CR_HSITRIM_3							3
#define RCC_CR_HSITRIM_4							3
#define RCC_CR_HSITRIM_MASK						(0x1F << RCC_CR_HSITRIM_0)
#define RCC_CR_HSICAL_0								8
#define RCC_CR_HSICAL_1								9
#define RCC_CR_HSICAL_2								10
#define RCC_CR_HSICAL_3								11
#define RCC_CR_HSICAL_4								12
#define RCC_CR_HSICAL_5								13
#define RCC_CR_HSICAL_6								14
#define RCC_CR_HSICAL_7								15
#define RCC_CR_HSICAL_MASK						(0xFF << RCC_CR_HSICAL_0)
#define RCC_CR_HSEON									16
#define RCC_CR_HSERDY									17
#define RCC_CR_HSEBYP									18
#define RCC_CR_CSSON									19
#define RCC_CR_PLLON									24
#define RCC_CR_PLLRDY									25
#if (defined(STM32F105) || defined(STM32F107))
#define RCC_CR_PLL2ON									26
#define RCC_CR_PLL2RDY								27
#define RCC_CR_PLL3ON									28
#define RCC_CR_PLL3RDY								29
#endif

#define RCC_CFGR											0x40021004
#define RCC_CFGR_SW_0									0
#define RCC_CFGR_SW_1									1
#define RCC_CFGR_SW_MASK							(0x03 << RCC_CFGR_SW_0)
#define RCC_CFGR_SWS_0								2
#define RCC_CFGR_SWS_1								3
#define RCC_CFGR_SWS_MASK							(0x03 << RCC_CFGR_SWS_0)
#define RCC_CFGR_HPRE_0								4
#define RCC_CFGR_HPRE_1								5
#define RCC_CFGR_HPRE_2								6
#define RCC_CFGR_HPRE_3								7
#define RCC_CFGR_HPRE_MASK						(0x0F << RCC_CFGR_HPRE_0)
#define RCC_CFGR_PPRE1_0							8
#define RCC_CFGR_PPRE1_1							9
#define RCC_CFGR_PPRE1_2							10
#define RCC_CFGR_PPRE1_MASK						(0x07 << RCC_CFGR_PPRE1_0)
#define RCC_CFGR_PPRE2_0							11
#define RCC_CFGR_PPRE2_1							12
#define RCC_CFGR_PPRE2_2							13
#define RCC_CFGR_PPRE2_MASK						(0x07 << RCC_CFGR_PPRE2_0)
#define RCC_CFGR_ADCPRE_0							14
#define RCC_CFGR_ADCPRE_1							15
#define RCC_CFGR_ADCPRE_MASK					(0x03 << RCC_CFGR_ADCPRE_0)
#define RCC_CFGR_PLLSRC								16
#define RCC_CFGR_PLLXTPRE							17
#define RCC_CFGR_PLLMUL_0							18
#define RCC_CFGR_PLLMUL_1							19
#define RCC_CFGR_PLLMUL_2							20
#define RCC_CFGR_PLLMUL_3							21
#define RCC_CFGR_PLLMUL_MASK					(0x0F << RCC_CFGR_PLLMUL_0)
#if (defined(STM32F105) || defined(STM32F107))
#define RCC_CFGR_OTGFSPRE							22
#else
#define RCC_CFGR_USBPRE								22
#endif
#define RCC_CFGR_MCO_0								24
#define RCC_CFGR_MCO_1								25
#define RCC_CFGR_MCO_2								26
#if (defined(STM32F105) || defined(STM32F107))
#define RCC_CFGR_MCO_3								27
#define RCC_CFGR_MCO_MASK							(0x0F << RCC_CFGR_MCO_0)
#else
#define RCC_CFGR_MCO_MASK							(0x07 << RCC_CFGR_MCO_0)
#endif

#define RCC_CIR												0x40021008
#define RCC_CIR_LSIRDYF								0
#define RCC_CIR_LSERDYF								1
#define RCC_CIR_HSIRDYF								2
#define RCC_CIR_HSERDYF								3
#define RCC_CIR_PLLRDYF								4
#define RCC_CIR_CSSF									7
#define RCC_CIR_LSIRDYIE							8
#define RCC_CIR_LSERDYIE							9
#define RCC_CIR_HSIRDYIE							10
#define RCC_CIR_HSERDYIE							11
#define RCC_CIR_PLLRDYIE							12
#if (defined(STM32F105) || defined(STM32F107))
#define RCC_CIR_PLL2RDYIE							13
#define RCC_CIR_PLL3RDYIE							14
#endif
#define RCC_CIR_LSIRDYC								16
#define RCC_CIR_LSERDYC								17
#define RCC_CIR_HSIRDYC								18
#define RCC_CIR_HSERDYC								19
#define RCC_CIR_PLLRDYC								20
#if (defined(STM32F105) || defined(STM32F107))
#define RCC_CIR_PLL2RDYC							21
#define RCC_CIR_PLL3RDYC							22
#endif
#define RCC_CIR_CSSC									23

#if (defined(STM32F105) || defined(STM32F107))
#define RCC_CFGR2											0x4002102C
#define RCC_CFGR2_PREDIV1_0						0
#define RCC_CFGR2_PREDIV1_1						1
#define RCC_CFGR2_PREDIV1_2						2
#define RCC_CFGR2_PREDIV1_3						3
#define RCC_CFGR2_PREDIV1_MASK				(0x0F << RCC_CFGR2_PREDIV1_0)
#define RCC_CFGR2_PREDIV2_0						4
#define RCC_CFGR2_PREDIV2_1						5
#define RCC_CFGR2_PREDIV2_2						6
#define RCC_CFGR2_PREDIV2_3						7
#define RCC_CFGR2_PREDIV2_MASK				(0x0F << RCC_CFGR2_PREDIV2_0)
#define RCC_CFGR2_PLL2MUL_0						8
#define RCC_CFGR2_PLL2MUL_1						9
#define RCC_CFGR2_PLL2MUL_2						10
#define RCC_CFGR2_PLL2MUL_3						11
#define RCC_CFGR2_PLL2MUL_MASK				(0x0F << RCC_CFGR2_PLL2MUL_0)
#define RCC_CFGR2_PLL3MUL_0						12
#define RCC_CFGR2_PLL3MUL_1						13
#define RCC_CFGR2_PLL3MUL_2						14
#define RCC_CFGR2_PLL3MUL_3						15
#define RCC_CFGR2_PLL3MUL_MASK				(0x0F << RCC_CFGR2_PLL3MUL_0)
#define RCC_CFGR2_PREDIV1SRC					16
#define RCC_CFGR2_I2S2SRC							17
#define RCC_CFGR2_I2S3SRC							18
#endif

#define RCC_APB1ENR										0x4002101C
#define RCC_APB1ENR_BKPEN							27

#define RCC_BDCR											0x40021020
#define RCC_BDCR_LSEON								0
#define RCC_BDCR_LSERDY								1

#define RCC_CSR												0x40021024
#define RCC_CSR_LSION									0
#define RCC_CSR_LSIRDY								1

int RCC_TurnOnHsi(void) {
	register uint32_t count;

	// Turn on the HSI by setting the bit HSION in RCC_CR register
	// Do DSB & ISB to ensure the operation is actually executed.
	BITBEND_SET(RCC_CR, RCC_CR_HSION, 1);

	// Keep checking bit HSIRDY in RCC_CR register until it is set.
	for (count = 0;; count++) {
		if (BITBEND(RCC_CR, RCC_CR_HSIRDY))
			break;

		if (count >= 100000L) {
			// If the bit couldn't be set within 100,000 for-loops, turn
			// off the HSI and return -1 to indicate error.
			BITBEND_SET(RCC_CR, RCC_CR_HSION, 0);

			return -1;
		}
	}

	return 0;
}

void RCC_TurnOffHsi(void) {
	BITBEND_SET(RCC_CR, RCC_CR_HSION, 0);
}

int RCC_IsHsiTurnedOn(void) {
	return BITBEND(RCC_CR, RCC_CR_HSIRDY);
}

int RCC_TrimHsi(int trim) {
	register uint32_t reg;

#if defined(DO_PARAM_CHECKING)
	if (trim < -15 || trim > 15)
		return -1;
#endif

	reg = HWREG32(RCC_CR);
	reg &= ~RCC_CR_HSITRIM_MASK;
	reg |= (trim + 16) << RCC_CR_HSITRIM_0;
	HWREG32_SET(RCC_CR, reg);

	return 0;
}

int RCC_TurnOnHse(void) {
	register uint32_t count;

	if (!XTAL_FREQUENCY)
		return -1;

	// Turn on the HSE by setting the bit HSEON in RCC_CR register
	// Do DSB & ISB to ensure the operation is actually executed.
	BITBEND_SET(RCC_CR, RCC_CR_HSEON, 1);

	// Keep checking bit HSERDY in RCC_CR register until it is set.
	for (count = 0;; count++) {
		if (BITBEND(RCC_CR, RCC_CR_HSERDY))
			break;

		if (count >= 100000L) {
			// If the bit couldn't be set within 100,000 for-loops, turn
			// off the HSE and return -1 to indicate error.
			BITBEND_SET(RCC_CR, RCC_CR_HSEON, 0);

			return -1;
		}
	}

	return 0;
}

void RCC_TurnOffHse(void) {
	BITBEND_SET(RCC_CR, RCC_CR_HSEON, 1);
}

int RCC_IsHseTurnedOn(void) {
	return BITBEND(RCC_CR, RCC_CR_HSERDY);
}

int RCC_SetPll(enum_pllin pllin, enum_pllmul pllmul) {
	register uint32_t reg;

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
	if (BITBEND(RCC_CR, RCC_CR_PLLON))
		return -1;

	switch (pllin) {
		case HSI_DIV_BY_2_AS_PLLIN:
			BITBEND_SET(RCC_CFGR, RCC_CFGR_PLLSRC, 0);
			break;

#if !(defined(STM32F105) || defined(STM32F107))
		case HSE_AS_PLLIN:
			if (!XTAL_FREQUENCY)
				return -1;

			BITBEND_SET(RCC_CFGR, RCC_CFGR_PLLXTPRE, 0);
			BITBEND_SET(RCC_CFGR, RCC_CFGR_PLLSRC, 1);
			break;

		case HSE_DIV_BY_2_AS_PLLIN:
			if (!XTAL_FREQUENCY)
				return -1;

			BITBEND_SET(RCC_CFGR, RCC_CFGR_PLLXTPRE, 1);
			BITBEND_SET(RCC_CFGR, RCC_CFGR_PLLSRC, 1);
			break;
#else
		case PREDIV1_AS_PLLIN:
			BITBEND_SET(RCC_CFGR, RCC_CFGR_PLLXTPRE, 0);
			BITBEND_SET(RCC_CFGR, RCC_CFGR_PLLSRC, 1);
			break;
#endif

		default:
			return -1;
	}

	reg = HWREG32(RCC_CFGR);
	reg &= ~(RCC_CFGR_PLLMUL_MASK);
	reg |= (pllmul << RCC_CFGR_PLLMUL_0);
	HWREG32_SET(RCC_CFGR, reg);

	return 0;
}

int RCC_TurnOnPll(void) {
	register uint32_t count;

	// Turn on the PLL by setting the bit PLLON in RCC_CR register
	// Do DSB & ISB to ensure the operation is actually executed.
	BITBEND_SET(RCC_CR, RCC_CR_PLLON, 1);

	// Keep checking bit PLLRDY in RCC_CR register until it is set.
	for (count = 0;; count++) {
		if (BITBEND(RCC_CR, RCC_CR_PLLRDY))
			break;

		// If the bit couldn't be set within 100,000 for-loops, turn
		// off the PLL and return -1 to indicate error.
		if (count >= 100000L) {
			BITBEND_SET(RCC_CR, RCC_CR_PLLON, 0);

			return -1;
		}
	}

	return 0;
}

void RCC_TurnOffPll(void) {
	BITBEND_SET(RCC_CR, RCC_CR_PLLON, 0);
}

int  RCC_IsPllTurnedOn(void) {
	return BITBEND(RCC_CR, RCC_CR_PLLRDY);
}

void RCC_BypassHse(void) {
	BITBEND_SET(RCC_CR, RCC_CR_HSEBYP, 1);
}

void RCC_UnbypassHse(void) {
	BITBEND_SET(RCC_CR, RCC_CR_HSEBYP, 0);
}

int  RCC_IsHseBypassed(void) {
	return BITBEND(RCC_CR, RCC_CR_HSEBYP);
}

void RCC_EnableCss(void) {
	BITBEND_SET(RCC_CR, RCC_CR_CSSON, 1);
}

void RCC_DisableCss(void) {
	BITBEND_SET(RCC_CR, RCC_CR_CSSON, 0);
}

int RCC_IsCssEnabled(void) {
	return BITBEND(RCC_CR, RCC_CR_CSSON);
}

int RCC_SetAhbPsc(enum_ahbpsc psc) {
	register uint32_t reg;

#if defined(DO_PARAM_CHECKING)
	if (psc < AHB_PRE_1 || psc > AHB_PRE_512)
		return -1;
#endif

	reg = HWREG32(RCC_CFGR);
	reg &= ~RCC_CFGR_HPRE_MASK;
	reg |= psc << RCC_CFGR_HPRE_0;
	HWREG32_SET(RCC_CFGR, reg);

	return 0;
}

int RCC_SetApb1Psc(enum_apbpsc psc) {
	register uint32_t reg;

#if defined(DO_PARAM_CHECKING)
	if (psc < APB_PRE_1 || psc > APB_PRE_16)
		return -1;
#endif

	reg = HWREG32(RCC_CFGR);
	reg &= ~RCC_CFGR_PPRE1_MASK;
	reg |= psc << RCC_CFGR_PPRE1_0;
	HWREG32_SET(RCC_CFGR, reg);

	return 0;
}

int RCC_SetApb2Psc(enum_apbpsc psc) {
	register uint32_t reg;

#if defined(DO_PARAM_CHECKING)
	if (psc < APB_PRE_1 || psc > APB_PRE_16)
		return -1;
#endif

	reg = HWREG32(RCC_CFGR);
	reg &= ~RCC_CFGR_PPRE2_MASK;
	reg |= psc << RCC_CFGR_PPRE2_0;
	HWREG32_SET(RCC_CFGR, reg);

	return 0;
}

int RCC_SetAdcPsc(enum_adcpsc psc) {
	register uint32_t reg;

#if defined(DO_PARAM_CHECKING)
	if (psc < ADC_PRE_2 || psc > ADC_PRE_8)
		return -1;
#endif

	reg = HWREG32(RCC_CFGR);
	reg &= ~RCC_CFGR_ADCPRE_MASK;
	reg |= psc << RCC_CFGR_ADCPRE_0;
	HWREG32_SET(RCC_CFGR, reg);

	return 0;
}

int RCC_SetSysClk(enum_sysclk sysclk) {
	register uint32_t reg;

	switch (sysclk) {
		case HSI_AS_SYSCLK:
			if (!BITBEND(RCC_CR, RCC_CR_HSIRDY))
				return -1;
			break;

		case HSE_AS_SYSCLK:
			if (!BITBEND(RCC_CR, RCC_CR_HSERDY))
				return -1;
			break;

		case PLL_AS_SYSCLK:
			if (!BITBEND(RCC_CR, RCC_CR_PLLRDY))
				return -1;
			break;

		default:
			return -1;
	}

	reg = HWREG32(RCC_CFGR);
	reg &= ~RCC_CFGR_SW_MASK;
	reg |= (sysclk << RCC_CFGR_SW_0);
	HWREG32_SET(RCC_CFGR, reg);

	return 0;
}

int RCC_SetMco(enum_mco mco) {
	register uint32_t reg;

#if defined(DO_PARAM_CHECKING)
#if !(defined(STM32F105) || defined(STM32F107))
	if ((mco < SYSCLK_TO_MCO || mco > PLL_DIV_BY_2_TO_MCO) && mco != NONE_TO_MCO)
		return -1;
#else
	if ((mco < SYSCLK_TO_MCO || mco > PLL3_TO_MCO) && mco != NONE_TO_MCO)
		return -1;
#endif
#endif

	reg = HWREG32(RCC_CFGR);
	reg &= ~RCC_CFGR_MCO_MASK;
	reg |= (mco << RCC_CFGR_MCO_0);
	HWREG32_SET(RCC_CFGR, reg);

	return 0;
}

uint32_t RCC_GetPllClk(void) {
	register uint32_t pllin, pllmul;

#if !(defined(STM32F105) || defined(STM32F107))
	if (BITBEND(RCC_CFGR, RCC_CFGR_PLLSRC)) {
		if (BITBEND(RCC_CFGR, RCC_CFGR_PLLXTPRE))
			pllin = XTAL_FREQUENCY / 2;
		else
			pllin = XTAL_FREQUENCY;
	} else
		pllin = 4000000L;
#else
	if (BITBEND(RCC_CFGR2, RCC_CFGR2_PREDIV1SRC))
		pllin = RCC_GetPll2Clk();
	else
		pllin = XTAL_FREQUENCY;

	pllin /= ((HWREG32(RCC_CFGR2) & RCC_CFGR2_PREDIV1_MASK) >> RCC_CFGR2_PREDIV1_0) + 1;

	if (BITBEND(RCC_CFGR, RCC_CFGR_PLLSRC)) {
		if (BITBEND(RCC_CFGR, RCC_CFGR_PLLXTPRE))
			pllin = pllin / 2;
	} else
		pllin = 4000000L;
#endif

	pllmul = ((HWREG32(RCC_CFGR) & RCC_CFGR_PLLMUL_MASK) >> RCC_CFGR_PLLMUL_0) + 2;
	if (pllmul > 16)
		pllmul = 16;

	return pllin * pllmul;
}

uint32_t RCC_GetSysClk(void) {
	switch((HWREG32(RCC_CFGR) & RCC_CFGR_SW_MASK) >> RCC_CFGR_SW_0) {
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
	register uint32_t psc;

	psc = (HWREG32(RCC_CFGR) & RCC_CFGR_HPRE_MASK) >> RCC_CFGR_HPRE_0;

	if (psc < 8)
		psc = 1;
	else if (psc < 12)
		psc = 1 << (psc - 7);
	else
		psc = 1 << (psc - 6);

	return RCC_GetSysClk() / psc;
}

uint32_t RCC_GetApb1Clk(void) {
	register uint32_t psc;

	psc = (HWREG32(RCC_CFGR) & RCC_CFGR_PPRE1_MASK) >> RCC_CFGR_PPRE1_0;

	if (psc < 4)
		psc = 1;
	else
		psc = 1 << (psc - 3);

	return RCC_GetAhbClk() / psc;
}

uint32_t RCC_GetApb2Clk(void) {
	register uint32_t psc;

	psc = (HWREG32(RCC_CFGR) & RCC_CFGR_PPRE2_MASK) >> RCC_CFGR_PPRE2_0;

	if (psc < 4)
		psc = 1;
	else
		psc = 1 << (psc - 3);

	return RCC_GetAhbClk() / psc;
}

uint32_t _RCC_GetAdcClk(void) {
	register uint32_t psc;

	psc = (HWREG32(RCC_CFGR) & RCC_CFGR_ADCPRE_MASK) >> RCC_CFGR_ADCPRE_0;
	psc = (psc + 1) * 2;

	return RCC_GetApb2Clk() / psc;
}

#if !(defined(STM32F105) || defined(STM32F107))
int RCC_SetUsbPsc(enum_usbpsc psc) {
	switch (psc) {
		case USB_PRE_1D5:
			BITBEND_SET(RCC_CFGR, RCC_CFGR_USBPRE, 0);
			break;

		case USB_PRE_1:
			BITBEND_SET(RCC_CFGR, RCC_CFGR_USBPRE, 1);
			break;

		default:
			return -1;
	}

	return 0;
}

int RCC_TurnOnLse(void) {
	register uint32_t count;

	BITBEND_SET(RCC_APB1ENR, RCC_APB1ENR_BKPEN, 1);

	// Turn on the HSI by setting the bit HSION in RCC_CR register
	// Do DSB & ISB to ensure the operation is actually executed.
	BITBEND_SET(RCC_BDCR, RCC_BDCR_LSEON, 1);

	// Keep checking bit HSIRDY in RCC_CR register until it is set.
	for (count = 0;; count++) {
		if (RCC_BDCR_LSERDY)
			break;

		if (count >= 10000000L) {
			// If the bit couldn't be set within 100,000 for-loops, turn
			// off the HSI and return -1 to indicate error.
			BITBEND_SET(RCC_BDCR, RCC_BDCR_LSEON, 0);

			return -1;
		}
	}

	return 0;
}

void RCC_TurnOffLse(void) {
	BITBEND_SET(RCC_BDCR, RCC_BDCR_LSEON, 0);
}

int RCC_IsLseTurnedOn(void) {
	return BITBEND(RCC_BDCR, RCC_BDCR_LSEON);
}

#else
int RCC_SetPrediv1(enum_prediv1in prediv1in, enum_predivpsc psc) {
	register uint32_t reg;

#if defined(DO_PARAM_CHECKING)
	if (psc < PREDIV_1 || psc > PREDIV_16)
		return -1;
#endif

	// Check whether the PLL is working. If it is, return -1 to indicate
	// error because the bit-fields which have relationship with the PREDIV1
	// can't be written during the PLL is working.
	if (BITBEND(RCC_CR, RCC_CR_PLLON))
		return -1;

	// Do actual setting.
	reg = HWREG32(RCC_CFGR2);
	reg &= ~RCC_CFGR2_PREDIV1_MASK;
	reg |= (psc << RCC_CFGR2_PREDIV1_0);
	HWREG32_SET(RCC_CFGR2, reg);

	BITBEND_SET(RCC_CFGR2, RCC_CFGR2_PREDIV1SRC, prediv1in);

	return 0;
}

int RCC_SetPrediv2(enum_predivpsc psc) {
	register uint32_t reg;

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
	reg = HWREG32(RCC_CFGR2);
	reg &= !RCC_CFGR2_PREDIV2_MASK;
	reg |= (psc << RCC_CFGR2_PREDIV2_0);
	HWREG32_SET(RCC_CFGR2, reg);

	return 0;
}

int RCC_SetPll2(enum_pll2mul mul) {
	register uint32_t reg;

#if defined(DO_PARAM_CHECKING)
	if (mul < PLL2_x8 || mul > PLL2_x20)
		return -1;
#endif

	if (BITBEND(RCC_CR, RCC_CR_PLL2ON))
		return -1;

	reg = HWREG32(RCC_CFGR2);
	reg &= ~RCC_CFGR2_PLL2MUL_MASK;
	reg |= (mul << RCC_CFGR2_PLL2MUL_0);
	HWREG32_SET(RCC_CFGR2, reg);

	return 0;
}

int RCC_TurnOnPll2(void) {
	register uint32_t count;

	// Turn on the PLL by setting the bit PLLON in RCC_CR register
	// Do DSB & ISB to ensure the operation is actually executed.
	BITBEND_SET(RCC_CR, RCC_CR_PLL2ON, 1);

	// Keep checking bit PLLRDY in RCC_CR register until it is set.
	for (count = 0;; count++) {
		if (BITBEND(RCC_CR, RCC_CR_PLL2RDY))
			break;

		// If the bit couldn't be set within 100,000 for-loops, turn
		// off the PLL and return -1 to indicate error.
		if (count >= 100000L) {
			BITBEND_SET(RCC_CR, RCC_CR_PLL2ON, 0);

			return -1;
		}
	}

	return 0;
}

void RCC_TurnOffPll2(void) {
	BITBEND_SET(RCC_CR, RCC_CR_PLL2ON, 0);
}

int RCC_IsPll2TurnedOn(void) {
	return BITBEND(RCC_CFGR2, RCC_CR_PLL2RDY);
}

int RCC_SetPll3(enum_pll3mul mul) {
	register uint32_t reg;

	#if defined(DO_PARAM_CHECKING)
		if (mul < PLL3_x8 || mul > PLL3_x20)
			return -1;
	#endif

	if (BITBEND(RCC_CR, RCC_CR_PLL3ON))
		return -1;

	reg = HWREG32(RCC_CFGR2);
	reg &= ~RCC_CFGR2_PLL3MUL_MASK;
	reg |= (mul << RCC_CFGR2_PLL3MUL_0);
	HWREG32_SET(RCC_CFGR2, reg);

	return 0;
}

int RCC_TurnOnPll3(void) {
	register uint32_t count;

	// Turn on the PLL by setting the bit PLLON in RCC_CR register
	// Do DSB & ISB to ensure the operation is actually executed.
	BITBEND_SET(RCC_CR, RCC_CR_PLL3ON, 1);

	// Keep checking bit PLLRDY in RCC_CR register until it is set.
	for (count = 0;; count++) {
		if (BITBEND(RCC_CR, RCC_CR_PLL3RDY))
			break;

		// If the bit couldn't be set within 100,000 for-loops, turn
		// off the PLL and return -1 to indicate error.
		if (count >= 100000L) {
			BITBEND_SET(RCC_CR, RCC_CR_PLL3ON, 0);

			return -1;
		}
	}

	return 0;
}

void RCC_TurnOffPll3(void) {
	BITBEND_SET(RCC_CR, RCC_CR_PLL3ON, 0);
}

int RCC_IsPll3TurnedOn(void) {
	return BITBEND(RCC_CR, RCC_CR_PLL3ON);
}

int RCC_SetOtgfsPsc(enum_otgfspsc psc) {
	switch (psc) {
		case OTGFS_PRE_1D5:
			BITBEND_SET(RCC_CFGR, RCC_CFGR_OTGFSPRE, 0);
			break;

		case OTGFS_PRE_1:
			BITBEND_SET(RCC_CFGR, RCC_CFGR_OTGFSPRE, 1);
			break;

		default:
			return -1;
	}

	return 0;
}

int RCC_SetI2s2(enum_i2sclk i2s2clk) {
#if defined(DO_PARAM_CHECKING)
	if (i2s2clk != SYSCLK_AS_I2SCLK && i2s2clk != Pll3_AS_I2SCLK)
		return -1;
#endif

	BITBEND_SET(RCC_CFGR, RCC_CFGR2_I2S2SRC, i2s2clk);

	return 0;
}

int RCC_SetI2s3(enum_i2sclk i2s3clk) {
#if defined(DO_PARAM_CHECKING)
	if (i2s3clk != SYSCLK_AS_I2SCLK && i2s3clk != Pll3_AS_I2SCLK)
		return -1;
#endif

	BITBEND_SET(RCC_CFGR, RCC_CFGR2_I2S3SRC, i2s3clk);

	return 0;
}

uint32_t RCC_GetPrediv1Clk(void) {
	register uint32_t prediv1in, psc;

	if (BITBEND(RCC_CFGR2, RCC_CFGR2_PREDIV1SRC))
		prediv1in = RCC_GetPll2Clk();
	else
		prediv1in = XTAL_FREQUENCY;

	psc = ((HWREG32(RCC_CFGR2) & RCC_CFGR2_PREDIV1_MASK) >> RCC_CFGR2_PREDIV1_0) + 1;

	return prediv1in / psc;
}

uint32_t RCC_GetPll2Clk(void) {
	register uint32_t prediv2psc, pll2mul;

	prediv2psc = ((HWREG32(RCC_CFGR2) & RCC_CFGR2_PREDIV2_MASK) >> RCC_CFGR2_PREDIV2_0) + 1;
	pll2mul = ((HWREG32(RCC_CFGR2) & RCC_CFGR2_PLL2MUL_MASK) >> RCC_CFGR2_PLL2MUL_0) + 2;

	return XTAL_FREQUENCY / prediv2psc * pll2mul;
}

uint32_t RCC_GetPll3Clk(void) {
	register uint32_t prediv2psc, pll3mul;

	prediv2psc = ((HWREG32(RCC_CFGR2) & RCC_CFGR2_PREDIV2_MASK) >> RCC_CFGR2_PREDIV2_0) + 1;
	pll3mul = ((HWREG32(RCC_CFGR2) & RCC_CFGR2_PLL3MUL_MASK) >> RCC_CFGR2_PLL3MUL_0) + 2;

	return XTAL_FREQUENCY / prediv2psc * pll3mul;
}

uint32_t RCC_GetI2S2Clk(void) {
	if (BITBEND(RCC_CFGR2, RCC_CFGR2_I2S2SRC))
		return RCC_GetPll3Clk();

	return RCC_GetSysClk();
}

uint32_t RCC_GetI2S3Clk(void) {
	if (BITBEND(RCC_CFGR2, RCC_CFGR2_I2S3SRC))
		return RCC_GetPll3Clk();

	return RCC_GetSysClk();
}
#endif
