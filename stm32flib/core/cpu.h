#ifndef __CPU_H__
#define __CPU_H__

#define HWREG32(addr)								(*((const uint32_t *)(addr)))
#define HWREG32_SET(addr, val)			__asm__ __volatile__ ( \
	"str %1, [%0]"		"\n\t" \
	"ldr %1, [%0]"		"\n\t" \
	::"r"(addr), "r"(val));

#define HWREG16(addr)								(*((const uint16_t *)(addr)))
#define HWREG16_SET(addr, val)			__asm__ __volatile__ ( \
	"strh %1, [%0]"		"\n\t" \
	"ldrh %1, [%0]"		"\n\t" \
	::"r"(addr), "r"(val));

#define HWREG8(addr)									(*((const uint8_t *)(addr)))
#define HWREG8_SET(addr, val)				__asm__ __volatile__ ( \
	"strh %1, [%0]"		"\n\t" \
	"ldrh %1, [%0]"		"\n\t" \
	::"r"(addr), "r"(val));

#define BITBEND(addr, bit) 					HWREG32((((uint32_t)(addr)) & 0xF0000000) + \
	0x2000000 + (((uint32_t)(addr)) & 0xFFFFF) * 32 + (bit) * 4)
#define BITBEND_SET(addr, bit)			__asm__ __volatile__ ( \
	"mov r0, #1"			"\n\t" \
	"str r0, [%0]"		"\n\t" \
	"ldr r0, [%0]"		"\n\t" \
	::"r"(&BITBEND(addr, bit)):"r0");
#define BITBEND_UNSET(addr, bit)		__asm__ __volatile__ ( \
	"mov r0, #0"			"\n\t" \
	"str r0, [%0]"		"\n\t" \
	"ldr r0, [%0]"		"\n\t" \
	::"r"(&BITBEND(addr, bit)):"r0");

#define MAX(a, b)						(((a) > (b)) ? (a) : (b))
#define MIN(a, b)						(((a) < (b)) ? (a) : (b))
#define SWAP(a, b)					a ^= b; b ^= a; a ^= b

#define BV(i) 		(1 << (i))
#define NOP() 		__asm__ __volatile__("nop")
#define DSB()			__asm__ __volatile__ ("dsb")
#define ISB()			__asm__ __volatile__ ("isb")

typedef uint32_t critical_t;

#define INTO_CRITICAL(cri)	__asm__ __volatile__( \
	"mrs r0, FAULTMASK"		"\n\t" \
	"cpsid f"								"\n\t" \
	:"=r"(cri));

#define EXIT_CRITICAL(cri)	__asm__ __volatile__( \
	"msr FAULTMASK, %0"		"\n\t" \
	::"r"(cri))

typedef enum {
	EXCEPTION_STACK_ALIGN_BY_4_BYTE = 0,
	EXCEPTION_STACK_ALIGN_BY_8_BYTE = 1,
} enum_exception_stack_aligment;

typedef enum {
	EXCEPTION_MEMORY_MANAGEMENT_FAULT = 0,
	EXCEPTION_BUS_FAULT = 1,
	EXCEPTION_USAGE_FAULT = 2,
	EXCEPTION_SVCALL = 7,
	EXCEPTION_PENDSV = 10,
	EXCEPTION_SYSTICK = 11,
} enum_exception;

#ifdef __cplusplus
extern "C" {
#endif

int LSBi(uint32_t x);
int MSBi(uint32_t x);

int CPU_SetExceptionStackAligment(enum_exception_stack_aligment align);
int CPU_GetExceptionStackAligment(void);

int CPU_SetExceptionPriority(enum_exception exception, unsigned int prio);
int CPU_GetExceptionPriority(enum_exception exception);

#ifdef __cplusplus
}
#endif

#endif // __CPU_H__
