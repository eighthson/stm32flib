#ifndef __NVIC_H__
#define __NVIC_H__

#if !(defined(STM32F105) || defined(STM32F107))
#define MAX_IRQS		60
#else
#define MAX_IRQS		68
#endif

struct irq_registeration {
	volatile struct list_node nod;
	void (*proc)(void *);
	void *udata;
};

typedef enum {
	IRQ_WWDG = 0,
	IRQ_PVD = 1,
	IRQ_TAMPER = 2,
	IRQ_RTC = 3,
	IRQ_FLASH = 4,
	IRQ_RCC = 5,
	IRQ_EXTI0 = 6,
	IRQ_EXTI1 = 7,
	IRQ_EXTI2 = 8,
	IRQ_EXTI3 = 9,
	IRQ_EXTI4 = 10,
	IRQ_DMA1CH1 = 11,
	IRQ_DMA1CH2 = 12,
	IRQ_DMA1CH3 = 13,
	IRQ_DMA1CH4 = 14,
	IRQ_DMA1CH5 = 15,
	IRQ_DMA1CH6 = 16,
	IRQ_DMA1CH7 = 17,
	IRQ_ADC1_2 = 18,
#if !(defined(STM32F105) || defined(STM32F107))
	IRQ_USB_HP_CAN_TX = 19,
	IRQ_USB_LP_CAN_RX0 = 20,
	IRQ_CAN_RX1 = 21,
	IRQ_CAN_SCE = 22,
#else
	IRQ_CAN1_TX = 19,
	IRQ_CAN1_RX0 = 20,
	IRQ_CAN1_RX1 = 21,
	IRQ_CAN1_SCE = 22,
#endif
	IRQ_EXTI5_9 = 23,
#if !defined(STM32F_XL)
	IRQ_TIM1_BRK = 24,
	IRQ_TIM1_UP = 25,
	IRQ_TIM1_TRG_COM = 26,
#else
	IRQ_TIM1_BRK_TIM9 = 24,
	IRQ_TIM1_UP_TIM10 = 25,
	IRQ_TIM1_TRG_COM_TIM11 = 26,
#endif
	IRQ_TIM1_CC = 27,
	IRQ_TIM2 = 28,
	IRQ_TIM3 = 29,
	IRQ_TIM4 = 30,
	IRQ_I2C1_EV = 31,
	IRQ_I2C1_ER = 32,
	IRQ_I2C2_EV = 33,
	IRQ_I2C2_ER = 34,
	IRQ_SPI1 = 35,
	IRQ_SPI2 = 36,
	IRQ_USART1 = 37,
	IRQ_USART2 = 38,
	IRQ_USART3 = 39,
	IRQ_EXTI10_15 = 40,
	IRQ_RTCAlarm = 41,
#if !defined(STM32F_CL) && !defined(STM32F_XL)
	IRQ_USBWakeup = 42,
	IRQ_TIM8_BRK = 43,
	IRQ_TIM8_UP = 44,
	IRQ_TIM8_TRG_COM = 45,
	IRQ_TIM8_CC = 46,
	IRQ_ADC3 = 47,
	IRQ_FMSC = 48,
	IRQ_SDIO = 49,
#endif
#if defined(STM32F_XL)
	IRQ_USBWakeup = 42,
	IRQ_TIM8_BRK_TIM12 = 43,
	IRQ_TIM8_UP_TIM13 = 44,
	IRQ_TIM8_TRG_COM_TIM14 = 45,
	IRQ_TIM8_CC = 46,
	IRQ_ADC3 = 47,
	IRQ_FMSC = 48,
	IRQ_SDIO = 49,
#endif
#if defined(STM32F_CL)
	IRQ_OTG_FS_WKUP = 42,
#endif
	IRQ_TIM5 = 50,
	IRQ_SPI3 = 51,
	IRQ_UART4 = 52,
	IRQ_UART5 = 53,
	IRQ_TIM6 = 54,
	IRQ_TIM7 = 55,
	IRQ_DMA2CH1 = 56,
	IRQ_DMA2CH2 = 57,
	IRQ_DMA2CH3 = 58,
#if !(defined(STM32F105) || defined(STM32F107))
	IRQ_DMA2CH4_5 = 59,
#else
	IRQ_DMA2CH4 = 59,
	IRQ_DMA2CH5 = 60,
	IRQ_ETH = 61,
	IRQ_ETH_WKUP = 62,
	IRQ_CAN2_TX = 63,
	IRQ_CAN2_RX0 = 64,
	IRQ_CAN2_RX1 = 65,
	IRQ_CAN2_SCE = 66,
	OTG_FS = 67,
#endif
} enum_irq;

#ifdef __cplusplus
extern "C" {
#endif

int NVIC_Init(void);
int NVIC_SetIrqRoutine(enum_irq irq, struct irq_registeration *registration);
int NVIC_SetIrqPriority(enum_irq irq, unsigned int prio);
int NVIC_GetIrqPriority(enum_irq irq);
int NVIC_EnableIrq(enum_irq irq);
int NVIC_DisableIrq(enum_irq irq);
int NVIC_IsIrqEnabled(enum_irq irq);
int NVIC_IsIrqPending(enum_irq irq);
int NVIC_ClearIrqPending(enum_irq irq);
int NVIC_TriggerIrq(enum_irq irq);

#ifdef __cplusplus
}
#endif

#endif // __NVIC_H__
