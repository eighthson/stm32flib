#include "stm32flib.h"

int __inline__ LSBi(uint32_t x) {
	if (x == 0)
		return -1;

	__asm__ __volatile__ (
		"rbit %1, %1"			"\n\t" \
		"clz %0, %1"			"\n\t" \
		:"=r"(x):"r"(x)
	);

	return x;
}

int __inline__ MSBi(uint32_t x) {
	if (x == 0)
		return -1;

	__asm__ __volatile__ (
		"clz %0, %1"			"\n\t" \
		:"=r"(x):"r"(x)
	);

	return (31 - x);
}

int CPU_SetExceptionStackAligment(enum_exception_stack_aligment align) {
	register uint32_t reg;

	if (align == EXCEPTION_STACK_ALIGN_BY_4_BYTE) {
		reg = HWREG32(0xE000ED14) & (~BV(9));
		HWREG32(0xE000ED14) = reg;
		DSB();
	}
	else if (align == EXCEPTION_STACK_ALIGN_BY_8_BYTE) {
		reg = HWREG32(0xE000ED14) | BV(9);
		HWREG32(0xE000ED14) = reg;
		DSB();
	}
	else
		return -1;

	return 0;
}

int CPU_GetExceptionStackAligment(void) {
	return (HWREG32(0xE000ED14) & BV(9)) ? EXCEPTION_STACK_ALIGN_BY_8_BYTE : \
			EXCEPTION_STACK_ALIGN_BY_4_BYTE;
}

int CPU_SetExceptionPriority(enum_exception exception, unsigned int prio) {
	register uint32_t reg;

#if defined(DO_PARAM_CHECKING)
	if (prio > 15)
		return -1;
#endif

	if (exception >=  EXCEPTION_MEMORY_MANAGEMENT_FAULT &&
			exception <= EXCEPTION_USAGE_FAULT) {
		reg = HWREG32(0xE000ED18);
		reg &= ~(0x0F << (exception * 8 + 4));
		reg |= (prio << (exception * 8 + 4));
		HWREG32(0xE000ED18) = reg;
		DSB();
	} else if (exception == EXCEPTION_SVCALL) {
		reg = HWREG32(0xE000ED1C);
		reg &= ~(0x0F << ((exception - 4) * 8 + 4));
		reg |= (prio << ((exception - 4) * 8 + 4));
		HWREG32(0xE000ED1C) = reg;
		DSB();
	} else if (exception >= EXCEPTION_PENDSV && exception <= EXCEPTION_SYSTICK) {
		reg = HWREG32(0xE000ED20);
		reg &= ~(0x0F << ((exception - 8) * 8 + 4));
		reg |= (prio << ((exception - 8) * 8 + 4));
		HWREG32(0xE000ED20) = reg;
		DSB();
	} else
		return -1;

	return 0;
}

int CPU_GetExceptionPriority(enum_exception exception) {
	if (exception >=  EXCEPTION_MEMORY_MANAGEMENT_FAULT && exception <= EXCEPTION_USAGE_FAULT)
		return ((HWREG32(0xE000ED18) >> (exception * 8)) & 0x0F);
	else if (exception == EXCEPTION_SVCALL)
		return ((HWREG32(0xE000ED18) >> ((exception - 4) * 8)) & 0x0F);
	else if (exception >= EXCEPTION_PENDSV && exception <= EXCEPTION_SYSTICK)
		return ((HWREG32(0xE000ED18) >> ((exception - 8) * 8)) & 0x0F);
	else
		return -1;
}
