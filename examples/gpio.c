#include "stm32flib.h"

int main(void) {
	FLASH_SetLatency(FLASH_LATENCY_2);
	FLASH_DisableHalfAccess();
	FLASH_EnablePrefetchBuffer();

	RCC_SetPll(HSI_DIV_BY_2_AS_PLLIN, PLL_MUL_16);
	RCC_TurnOnPll();
	RCC_SetAhbPsc(AHB_PRE_1);
	RCC_SetApb1Psc(APB_PRE_2);
	RCC_SetApb2Psc(APB_PRE_1);
	RCC_SetSysClk(PLL_AS_SYSCLK);

	GPIO_EnablePort(GPIO_PB);
	GPIO_PinOutHigh(GPIO_PB8);
	GPIO_SetPinMode(GPIO_PB8, GPIO_OUT_OPENDRAIN_2MHz);

	while (1) {
		GPIO_PinInvert(GPIO_PB8);
	}

	return 0;
}
