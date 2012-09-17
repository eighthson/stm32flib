#include "stm32flib.h"

#define RCC_APB2ENR												0x40021018
#define RCC_APB2ENR_IPOxEN(port)					(2 + (port))

#define GPIOx_CRL(port)           				(0x40010800 + (port) * 0x400)
#define GPIOx_CRH(port)           				(0x40010804 + (port) * 0x400)
#define GPIOx_CR_MODEx(pin)								((pin) * 4 + 0)
#define GPIOx_CR_MODEx_MASK(pin)					(0x03 << (GPIOx_CR_MODEx(pin)))
#define GPIOx_CR_CNFx(pin)								((pin) * 4 + 2)
#define GPIOx_CR_CNFx_MASK(pin)						(0x03 << (GPIOx_CR_CNFx(pin)))
#define GPIOx_IDR(port)										(0x40010808 + (port) * 0x400)
#define GPIOx_ODR(port)										(0x4001080C + (port) * 0x400)
#define GPIOx_LCKR(port)									(0x40010818 + (port) * 0x400)
#define GPIOx_LCKR_LCKK										16

int GPIO_EnablePort(enum_gpio_port port) {
#if defined(DO_PARAM_CHECKING)
	if (port < GPIO_PA || port > GPIO_PG)
		return -1;
#endif

	BITBEND_SET(RCC_APB2ENR, RCC_APB2ENR_IPOxEN(port), 1);

	return 0;
}

int GPIO_DisablePort(enum_gpio_port port) {
#if defined(DO_PARAM_CHECKING)
	if (port < GPIO_PA || port > GPIO_PG)
		return -1;
#endif

	BITBEND_SET(RCC_APB2ENR, RCC_APB2ENR_IPOxEN(port), 0);

	return 0;
}

int GPIO_IsPortEnabled(enum_gpio_port port) {
#if defined(DO_PARAM_CHECKING)
	if (port < GPIO_PA || port > GPIO_PG)
			return -1;
#endif

	return BITBEND(RCC_APB2ENR, RCC_APB2ENR_IPOxEN(port));
}

int GPIO_SetPinMode(enum_gpio_pin pin, enum_gpio_pin_mode mode) {
	register uint32_t cr, *cr_addr;

#if defined(DO_PARAM_CHECKING)
	if (GPIO_PORT(pin) < GPIO_PA || GPIO_PORT(pin) > GPIO_PG)
		return -1;

	if (mode < GPIO_IN_ANALOG || mode > GPIO_AFOUT_OPENDRAIN_50MHz)
		return -1;
#endif

	if (GPIO_PIN_NUMBER(pin) >= 0 && GPIO_PIN_NUMBER(pin) <= 7) {
		if (BITBEND(GPIOx_LCKR(GPIO_PORT(pin)), GPIO_PIN_NUMBER(pin)))
			return -1;

		cr_addr = (uint32_t *)GPIOx_CRL(GPIO_PORT(pin));
	} else if (GPIO_PIN_NUMBER(pin) <= 15) {
		if (BITBEND(GPIOx_LCKR(GPIO_PORT(pin)), GPIO_PIN_NUMBER(pin)))
			return -1;

		cr_addr = (uint32_t *)GPIOx_CRH(GPIO_PORT(pin));
	} else
		return -1;

	if (mode == GPIO_IN_PULLDOWN || mode == GPIO_IN_PULLUP) {
		BITBEND_SET(GPIOx_ODR(GPIO_PORT(pin)), GPIO_PIN_NUMBER(pin), mode & 0x01);
		mode = 8;
	}

	cr = HWREG32(cr_addr);
	cr &= ~GPIOx_CR_MODEx_MASK(GPIO_PIN_NUMBER(pin));
	cr &= ~GPIOx_CR_CNFx_MASK(GPIO_PIN_NUMBER(pin));
	cr |= (mode << GPIOx_CR_MODEx(GPIO_PIN_NUMBER(pin)));
	HWREG32_SET(cr_addr, cr);

	return 0;
}

int GPIO_GetPinMode(enum_gpio_pin pin) {
	register uint32_t cr;

#if defined(DO_PARAM_CHECKING)
	if (GPIO_PORT(pin) < GPIO_PA || GPIO_PORT(pin) > GPIO_PG)
		return -1;
#endif

	if (GPIO_PIN_NUMBER(pin) >= 0 && GPIO_PIN_NUMBER(pin) <= 7)
		cr = HWREG32(GPIOx_CRL(GPIO_PORT(pin)));
	else if (GPIO_PIN_NUMBER(pin) <= 15)
		cr = HWREG32(GPIOx_CRH(GPIO_PORT(pin)));

	cr = (cr >> (pin & 0x07)) & 0x0F;

	if (cr == 8) {
		if (BITBEND(GPIOx_ODR(GPIO_PORT(pin)), GPIO_PIN_NUMBER(pin)))
			return GPIO_IN_PULLUP;
		else
			return GPIO_IN_PULLDOWN;
	}

	return (enum_gpio_pin_mode)cr;
}

int GPIO_LockPinMode(enum_gpio_pin pin) {
#if defined(DO_PARAM_CHECKING)
	if (GPIO_PORT(pin) < GPIO_PA || GPIO_PORT(pin) > GPIO_PG)
		return -1;

	if (GPIO_PIN_NUMBER(pin) < 0 || GPIO_PIN_NUMBER(pin) > 15)
			return -1;
#endif

	if (BITBEND(GPIOx_LCKR(GPIO_PORT(pin)), GPIO_PIN_NUMBER(pin))) {
		BITBEND_SET(GPIOx_LCKR(GPIO_PORT(pin)), GPIO_PIN_NUMBER(pin), 1);
		BITBEND_SET(GPIOx_LCKR(GPIO_PORT(pin)), GPIO_PIN_NUMBER(pin), 0);
		BITBEND_SET(GPIOx_LCKR(GPIO_PORT(pin)), GPIO_PIN_NUMBER(pin), 1);

		while (1) {
			if (!BITBEND(GPIOx_LCKR(GPIO_PORT(pin)), GPIO_PIN_NUMBER(pin)))
				break;
		}

		while (1) {
			if (BITBEND(GPIOx_LCKR(GPIO_PORT(pin)), GPIO_PIN_NUMBER(pin)))
				break;
		}
	}

	return 0;
}

int __inline__ GPIO_PinOut(enum_gpio_pin pin, enum_gpio_pin_stat stat) {
#if defined(DO_PARAM_CHECKING)
	if (GPIO_PORT(pin) < GPIO_PA || GPIO_PORT(pin) > GPIO_PG)
		return -1;

	if (GPIO_PIN_NUMBER(pin) < 0 || GPIO_PIN_NUMBER(pin) > 15)
			return -1;

	if (stat != GPIO_PIN_STAT_LOW && stat != GPIO_PIN_STAT_HIGH)
		return -1;
#endif

	BITBEND_SET(GPIOx_ODR(GPIO_PORT(pin)), GPIO_PIN_NUMBER(pin), stat);

	return 0;
}

int __inline__ GPIO_PinOutHigh(enum_gpio_pin pin) {
#if defined(DO_PARAM_CHECKING)
	if (GPIO_PORT(pin) < GPIO_PA || GPIO_PORT(pin) > GPIO_PG)
		return -1;

	if (GPIO_PIN_NUMBER(pin) < 0 || GPIO_PIN_NUMBER(pin) > 15)
			return -1;
#endif

	BITBEND_SET(GPIOx_ODR(GPIO_PORT(pin)), GPIO_PIN_NUMBER(pin), 1);

	return 0;
}

int __inline__ GPIO_PinOutLow(enum_gpio_pin pin) {
#if defined(DO_PARAM_CHECKING)
	if (GPIO_PORT(pin) < GPIO_PA || GPIO_PORT(pin) > GPIO_PG)
		return -1;

	if (GPIO_PIN_NUMBER(pin) > 15)
		return -1;
#endif

	BITBEND_SET(GPIOx_ODR(GPIO_PORT(pin)), GPIO_PIN_NUMBER(pin), 0);

	return 0;
}

int __inline__ GPIO_PinInvert(enum_gpio_pin pin) {
#if defined(DO_PARAM_CHECKING)
	if (GPIO_PORT(pin) < GPIO_PA || GPIO_PORT(pin) > GPIO_PG)
		return -1;

	if (GPIO_PIN_NUMBER(pin) > 15)
		return -1;
#endif

	BITBEND_SET(GPIOx_ODR(GPIO_PORT(pin)), GPIO_PIN_NUMBER(pin),
		!BITBEND(GPIOx_ODR(GPIO_PORT(pin)), GPIO_PIN_NUMBER(pin)));

	return 0;
}

int __inline__ GPIO_GetPinStat(enum_gpio_pin pin) {
#if defined(DO_PARAM_CHECKING)
	if (GPIO_PORT(pin) < GPIO_PA || GPIO_PORT(pin) > GPIO_PG)
		return -1;

	if (GPIO_PIN_NUMBER(pin) > 15)
		return -1;
#endif

	return BITBEND(GPIOx_IDR(GPIO_PORT(pin)), GPIO_PIN_NUMBER(pin));
}
