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
	register uint32_t r;

	if (align == EXCEPTION_STACK_ALIGN_BY_4_BYTE) {
		r = HWREG32(0xE000ED14) & (~BV(9));
		HWREG32_SET(0xE000ED14, r);
	}
	else if (align == EXCEPTION_STACK_ALIGN_BY_8_BYTE) {
		r = HWREG32(0xE000ED14) | BV(9);
		HWREG32_SET(0xE000ED14, r);
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
	register uint32_t r;

#if defined(DO_PARAM_CHECKING)
	if (prio > 15)
		return -1;
#endif

	if (exception >=  EXCEPTION_MEMORY_MANAGEMENT_FAULT &&
			exception <= EXCEPTION_USAGE_FAULT) {
		r = HWREG32(0xE000ED18);
		r &= ~(0x0F << (exception * 8 + 4));
		r |= (prio << (exception * 8 + 4));
		HWREG32_SET(0xE000ED18, r);
	} else if (exception == EXCEPTION_SVCALL) {
		r = HWREG32(0xE000ED1C);
		r &= ~(0x0F << ((exception - 4) * 8 + 4));
		r |= (prio << ((exception - 4) * 8 + 4));
		HWREG32_SET(0xE000ED1C, r);
	} else if (exception >= EXCEPTION_PENDSV && exception <= EXCEPTION_SYSTICK) {
		r = HWREG32(0xE000ED20);
		r &= ~(0x0F << ((exception - 8) * 8 + 4));
		r |= (prio << ((exception - 8) * 8 + 4));
		HWREG32_SET(0xE000ED20, r);
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
