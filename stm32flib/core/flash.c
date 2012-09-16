#include "stm32flib.h"

#define FLASH_ACR												0x40022000
#define FLASH_ACR_LATENCY_0						0
#define FLASH_ACR_LATENCY_1						1
#define FLASH_ACR_LATENCY_2						2
#define FLASH_ACR_LATENCY_MASK				(0x07 << FLASH_ACR_LATENCY_0)
#define FLASH_ACR_HLFCYA							3
#define FLASH_ACR_PRFTBE							4
#define FLASH_ACR_PRFTBS							5

#define FLASH_KEYR											0x40022004

#define FLASH_OPTKEYR									0x40022008

#define FLASH_CR												0x40022010
#define FLASH_CR_PG										0
#define FLASH_CR_PER										1
#define FLASH_CR_MER										2
#define FLASH_CR_OPTPG									4
#define FLASH_CR_OPTPER								5
#define FLASH_CR_STRT									6
#define FLASH_CR_LOCK									7
#define FLASH_CR_OPTWRE								9
#define FLASH_CR_ERRIE									10
#define FLASH_CR_EOPIE									12

#define FLASH_SR												0x4002200C
#define FLASH_SR_BSY										0

#define FLASH_AR												0x40022014

#define FLASH_OBR												0x4002201C
#define FLASH_OBR_OPTERR							0
#define FLASH_OBR_RDPRT								1
#define FLASH_OBR_WDG_SW							2
#define FLASH_OBR_nRST_STOP						3
#define FLASH_OBR_nRST_STDBY					4
#define FLASH_OBR_data0_0							10
#define FLASH_OBR_data0_1							11
#define FLASH_OBR_data0_2							12
#define FLASH_OBR_data0_3							13
#define FLASH_OBR_data0_4							14
#define FLASH_OBR_data0_5							15
#define FLASH_OBR_data0_6							16
#define FLASH_OBR_data0_7							17
#define FLASH_OBR_data0_MASK					(0xFF << FLASH_OBR_data0_0)
#define FLASH_OBR_data1_0							18
#define FLASH_OBR_data1_1							19
#define FLASH_OBR_data1_2							20
#define FLASH_OBR_data1_3							21
#define FLASH_OBR_data1_4							22
#define FLASH_OBR_data1_5							23
#define FLASH_OBR_data1_6							24
#define FLASH_OBR_data1_7							25
#define FLASH_OBR_data1_MASK					(0xFF << FLASH_OBR_data1_0)

#define FLASH_WRPR											0x4002201C

#if (defined(STM32F100) || defined(STM32F101) || defined(STM32F102))
#define FLASH_PAGESIZE			1024
#elif (defined(STM32F103) || defined(STM32F105) || defined(STM32F107))
#define FLASH_PAGESIZE			2048
#endif

#if defined(DO_PARAM_CHECKING)
extern uint32_t _flash_start_;
extern uint32_t _flash_end_;
#endif

int FLASH_SetLatency(enum_flash_latency latency) {
	register uint32_t acr;

#if defined(DO_PARAM_CHECKING)
	if (latency < FLASH_LATENCY_0 || latency > FLASH_LATENCY_2)
		return -1;
#endif

	acr = HWREG32(FLASH_ACR);
	acr &= ~FLASH_ACR_LATENCY_MASK;
	acr |= (latency << FLASH_ACR_LATENCY_0);
	HWREG32_SET(FLASH_ACR, acr);

	return 0;
}

int FLASH_GetLatency(void) {
	return ((HWREG32(FLASH_ACR) & FLASH_ACR_LATENCY_MASK) >> FLASH_ACR_LATENCY_0);
}

void FLASH_EnableHalfAccess(void) {
	BITBEND_SET(FLASH_ACR, FLASH_ACR_HLFCYA, 1);
}

void FLASH_DisableHalfAccess(void) {
	BITBEND_SET(FLASH_ACR, FLASH_ACR_HLFCYA, 0);
}

int FLASH_IsHalfAccessEnabled(void) {
	return BITBEND(FLASH_ACR, FLASH_ACR_HLFCYA);
}

void FLASH_EnablePrefetchBuffer(void) {
	BITBEND_SET(FLASH_ACR, FLASH_ACR_PRFTBE, 1);
}

void FLASH_DisablePrefetchBuffer(void) {
	BITBEND_SET(FLASH_ACR, FLASH_ACR_PRFTBE, 0);
}

int FLASH_IsPrefetchBufferEnabled(void) {
	return BITBEND(FLASH_ACR, FLASH_ACR_PRFTBE);
}

void FLASH_Lock(void) {
	BITBEND_SET(FLASH_CR, FLASH_CR_LOCK, 1);
}

int FLASH_Unlock(void) {
	HWREG32_SET(FLASH_KEYR, 0x45670123);
	HWREG32_SET(FLASH_KEYR, 0xCDEF89AB);
	HWREG32_SET(FLASH_CR, 0);

	return (BITBEND(FLASH_CR, FLASH_CR_LOCK) ? -1 : 0);
}

int FLASH_ErasePage(void *addr) {
	register void *addr_verify;

#if defined(DO_PARAM_CHECKING)
	if (addr < ((void *)&_flash_start_) || addr > ((void *)&_flash_end_))
		return -1;
#endif

	addr = (void *)(((uint32_t)addr) & (~(FLASH_PAGESIZE - 1)));

	BITBEND_SET(FLASH_CR, FLASH_CR_PER, 1);
	HWREG32_SET(FLASH_AR, addr);
	BITBEND_SET(FLASH_CR, FLASH_CR_STRT, 1);

	while (1) {
		if (!BITBEND(FLASH_SR, FLASH_SR_BSY))
			break;
	}

	BITBEND_SET(FLASH_CR, FLASH_CR_PER, 0);

	for (addr_verify = addr, addr += FLASH_PAGESIZE; addr_verify < addr; addr_verify += 2) {
		if (HWREG16(addr_verify) != 0xFFFF)
			return -1;
	}

	return 0;
}

int FLASH_Write(void *addr, uint16_t halfword) {
#if defined(DO_PARAM_CHECKING)
	if (addr < ((void *)&_flash_start_) || addr > ((void *)&_flash_end_) || (((uint32_t)addr) & 0x01))
		return -1;
#endif

	// Check whether the operation is up to change any bits from 0 to 1.
	// If it is, refuse to perform.
	if ((~HWREG16(addr)) & halfword)
		return -1;

	BITBEND_SET(FLASH_CR, FLASH_CR_PG, 1);
	HWREG16_SET(addr, halfword);

	while (1) {
		if (!BITBEND(FLASH_SR, FLASH_SR_BSY))
			break;
	}

	BITBEND_SET(FLASH_CR, FLASH_CR_PG, 0);

	return ((HWREG16(addr) == halfword) ? 0 : -1);
}
