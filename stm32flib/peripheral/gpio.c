#include "stm32flib.h"

#define RCC_APB2ENR_IPOxEN(port)					BITBEND(0x40021018, (2 + (port)))

#define GPIOx_CRL(port)           				HWREG32(0x40010800 + (port) * 0x400)
#define GPIOx_CRH(port)           				HWREG32(0x40010804 + (port) * 0x400)
#define GPIOx_CR_MODEx_OFFSET(pin)				((pin) * 4 + 0)
#define GPIOx_CR_MODEx_MASK(pin)					(0x03 << (GPIOx_CR_MODEx_OFFSET(pin)))
#define GPIOx_CR_CNFx_OFFSET(pin)				((pin) * 4 + 2)
#define GPIOx_CR_CNFx_MASK(pin)					(0x03 << (GPIOx_CR_CNFx_OFFSET(pin)))
#define GPIOx_IDRx(port, pin)							BITBEND(0x40010808 + (port) * 0x400, pin)
#define GPIOx_ODRx(port, pin)							BITBEND(0x4001080C + (port) * 0x400, pin)
#define GPIOx_BSRR_BSx(port, pin)				BITBEND(0x40010810 + (port) * 0x400, pin)
#define GPIOx_BSRR_BRx(port, pin)				BITBEND(0x40010810 + (port) * 0x400, pin)
#define GPIOx_LCKR(port, pin)							BITBEND(0x40010818 + (port) * 0x400, pin)
#define GPIOx_LCKR_LCKK(port)							BITBEND(0x40010818 + (port) * 0x400, 16)

int GPIO_EnablePort(enum_gpio_port port) {
#if defined(DO_PARAM_CHECKING)
	if (port < GPIO_PA || port > GPIO_PG)
		return -1;
#endif

	RCC_APB2ENR_IPOxEN(port) = 1;
	DSB();

	return 0;
}

int GPIO_DisablePort(enum_gpio_port port) {
#if defined(DO_PARAM_CHECKING)
	if (port < GPIO_PA || port > GPIO_PG)
		return -1;
#endif

	RCC_APB2ENR_IPOxEN(port) = 0;
	DSB();

	return 0;
}

int GPIO_IsPortEnabled(enum_gpio_port port) {
#if defined(DO_PARAM_CHECKING)
	if (port < GPIO_PA || port > GPIO_PG)
			return -1;
#endif

	return RCC_APB2ENR_IPOxEN(port);
}

int GPIO_SetPinMode(enum_gpio_pin pin, enum_gpio_pin_mode mode) {
	register uint32_t cr, *cr_addr;

#if defined(DO_PARAM_CHECKING)
	if (GPIO_PORT(pin) < GPIO_PA || GPIO_PORT(pin) > GPIO_PG)
		return -1;

	if (mode < GPIO_IN_ANALOG || mode > GPIO_AFOUT_OPENDRAIN_50MHz)
		return -1;
#endif

	// Check whether the GPIO pin has been locked
	if (GPIOx_LCKR(GPIO_PORT(pin), GPIO_PIN_NUMBER(pin)))
		return -1;

	if (GPIO_PIN_NUMBER(pin) >= 0 && GPIO_PIN_NUMBER(pin) <= 7) {
		cr_addr = (uint32_t *)(&GPIOx_CRL(GPIO_PORT(pin)));
	} else if (GPIO_PIN_NUMBER(pin) <= 15) {
		cr_addr = (uint32_t *)(&GPIOx_CRH(GPIO_PORT(pin)));
	} else
		return -1;

	if (mode == GPIO_IN_PULLDOWN || mode == GPIO_IN_PULLUP) {
		GPIOx_ODRx(GPIO_PORT(pin), GPIO_PIN_NUMBER(pin)) = mode & 0x01;
		mode = 8;
	}

	cr = HWREG32(cr_addr);
	cr &= ~GPIOx_CR_MODEx_MASK(GPIO_PIN_NUMBER(pin));
	cr &= ~GPIOx_CR_CNFx_MASK(GPIO_PIN_NUMBER(pin));
	cr |= (mode << GPIOx_CR_MODEx_OFFSET(GPIO_PIN_NUMBER(pin)));
	HWREG32(cr_addr) = cr;
	DSB();

	return 0;
}

int GPIO_GetPinMode(enum_gpio_pin pin) {
	register uint32_t cr;

#if defined(DO_PARAM_CHECKING)
	if (GPIO_PORT(pin) < GPIO_PA || GPIO_PORT(pin) > GPIO_PG)
		return -1;

	if (GPIO_PIN_NUMBER(pin) < 0 || GPIO_PIN_NUMBER(pin) > 15)
			return -1;
#endif

	if (GPIO_PIN_NUMBER(pin) <= 7)
		cr = GPIOx_CRL(GPIO_PORT(pin));
	else
		cr = GPIOx_CRH(GPIO_PORT(pin));

	cr = (cr >> (pin & 0x07)) & 0x0F;

	if (cr == 8) {
		if (GPIOx_ODRx(GPIO_PORT(pin), GPIO_PIN_NUMBER(pin)))
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

	if (!GPIOx_LCKR(GPIO_PORT(pin), GPIO_PIN_NUMBER(pin))) {
		GPIOx_LCKR(GPIO_PORT(pin), GPIO_PIN_NUMBER(pin)) = 1;
		DSB();

		GPIOx_LCKR_LCKK(GPIO_PORT(pin)) = 1;
		DSB();

		GPIOx_LCKR_LCKK(GPIO_PORT(pin)) = 0;
		DSB();

		GPIOx_LCKR_LCKK(GPIO_PORT(pin)) = 1;
		DSB();

		while (1) {
			if (!GPIOx_LCKR_LCKK(GPIO_PORT(pin)))
				break;
		}

		while (1) {
			if (GPIOx_LCKR_LCKK(GPIO_PORT(pin)))
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

	GPIOx_ODRx(GPIO_PORT(pin), GPIO_PIN_NUMBER(pin)) = stat;
	DSB();

	return 0;
}

int __inline__ GPIO_PinOutHigh(enum_gpio_pin pin) {
#if defined(DO_PARAM_CHECKING)
	if (GPIO_PORT(pin) < GPIO_PA || GPIO_PORT(pin) > GPIO_PG)
		return -1;

	if (GPIO_PIN_NUMBER(pin) < 0 || GPIO_PIN_NUMBER(pin) > 15)
			return -1;
#endif

	GPIOx_BSRR_BSx(GPIO_PORT(pin), GPIO_PIN_NUMBER(pin)) = 1;
	DSB();

	return 0;
}

int __inline__ GPIO_PinOutLow(enum_gpio_pin pin) {
#if defined(DO_PARAM_CHECKING)
	if (GPIO_PORT(pin) < GPIO_PA || GPIO_PORT(pin) > GPIO_PG)
		return -1;

	if (GPIO_PIN_NUMBER(pin) > 15)
		return -1;
#endif

	GPIOx_BSRR_BRx(GPIO_PORT(pin), GPIO_PIN_NUMBER(pin)) = 1;
	DSB();

	return 0;
}

int __inline__ GPIO_PinInvert(enum_gpio_pin pin) {
#if defined(DO_PARAM_CHECKING)
	if (GPIO_PORT(pin) < GPIO_PA || GPIO_PORT(pin) > GPIO_PG)
		return -1;

	if (GPIO_PIN_NUMBER(pin) > 15)
		return -1;
#endif

	GPIOx_ODRx(GPIO_PORT(pin), GPIO_PIN_NUMBER(pin)) = !GPIOx_ODRx(GPIO_PORT(pin), GPIO_PIN_NUMBER(pin));

	return 0;
}

int __inline__ GPIO_GetPinStat(enum_gpio_pin pin) {
#if defined(DO_PARAM_CHECKING)
	if (GPIO_PORT(pin) < GPIO_PA || GPIO_PORT(pin) > GPIO_PG)
		return -1;

	if (GPIO_PIN_NUMBER(pin) > 15)
		return -1;
#endif

	return GPIOx_IDRx(GPIO_PORT(pin), GPIO_PIN_NUMBER(pin));
}
