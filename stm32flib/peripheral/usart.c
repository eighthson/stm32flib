#include "stm32flib.h"

#define RCC_APB2ENR									0x40021018
#define RCC_APB2ENR_USART1EN				14

#define RCC_APB1ENR									0x4002101C
#define RCC_APB1ENR_USART2EN				17
#define RCC_APB1ENR_USART3EN				18

#define USART_SR(usart)							(usart + 0x00)
#define USART_SR_RXNE								5
#define USART_SR_TC									6
#define USART_SR_TXE									7

#define USART_DR(usart)							(usart + 0x04)

#define USART_BRR(usart)						(usart + 0x08)

#define USART_CR1(usart)						(usart + 0x0C)
#define USART_CR1_RE									2
#define USART_CR1_TE									3
#define USART_CR1_RXNEIE						5
#define USART_CR1_TCIE								6
#define USART_CR1_TXEIE							7
#define USART_CR1_PS									9
#define USART_CR1_PCE								10
#define USART_CR1_M									11
#define USART_CR1_UE									13

#define USART_CR2(usart)						(usart + 0x10)
#define USART_CR2_STOP_0						12
#define USART_CR2_STOP_1						13
#define USART_CR2_STOP_2						14
#define USART_CR2_STOP_MASK					(0x03 << USART_CR2_STOP_0)

int USART_Enable(enum_usart usart) {
	if (usart == USART1) {
		BITBEND_SET(RCC_APB2ENR, RCC_APB2ENR_USART1EN, 1);
	} else if (usart == USART2) {
		BITBEND_SET(RCC_APB1ENR, RCC_APB1ENR_USART2EN, 1);
	} else if (usart == USART2) {
		BITBEND_SET(RCC_APB1ENR, RCC_APB1ENR_USART3EN, 1);
	} else
		return -1;

	BITBEND_SET(USART_CR(usart), USART_CR1_UE, 1);

	return 0;
}

int USART_Disable(enum_usart usart) {
	if (usart == USART1) {
		BITBEND_SET(USART_CR(usart), USART_CR1_UE, 0);
		BITBEND_SET(RCC_APB2ENR, RCC_APB2ENR_USART1EN, 0);
	} else if (usart == USART2) {
		BITBEND_SET(USART_CR(usart), USART_CR1_UE, 0);
		BITBEND_SET(RCC_APB1ENR, RCC_APB1ENR_USART2EN, 0);
	} else if (usart == USART2) {
		BITBEND_SET(USART_CR(usart), USART_CR1_UE, 0);
		BITBEND_SET(RCC_APB1ENR, RCC_APB1ENR_USART3EN, 0);
	} else
		return -1;

	return 0;
}

int USART_IsEnabled(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	return BITBEND(USART_CR(usart), USART_CR1_UE);
}

int USART_SetBaud(enum_usart usart, unsigned int baud) {
	register uint32_t psc;

	if (usart == USART1) {
		psc = RCC_GetApb2Clk() * 16 / baud;
	} else if (usart == USART2 || usart == USART3) {
		psc = RCC_GetApb1Clk() * 16 / baud;
	} else
		return -1;

	if (psc > 0xFFFF || psc == 0)
		return -1;

	HWREG32_SET(USART_BRR(usart), psc);

	return 0;
}

int USART_GetBaud(enum_usart usart) {
	register uint32_t fck;

	if (usart == USART1) {
		fck = RCC_GetApb2Clk();
	} else if (usart == USART2 || usart == USART3) {
		fck = RCC_GetApb1Clk();
	} else
		return -1;

	return (int)(fck * 16 / HWREG32(USART_BRR(usart)));
}

int USART_SetDataWidth(enum_usart usart, unsigned int width) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	if (width == 8) {
		BITBEND_SET(USART_CR1(usart), USART_CR1_M, 0);
	}  else	if (width == 9 && !USART_CR1_PCE(usart)) {
		BITBEND_SET(USART_CR1(usart), USART_CR1_M, 1);
	} else
		return -1;

	return 0;
}

int USART_SetParity(enum_usart usart, enum_usart_parity parity) {
	register uint32_t reg;

#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;

	if (parity != USART_PARITY_EVEN && parity != USART_PARITY_ODD && parity == USART_PARITY_NONE)
		return -1;
#endif

	reg = HWREG32(USART_CR1(usart));
	reg &= ~(BV(USART_CR1_PS) | BV(USART_CR1_PCE));
	reg |= (parity << USART_CR1_PS);
	HWREG32_SET(USART_CR1(usart), reg);

	return 0;
}

int USART_SetStopBit(enum_usart usart, enum_usart_stopbit stopbit) {
	register uint32_t reg;

#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;

	if (stopbit < USART_STOPBIT_1 || stopbit > USART_STOPBIT_1d5)
		return -1;
#endif

	reg = HWREG32(USART_CR2(usart));
	reg &= ~USART_CR2_STOP_MASK;
	reg |= (stopbit << USART_CR2_STOP_0);
	HWREG32_SET(USART_CR2(usart), reg);

	return 0;
}

int USART_GetDataWidth(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	return (BITBEND(USART_CR1(usart), USART_CR1_M) ? 9 : 8);
}

int USART_GetParity(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	return (int)((HWREG32(USART_CR1(usart)) >> USART_CR1_PS) & 0x03);
}

int USART_GetStopBit(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	return (int)((HWREG32(USART_CR2(usart)) & USART_CR2_STOP_MASK) >> USART_CR2_STOP_0);
}

int USART_EnableTransmission(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	BITBEND_SET(USART_CR1(usart), USART_CR1_TE, 1);

	return 0;
}

int USART_DisableTransmission(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	BITBEND_SET(USART_CR1(usart), USART_CR1_TE, 0);

	return 0;
}

int USART_IsTransmissionEnabled(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	return BITBEND(USART_CR1(usart), USART_CR1_TE);
}

int USART_EnableReceiption(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	BITBEND_SET(USART_CR1(usart), USART_CR1_RE, 1);

	return 0;
}

int USART_DisableReceiption(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	BITBEND_SET(USART_CR1(usart), USART_CR1_RE, 0);

	return 0;
}

int USART_IsReceiptionEnabled(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	return BITBEND(USART_CR1(usart), USART_CR1_RE);
}

int USART_EnableTxeInterrupt(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	BITBEND_SET(USART_CR1(usart), USART_CR1_TXEIE, 1);

	return 0;
}

int USART_DisableTxeInterrupt(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	BITBEND_SET(USART_CR1(usart), USART_CR1_TXEIE, 0);

	return 0;
}

int USART_IsTxeInterruptEnabled(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	return BITBEND(USART_CR1(usart), USART_CR1_TXEIE);
}

int USART_EnableRxneInterrupt(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	BITBEND_SET(USART_CR1(usart), USART_CR1_RXNEIE, 1);

	return 0;
}

int USART_DisableRxneInterrupt(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	BITBEND_SET(USART_CR1(usart), USART_CR1_RXNEIE, 0);

	return 0;
}

int USART_IsRxneInterruptEnabled(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	return BITBEND(USART_CR1(usart), USART_CR1_RXNEIE);
}

int USART_EnableTcInterrupt(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	BITBEND_SET(USART_CR1(usart), USART_CR1_TCIE, 1);

	return 0;
}

int USART_DisableTcInterrupt(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	BITBEND_SET(USART_CR1(usart), USART_CR1_TCIE, 0);

	return 0;
}

int USART_IsTcInterruptEnabled(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	return BITBEND(USART_CR1(usart), USART_CR1_RXNEIE);
}

int __inline__ USART_IsTxeSet(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	return BITBEND(USART_SR(usart), USART_SR_TXE);
}

int __inline__ USART_IsTcSet(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	return BITBEND(USART_SR(usart), USART_SR_TC);
}

int __inline__ USART_ClearTc(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	BITBEND_SET(USART_SR(usart), USART_SR_TC, 0);

	return 0;
}

int __inline__ USART_IsRxneSet(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	return BITBEND(USART_SR(usart), USART_SR_RXNE);
}

int __inline__ USART_ClearRxne(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	BITBEND_SET(USART_SR(usart), USART_SR_RXNE, 0);

	return 0;
}

int __inline__ USART_SendData(enum_usart usart, uint16_t data) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	 if (!BITBEND(USART_SR(usart), USART_SR_TXE))
		 return -1;

	 HWREG32_SET(USART_DR(usart), data & 0x1F);

	return 0;
}

int __inline__ USART_QueryData(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	 if (!BITBEND(USART_SR(usart), USART_SR_RXNE))
		 return -1;

	 return (int)HWREG32(USART_DR(usart));
}
