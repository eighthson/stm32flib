#ifndef __USART_H__
#define __USART_H__

typedef enum {
	USART1 = 0x40013800,
	USART2 = 0x40014400,
	USART3 = 0x40014800,
} enum_usart;

typedef enum {
	USART_PARITY_NONE = 0,
	USART_PARITY_EVEN = 2,
	USART_PARITY_ODD = 3,
} enum_usart_parity;

typedef enum {
	USART_STOPBIT_1 = 0,
	USART_STOPBIT_0d5 = 1,
	USART_STOPBIT_2 = 2,
	USART_STOPBIT_1d5 = 3,
} enum_usart_stopbit;

#ifdef __cplusplus
extern "C" {
#endif

int USART_Enable(enum_usart usart);
int USART_Disable(enum_usart usart);
int USART_IsEnabled(enum_usart usart);
int USART_SetBaud(enum_usart usart, unsigned int baud);
int USART_GetBaud(enum_usart usart);
int USART_SetDataWidth(enum_usart usart, unsigned int width);
int USART_SetParity(enum_usart usart, enum_usart_parity parity);
int USART_SetStopBit(enum_usart usart, enum_usart_stopbit stopbit);
int USART_GetDataWidth(enum_usart usart);
int USART_GetParity(enum_usart usart);
int USART_GetStopBit(enum_usart usart);
int USART_EnableTransmission(enum_usart usart);
int USART_DisableTransmission(enum_usart usart);
int USART_IsTransmissionEnabled(enum_usart usart);
int USART_EnableReceiption(enum_usart usart);
int USART_DisableReceiptio(enum_usart usart);
int USART_IsReceiptioEnabled(enum_usart usart);
int USART_EnableTxeInterrupt(enum_usart usart);
int USART_DisableTxeInterrupt(enum_usart usart);
int USART_IsTxeInterruptEnabled(enum_usart usart);
int USART_EnableRxneInterrupt(enum_usart usart);
int USART_DisableRxneInterrupt(enum_usart usart);
int USART_IsRxneInterruptEnabled(enum_usart usart);
int USART_EnableTcInterrupt(enum_usart usart);
int USART_DisableTcInterrupt(enum_usart usart);
int USART_IsTcInterruptEnabled(enum_usart usart);
int USART_IsTxeSet(enum_usart usart);
int USART_IsTcSet(enum_usart usart);
int USART_ClearTc(enum_usart usart);
int USART_IsRxneSet(enum_usart usart);
int USART_ClearRxne(enum_usart usart);
int USART_SendData(enum_usart usart, uint16_t data);
int USART_QueryData(enum_usart usart);

#ifdef __cplusplus
}
#endif

#endif // __USART_H__
