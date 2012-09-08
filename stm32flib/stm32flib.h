#ifndef __STM32F_H__
#define __STM32F_H__

#if !(defined(STM32F103T8) || defined(STM32F103TB) || defined(STM32F103C8) || \
	defined(STM32F103CB) || defined(STM32F103R8) || defined(STM32F103RB) || \
	defined(STM32F103RC) || defined(STM32F103RD) || defined(STM32F103RE) || \
	defined(STM32F103C8) || defined(STM32F103VB) || defined(STM32F103VC) || \
	defined(STM32F103VD) || defined(STM32F103VE) || defined(STM32F103ZC) || \
	defined(STM32F103ZD) || defined(STM32F103ZE))
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

#endif // __STM32F_H__
