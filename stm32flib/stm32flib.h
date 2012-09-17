#ifndef __STM32F_H__
#define __STM32F_H__

#if !(defined(STM32F100) || defined(STM32F101) || defined(STM32F102) || \
	defined(STM32F103) || defined(STM32F105) || defined(STM32F107))
#error "The production line of the MCU must be specified!"
#endif

#if !defined(XTAL_FREQUENCY)
#define XTAL_FREQUENCY		0
#endif

#define LIB_VERSION_MAJOR				0x0001
#define LIB_VERSION_MINOR				0x0000
#define STM32FLIB_GetVersion		((LIB_VERSION_MAJOR << 16) | LIB_VERSION_MINOR)

#include <stdlib.h>
#include <stdint.h>

#include "algrithm/div64.h"
#include "algrithm/list.h"

#include "core/cpu.h"
#include "core/flash.h"
#include "core/nvic.h"
#include "core/rcc.h"

#include "peripheral/gpio.h"
#include "peripheral/usart.h"

#endif // __STM32F_H__
