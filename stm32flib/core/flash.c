#include "stm32flib.h"

#define FLASH_ACR												HWREG32(0x40022000)
#define FLASH_ACR_LATENCY_0						BITBEND(0x40022000, 0)
#define FLASH_ACR_LATENCY_1						BITBEND(0x40022000, 1)
#define FLASH_ACR_LATENCY_2						BITBEND(0x40022000, 2)
#define FLASH_ACR_LATENCY_OFFSET			0
#define FLASH_ACR_LATENCY_MASK				(0x07 << FLASH_ACR_LATENCY_OFFSET)
#define FLASH_ACR_HLFCYA							BITBEND(0x40022000, 3)
#define FLASH_ACR_PRFTBE							BITBEND(0x40022000, 4)
#define FLASH_ACR_PRFTBS							BITBEND(0x40022000, 5)

#define FLASH_KEYR											HWREG32(0x40022004)

#define FLASH_OPTKEYR									HWREG32(0x40022008)

#define FLASH_CR												HWREG32(0x40022010)
#define FLASH_CR_PG										BITBEND(0x40022010, 0)
#define FLASH_CR_PER										BITBEND(0x40022010, 1)
#define FLASH_CR_MER										BITBEND(0x40022010, 2)
#define FLASH_CR_OPTPG									BITBEND(0x40022010, 4)
#define FLASH_CR_OPTPER								BITBEND(0x40022010, 5)
#define FLASH_CR_STRT									BITBEND(0x40022010, 6)
#define FLASH_CR_LOCK									BITBEND(0x40022010, 7)
#define FLASH_CR_OPTWRE								BITBEND(0x40022010, 9)
#define FLASH_CR_ERRIE									BITBEND(0x40022010, 10)
#define FLASH_CR_EOPIE									BITBEND(0x40022010, 12)

#define FLASH_SR												HWREG32(0x4002200C)
#define FLASH_SR_BSY										BITBEND(0x40022010, 0)

#define FLASH_AR												HWREG32(0x40022014)

#define FLASH_OBR												HWREG32(0x4002201C)
#define FLASH_OBR_OPTERR							BITBEND(0x40022010, 0)
#define FLASH_OBR_RDPRT								BITBEND(0x40022010, 1)
#define FLASH_OBR_WDG_SW							BITBEND(0x40022010, 2)
#define FLASH_OBR_nRST_STOP						BITBEND(0x40022010, 3)
#define FLASH_OBR_nRST_STDBY					BITBEND(0x40022010, 4)
#define FLASH_OBR_data0_0							BITBEND(0x40022010, 10)
#define FLASH_OBR_data0_1							BITBEND(0x40022010, 11)
#define FLASH_OBR_data0_2							BITBEND(0x40022010, 12)
#define FLASH_OBR_data0_3							BITBEND(0x40022010, 13)
#define FLASH_OBR_data0_4							BITBEND(0x40022010, 14)
#define FLASH_OBR_data0_5							BITBEND(0x40022010, 15)
#define FLASH_OBR_data0_6							BITBEND(0x40022010, 16)
#define FLASH_OBR_data0_7							BITBEND(0x40022010, 17)
#define FLASH_OBR_data0_OFFSET				10
#define FLASH_OBR_data0_MASK					(0xFF << FLASH_OBR_data0_OFFSET)
#define FLASH_OBR_data1_0							BITBEND(0x40022010, 18)
#define FLASH_OBR_data1_1							BITBEND(0x40022010, 19)
#define FLASH_OBR_data1_2							BITBEND(0x40022010, 20)
#define FLASH_OBR_data1_3							BITBEND(0x40022010, 21)
#define FLASH_OBR_data1_4							BITBEND(0x40022010, 22)
#define FLASH_OBR_data1_5							BITBEND(0x40022010, 23)
#define FLASH_OBR_data1_6							BITBEND(0x40022010, 24)
#define FLASH_OBR_data1_7							BITBEND(0x40022010, 25)
#define FLASH_OBR_data1_OFFSET				18
#define FLASH_OBR_data1_MASK					(0xFF << FLASH_OBR_data1_0)

#define FLASH_WRPR											HWREG32(0x4002201C)

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

	acr = FLASH_ACR;
	acr &= ~FLASH_ACR_LATENCY_MASK;
	acr |= (latency << FLASH_ACR_LATENCY_OFFSET);
	FLASH_ACR = acr;
	DSB();

	return 0;
}

int FLASH_GetLatency(void) {
	return ((FLASH_ACR & FLASH_ACR_LATENCY_MASK) >> FLASH_ACR_LATENCY_OFFSET);
}

void FLASH_EnableHalfAccess(void) {
	FLASH_ACR_HLFCYA = 1;
	DSB();
}

void FLASH_DisableHalfAccess(void) {
	FLASH_ACR_HLFCYA = 0;
	DSB();
}

int FLASH_IsHalfAccessEnabled(void) {
	return FLASH_ACR_HLFCYA;
}

void FLASH_EnablePrefetchBuffer(void) {
	FLASH_ACR_PRFTBE = 1;
	DSB();
}

void FLASH_DisablePrefetchBuffer(void) {
	FLASH_ACR_PRFTBE = 0;
	DSB();
}

int FLASH_IsPrefetchBufferEnabled(void) {
	return FLASH_ACR_PRFTBE;
}

void FLASH_Lock(void) {
	FLASH_CR_LOCK = 1;
	DSB();
}

int FLASH_Unlock(void) {
	FLASH_KEYR = 0x45670123;
	DSB();

	FLASH_KEYR = 0xCDEF89AB;
	DSB();

	FLASH_CR = 0;
	DSB();

	return (FLASH_CR_LOCK ? -1 : 0);
}

int FLASH_ErasePage(void *addr) {
	register void *addr_verify;

#if defined(DO_PARAM_CHECKING)
	if (addr < ((void *)&_flash_start_) || addr > ((void *)&_flash_end_))
		return -1;
#endif

	addr = (void *)(((uint32_t)addr) & (~(FLASH_PAGESIZE - 1)));

	FLASH_CR_PER = 1;
	DSB();

	FLASH_AR = (uint32_t)addr;
	DSB();

	FLASH_CR_STRT = 1;
	DSB();

	while (1) {
		if (!FLASH_SR_BSY)
			break;
	}

	FLASH_CR_PER = 0;
	DSB();

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

	if (HWREG16(addr) != 0xFF)
		return -1;

	FLASH_CR_PG = 1;
	DSB();

	HWREG16(addr)  = halfword;
	DSB();

	while (1) {
		if (!FLASH_SR_BSY)
			break;
	}

	FLASH_CR_PG = 0;
	DSB();

	return ((HWREG16(addr) == halfword) ? 0 : -1);
}
