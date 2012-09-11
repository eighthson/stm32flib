#include "stm32flib.h"

#define RCC_APB2ENR_USART1EN				BITBEND(0x40021018, 14)
#define RCC_APB2ENR_USART2EN				BITBEND(0x4002101C, 17)
#define RCC_APB2ENR_USART3EN				BITBEND(0x4002101C, 18)

#define USART_SR(usart)							HWREG32(usart + 0x00)
#define USART_SR_RXNE(usart)				BITBEND(usart + 0x00, 5)
#define USART_SR_TC(usart)					BITBEND(usart + 0x00, 6)
#define USART_SR_TXE(usart)					BITBEND(usart + 0x00, 7)

#define USART_DR(usart)							HWREG32(usart + 0x04)

#define USART_BRR(usart)						HWREG32(usart + 0x08)

#define USART_CR1(usart)						HWREG32(usart + 0x0C)
#define USART_CR1_RE(usart)					BITBEND(usart + 0x0C, 2)
#define USART_CR1_TE(usart)					BITBEND(usart + 0x0C, 3)
#define USART_CR1_RXNEIE(usart)			BITBEND(usart + 0x0C, 5)
#define USART_CR1_TCIE(usart)				BITBEND(usart + 0x0C, 6)
#define USART_CR1_TXEIE(usart)			BITBEND(usart + 0x0C, 7)
#define USART_CR1_PS(usart)					BITBEND(usart + 0x0C, 9)
#define USART_CR1_PCE(usart)				BITBEND(usart + 0x0C, 10)
#define USART_CR1_M(usart)					BITBEND(usart + 0x0C, 11)
#define USART_CR1_UE(usart)					BITBEND(usart + 0x0C, 13)

#define USART_CR2(usart)						HWREG32(usart + 0x10)
#define USART_CR2_STOP_OFFSET				12
#define USART_CR2_STOP_MASK					(0x03 << USART_CR2_STOP_OFFSET)

int USART_Enable(enum_usart usart) {
	if (usart == USART1) {
		RCC_APB2ENR_USART1EN = 1;
		DSB();
	} else if (usart == USART2) {
		RCC_APB2ENR_USART2EN = 1;
		DSB();
	} else if (usart == USART2) {
		RCC_APB2ENR_USART2EN = 1;
		DSB();
	} else
		return -1;

	USART_CR1_UE(usart) = 1;
	DSB();

	return 0;
}

int USART_Disable(enum_usart usart) {
	if (usart == USART1) {
		USART_CR1_UE(usart) = 0;
		DSB();

		RCC_APB2ENR_USART1EN = 1;
		DSB();
	} else if (usart == USART2) {
		USART_CR1_UE(usart) = 0;
		DSB();

		RCC_APB2ENR_USART2EN = 1;
		DSB();
	} else if (usart == USART2) {
		USART_CR1_UE(usart) = 0;
		DSB();

		RCC_APB2ENR_USART2EN = 1;
		DSB();
	} else
		return -1;

	return 0;
}

int USART_IsEnabled(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	return USART_CR1_UE(usart);
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

	USART_BRR(usart) = psc;
	DSB();

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

	return (int)(fck * 16 / USART_BRR(usart));
}

int USART_SetDataWidth(enum_usart usart, unsigned int width) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	if (width == 8) {
		USART_CR1_M(usart) = 1;
		DSB();
	}  else	if (width == 9 && !USART_CR1_PCE(usart)) {
		USART_CR1_M(usart) = 0;
		DSB();
	} else
		return -1;

	return 0;
}

int USART_SetParity(enum_usart usart, enum_usart_parity parity) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	if (parity == USART_PARITY_EVEN || parity == USART_PARITY_ODD) {
		if (!USART_CR1_M(usart)) {
			USART_CR1_PS(usart) = parity & 0x01;
			DSB();

			USART_CR1_PCE(usart) = 1;
			DSB();
		} else
			return -1;
	} else if (parity == USART_PARITY_NONE) {
		USART_CR1_PCE(usart) = 0;
		DSB();
	} else
		return -1;

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

	reg = USART_CR2(usart);
	reg &= ~USART_CR2_STOP_MASK;
	reg |= stopbit << USART_CR2_STOP_OFFSET;
	USART_CR2(usart) = reg;
	DSB();

	return 0;
}

int USART_GetDataWidth(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	return (USART_CR1_M(usart) ? 9 : 8);
}

int USART_GetParity(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	return (int)((USART_CR1_PCE(usart) << 1) | USART_CR1_PS(usart));
}

int USART_GetStopBit(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	return (int)((USART_CR2(usart) & USART_CR2_STOP_MASK) >> USART_CR2_STOP_OFFSET);
}

int USART_EnableTransmission(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	USART_CR1_TE(usart) = 1;
	DSB();

	return 0;
}

int USART_DisableTransmission(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	USART_CR1_TE(usart) = 0;
	DSB();

	return 0;
}

int USART_IsTransmissionEnabled(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	return USART_CR1_TE(usart);
}

int USART_EnableReceiption(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	USART_CR1_RE(usart) = 1;
	DSB();

	return 0;
}

int USART_DisableReceiption(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	USART_CR1_RE(usart) = 0;
	DSB();

	return 0;
}

int USART_IsReceiptionEnabled(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	return USART_CR1_TE(usart);
}

int USART_EnableTxeInterrupt(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	USART_CR1_TXEIE(usart) = 1;
	DSB();

	return 0;
}

int USART_DisableTxeInterrupt(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	USART_CR1_TXEIE(usart) = 0;
	DSB();

	return 0;
}

int USART_IsTxeInterruptEnabled(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	return USART_CR1_TXEIE(usart);
}

int USART_EnableRxneInterrupt(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	USART_CR1_RXNEIE(usart) = 1;
	DSB();

	return 0;
}

int USART_DisableRxneInterrupt(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	USART_CR1_RXNEIE(usart) = 1;
	DSB();

	return 0;
}

int USART_IsRxneInterruptEnabled(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	return USART_CR1_RXNEIE(usart);
}

int USART_EnableTcInterrupt(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	USART_CR1_TCIE(usart) = 1;
	DSB();

	return 0;
}

int USART_DisableTcInterrupt(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	USART_CR1_TCIE(usart) = 0;
	DSB();

	return 0;
}

int USART_IsTcInterruptEnabled(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	return USART_CR1_TCIE(usart);
}

int __inline__ USART_IsTxeSet(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	return USART_SR_TXE(usart);
}

int __inline__ USART_IsTcSet(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	return USART_SR_TC(usart);
}

int __inline__ USART_ClearTc(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	USART_SR_TC(usart) = 0;
	DSB();

	return 0;
}

int __inline__ USART_IsRxneSet(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	return USART_SR_RXNE(usart);
}

int __inline__ USART_ClearRxne(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	USART_SR_RXNE(usart) = 0;
	DSB();

	return 0;
}

int __inline__ USART_SendData(enum_usart usart, uint16_t data) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	 if (!USART_SR_TXE(usart))
		 return -1;

	 USART_DR(usart) = data & 0x1F;

	return 0;
}

int __inline__ USART_QueryData(enum_usart usart) {
#if defined(DO_PARAM_CHECKING)
	if (usart != USART1 && usart != USART2 && usart != USART3)
		return -1;
#endif

	 if (!USART_SR_RXNE(usart))
		 return -1;

	 return (int)(USART_DR(usart) & 0x1F);
}
