#include "stm32flib.h"

extern uint32_t _text_end_;
extern uint32_t _data_start_;
extern uint32_t _data_end_;
extern uint32_t _bss_start_;
extern uint32_t _bss_end_;
extern uint32_t _stack_end_;

void NVIC_IrqRouter(void) {
}

void __attribute__((naked)) fault_exception_handler(void) {
	while(1);
}

void __attribute__((naked)) default_exception_handler(void) {
	__asm__ __volatile__ ("bx lr");
}

void reset_handler(void) {
	register uint32_t *psrc, *pdst;

	psrc = &_stack_end_;
	__asm__ __volatile__ ("cpsid f");

	// Copy all of the variables which are in .data section from ROM to RAM
	for (psrc = &_text_end_, pdst = &_data_start_; pdst < &_data_end_;) {
		*pdst++ = *psrc++;
	}

	// Set all of the variables which are in .bss section to 0
	for (pdst = &_bss_start_; pdst < &_bss_end_;) {
		*pdst++ = 0;
	}

	DSB();

	// Correctlly set SP then start the application program
	__asm__ __volatile__(
		"msr msp, %0"		"\n\t"
		"bl main"				"\n\t"
		::"r"(&_stack_end_));

	while (1) {
//		__asm__ __volatile__ ("wfi");
		NOP();
	}
}

__attribute__ ((section(".exception_vect")))
void (* const arr_rom_vect[])(void) = {
	(void(*)(void))(&_stack_end_),
	reset_handler,
	fault_exception_handler,
	fault_exception_handler,
	fault_exception_handler,
	fault_exception_handler,
	fault_exception_handler,
	0, 0, 0, 0, 0, 0, 0,
	0,
	0,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
	NVIC_IrqRouter,
};
