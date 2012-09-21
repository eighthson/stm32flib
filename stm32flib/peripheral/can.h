#ifndef __CAN_H__
#define __CAN_H__

#if (defined(STM32F105) || defined(STM32F107))
typedef enum {
	CAN1 = 0x40006400,
	CAN2 = 0x40006800,
} enum_can;
#endif

typedef enum {
	CAN_MODE_NORMAL = 0,
	CAN_MODE_INIT = 1,
	CAN_MODE_SLEEP = 2,
} enum_can_mode;

typedef enum {
	CAN_TRANSMISSION_MAILBOX_PRIORITY_DRIVEN_BY_ID = 0,
	CAN_TRANSMISSION_MAILBOX_PRIORITY_DRIVEN_BY_ORDER = 1,
} enum_can_transmission_maibox_priority;

typedef enum {
	CAN_RECEIPTION_FIFO_UNLOCKED_ON_OVERRUN = 0,
	CAN_RECEIPTION_FIFO_LOCKED_AGAINST_OVERRUN = 1,
} enum_can_receiption_fifo_lock_mode;

typedef enum {
	CAN_ERROR_WARNING = (1 << 0),
	CAN_ERROR_PASSIVE = (1 << 1),
	CAN_ERROR_BUSOFF = (1 << 2),
} enum_error_stat;

typedef enum {
	CAN_STAT_IDLE = 0,
	CAN_STAT_TRANSMITTING = 1,
	CAN_STAT_RECEIVING = 2,
} enum_can_communication_stat;

typedef enum {
	CAN_TRANSMISSION_STAT_IDLE = 0,
	CAN_TRANSMISSION_STAT_TRANSMITTING = 1,
	CAN_TRANSMISSION_STAT_OK = 4,
	CAN_TRANSMISSION_STAT_ARB_LOST = 5,
	CAN_TRANSMISSION_STAT_ERR = 9,
} enum_transmission_stat;

typedef enum {
	CAN_ID_STID = (0 << 31),
	CAN_ID_EXID = (1 << 31),
} enum_can_id_type;

#define CAN_ID_MAKE_ID(flags, id)			((flags) | ((id) & 0x7FFFFFFF))
#define CAN_ID_MAKE_STID(id)						((id) & 0x7FFFFFFF)
#define CAN_ID_MAKE_EXID(id)						(CAN_ID_EXID | ((id) & 0x7FFFFFFF))
#define CAN_ID_IS_STID(id)							(!((id) & CAN_ID_EXID))
#define CAN_ID_IS_EXID(id)							((id) & CAN_ID_EXID)
#define CAN_ID_GET_ID(id)								(CAN_ID_IS_EXID(id) ? (id) & 0x3FFFFFFF : (id) & 0x7FF)

typedef enum {
	CAN_DATA_MESSAGE = 0,
	CAN_REMOTE_MESSAGE = 1,
	CAN_ALL_SORTS_OF_MESSAGE = 2,
} enum_can_message_type;

typedef enum {
	CAN_16BIT_ID_MASK_FILTER = 0,
	CAN_16BIT_ID_LIST_FILTER = 1,
	CAN_32BIT_ID_MASK_FILTER = 2,
	CAN_32BIT_ID_LIST_FILTER = 3,
} enum_can_receiption_filter_type;

struct can_receiption_filter {
	uint8_t filter_type;
	uint8_t message_type;
	uint32_t mask;
	uint32_t id;
};

struct can_message {
	uint32_t id;
	uint8_t type;
	uint8_t data_len;
	union {
		uint8_t data8[8];
		uint8_t data16[8];
		uint32_t data32[2];
	};
};

#ifdef __cplusplus
extern "C" {
#endif

#if !(defined(STM32F105) || defined(STM32F107))
void CAN_Enable(void);
void CAN_Disable(void);
int CAN_IsEnabled(void);
void CAN_Reset(void);
int CAN_SetMode(enum_can_mode mode);
int CAN_GetMode(void);
int CAN_SetTransmissionMailboxPriority(enum_can_transmission_maibox_priority prio);
int CAN_GetTransmissionMailboxPriority(void);
int CAN_SetReceiptionFifoLockMode(enum_can_receiption_fifo_lock_mode mode);
int CAN_GetReceiptionFifoLockMode(void);
void CAN_EnableAutoRetransimit(void);
void CAN_DisableAutoRetransimit(void);
int CAN_IsAutomaticRetransimitEnabled(void);
void CAN_EnableAutoWakeup(void);
void CAN_DisableAutoWakeup(void);
int CAN_IsAutoWakeupEnabled(void);
void CAN_EnableAutoBuslink(void);
void CAN_DisableAutoBuslink(void);
int CAN_IsAutoBuslinkEnabled(void);
void CAN_EnableDebugFreeze(void);
void CAN_DisableDebugFreeze(void);
int CAN_SetBitRate(unsigned int bps, unsigned int sjw);
int CAN_GetBitRate(void);
int CAN_GetSJW(void);
void CAN_EnableLoopbackMode(void);
void CAN_DisableLoopbackMode(void);
int CAN_IsLoopbackModeEnabled(void);
void CAN_EnableSilentMode(void);
void CAN_DisableSilentMode(void);
int CAN_IsSlientModeEnabled(void);
void CAN_EnableTmeInterrupt(void);
void CAN_DisableTmeInterrupt(void);
int CAN_IsTmeInterruptEnabled(void);
void CAN_EnableFmp0Interrupt(void);
void CAN_DisableFmp0Interrupt(void);
int CAN_IsFmp0InterruptEnabled(void);
void CAN_EnableFmp1Interrupt(void);
void CAN_DisableFmp1Interrupt(void);
int CAN_IsFmp1InterruptEnabled(void);
int CAN_GetControllerStat(void);
int CAN_GetErrorStat(void);
int CAN_GetTransmissionStat(unsigned int mailbox);
int CAN_ResetTransmissionMailbox(unsigned int mailbox);
int CAN_LoadMessageToTransmissionMailbox(unsigned int mailbox, struct can_message *message);
int CAN_StartTransmission(unsigned int mailbox);
int CAN_AbortTransmission(unsigned int mailbox);
int CAN_IsReceiptionFifoFull(unsigned int fifo);
int CAN_IsReceiptionFifoOverrun(unsigned int fifo);
int CAN_ResetReceiptionFifo(unsigned int fifo);
int CAN_CountReceiptedMessage(unsigned int fifo);
int CAN_QueryReceiptionMessage(unsigned int fifo, struct can_message *message);
int CAN_GetAssocitedFilterIdOfReceiptionMessage(unsigned int fifo);
int CAN_ReleaseReceiptionMessage(unsigned int fifo);
int CAN_SetTypeOfReceiptionFilter(unsigned int i, enum_can_receiption_filter_type type);
int CAN_GetTypeOfReceiptionFilter(unsigned int i);
int CAN_SetReceiptionFilter(unsigned int i, unsigned int slot, struct can_receiption_filter *filter);
int CAN_GetReceiptionFilter(unsigned int i, unsigned int slot, struct can_receiption_filter *filter);
int CAN_AssignReceiptionFilterToFifo(unsigned int i, unsigned int fifo);
int CAN_GetFifoReceiptionFilterAssignedTo(unsigned int i);
int CAN_ActivateReceiptionFilter(unsigned int i);
int CAN_DeactivateReceiptionFilter(unsigned int i);
int CAN_IsReceiptionFilterActive(unsigned int i);
#else
int CAN_Enable(enum_can can);
int CAN_Disable(enum_can can);
int CAN_IsEnabled(enum_can can);
int CAN_Reset(enum_can can);
int CAN_SetMode(enum_can can, enum_can_mode mode);
int CAN_GetMode(enum_can can);
int CAN_SetTransmissionMailboxPriority(enum_can can, enum_can_transmission_maibox_priority prio);
int CAN_GetTransmissionMailboxPriority(enum_can can);
int CAN_SetReceiptionFifoLockMode(enum_can can, enum_can_receiption_fifo_lock_mode mode);
int CAN_GetReceiptionFifoLockMode(enum_can can);
int CAN_EnableAutoRetransimit(enum_can can);
int CAN_DisableAutoRetransimit(enum_can can);
int CAN_IsAutomaticRetransimitEnabled(enum_can can);
int CAN_EnableAutoWakeup(enum_can can);
int CAN_DisableAutoWakeup(enum_can can);
int CAN_IsAutoWakeupEnabled(enum_can can);
int CAN_EnableAutoBuslink(enum_can can);
int CAN_DisableAutoBuslink(enum_can can);
int CAN_IsAutoBuslinkEnabled(enum_can can);
int CAN_EnableDebugFreeze(enum_can can);
int CAN_DisableDebugFreeze(enum_can can);
int CAN_IsDebugFreezeEnabled(enum_can can);
int CAN_SetBitRate(enum_can can, unsigned int bps, unsigned int sjw);
int CAN_GetBitRate(enum_can can);
int CAN_GetSJW(enum_can can);
int CAN_EnableLoopbackMode(enum_can can);
int CAN_DisableLoopbackMode(enum_can can);
int CAN_IsLoopbackModeEnabled(enum_can can);
int CAN_EnableSilentMode(enum_can can);
int CAN_DisableSilentMode(enum_can can);
int CAN_IsSlientModeEnabled(enum_can can);
int CAN_EnableTmeInterrupt(enum_can can);
int CAN_DisableTmeInterrupt(enum_can can);
int CAN_IsTmeInterruptEnabled(enum_can can);
int CAN_EnableFmp0Interrupt(enum_can can);
int CAN_DisableFmp0Interrupt(enum_can can);
int CAN_IsFmp0InterruptEnabled(enum_can can);
int CAN_EnableFmp1Interrupt(enum_can can);
int CAN_DisableFmp1Interrupt(enum_can can);
int CAN_IsFmp1InterruptEnabled(enum_can can);
int CAN_GetControllerStat(enum_can can);
int CAN_GetErrorStat(enum_can can);
int CAN_GetTransmissionStat(enum_can can, unsigned int mailbox);
int CAN_ResetTransmissionMailbox(enum_can can, unsigned int mailbox);
int CAN_LoadMessageToTransmissionMailbox(enum_can can, unsigned int mailbox, struct can_message *message);
int CAN_StartTransmission(enum_can can, unsigned int mailbox);
int CAN_AbortTransmission(enum_can can, unsigned int mailbox);
int CAN_IsReceiptionFifoFull(enum_can can, unsigned int fifo);
int CAN_IsReceiptionFifoOverrun(enum_can can, unsigned int fifo);
int CAN_ResetReceiptionFifo(enum_can can, unsigned int fifo);
int CAN_CountReceiptedMessage(enum_can can, unsigned int fifo);
int CAN_QueryReceiptionMessage(enum_can can, unsigned int fifo, struct can_message *message);
int CAN_GetAssocitedFilterIdOfReceiptionMessage(enum_can can, unsigned int fifo);
int CAN_ReleaseReceiptionMessage(enum_can can, unsigned int fifo);
int CAN_SetTypeOfReceiptionFilter(enum_can can, unsigned int i, enum_can_receiption_filter_type type);
int CAN_GetTypeOfReceiptionFilter(enum_can can, unsigned int i);
int CAN_SetReceiptionFilter(enum_can can, unsigned int i, unsigned int slot, struct can_receiption_filter *filter);
int CAN_GetReceiptionFilter(enum_can can, unsigned int i, unsigned int slot, struct can_receiption_filter *filter);
int CAN_AssignReceiptionFilterToFifo(enum_can can, unsigned int i, unsigned int fifo);
int CAN_GetFifoReceiptionFilterAssignedTo(enum_can can, unsigned int i);
int CAN_ActivateReceiptionFilter(enum_can can, unsigned int i);
int CAN_DeactivateReceiptionFilter(enum_can can, unsigned int i);
int CAN_IsReceiptionFilterActive(enum_can can, unsigned int i);
#endif

#ifdef __cplusplus
}
#endif

#endif // __CAN_H__
