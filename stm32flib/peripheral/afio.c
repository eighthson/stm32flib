#include "stm32flib.h"

#define RCC_APB2ENR										0x40021018
#define RCC_APB2ENR_AFIOEN						0

void AFIO_Enable(void) {
	BITBEND_SET(RCC_APB2ENR, RCC_APB2ENR_AFIOEN, 1);
}

void AFIO_Disable(void) {
	BITBEND_SET(RCC_APB2ENR, RCC_APB2ENR_AFIOEN, 0);
}

int AFIO_IsEnabled(void) {
	return BITBEND(RCC_APB2ENR, RCC_APB2ENR_AFIOEN);
}
