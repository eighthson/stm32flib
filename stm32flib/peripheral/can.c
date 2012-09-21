#include "stm32flib.h"
#include "can.h"

/***********************************************************************************
 *
 *  Written by eighthson (eighthson@yeah.net) in May, 2012. The file is
 *  associated with can.h. It provides a set of functions which can help
 *  users to operate the CAN controllers of STM32F series MCUs
 *
 ***********************************************************************************/

#if !(defined(STM32F105) || defined(STM32F107))
#define RCC_APB1RSTR										0x4002100C
#define RCC_APB1RSTR_CANRST							25

#define RCC_APB1ENR											0x4002101C
#define RCC_APB1ENR_CANEN								25

#define CAN_MCR													0x40006400
#define CAN_MCR_INRQ										0
#define CAN_MCR_SLEEP										1
#define CAN_MCR_TXFP										2
#define CAN_MCR_RFLM										3
#define CAN_MCR_NART										4
#define CAN_MCR_AWUM										5
#define CAN_MCR_ABOM										6
#define CAN_MCR_TTCM										7
#define CAN_MCR_DBF											16

#define CAN_MSR													0x40006404
#define CAN_MSR_INAK										0
#define CAN_MSR_SLAK										1
#define CAN_MSR_ERRI										2
#define CAN_MSR_WKUI										3
#define CAN_MSR_SLAKI										4
#define CAN_MSR_TXM											8
#define CAN_MSR_RXM											9
#define CAN_MSR_SAMP										10
#define CAN_MSR_RX											11

#define CAN_TSR													0x40006408
#define CAN_TSR_STATx(n)								((n) * 8)
#define CAN_TSR_STAT_MASK(n)						(0x0F << CAN_TSR_STATx(n))
#define CAN_TSR_RQCPx(n)								((n) * 8)
#define CAN_TSR_TXOKx(n)								((n) * 8 + 1)
#define CAN_TSR_ALSTx(n)								((n) * 8 + 2)
#define CAN_TSR_TEERx(n)								((n) * 8 + 3)
#define CAN_TSR_ABRQx(n)								((n) * 8 + 7)
#define CAN_TSR_CODE_0									24
#define CAN_TSR_CODE_1									25
#define CAN_TSR_CODE_2									26
#define CAN_TSR_CODE_MASK								(0x03 << CAN_TSR_CODE_0)
#define CAN_TSR_TMEx(n)									((n) + 26)
#define CAN_TSR_LOWx(n)									((n) + 29)

#define CAN_RFxR(n)											(0x4000640C + (n) * 4)
#define CAN_RFxR_FMP_0									0
#define CAN_RFxR_FMP_1									1
#define CAN_RFxR_FMP_MASK								(0x03 << CAN_RFxR_FMP_0)
#define CAN_RFxR_FULL										3
#define CAN_RFxR_FOVR										4
#define CAN_RFxR_RFOM										5

#define CAN_IERx(n)											BITBEND(0x40006414, n)

#define CAN_ESR													0x40006418
#define CAN_ESR_EWGF										0
#define CAN_ESR_EPVF										1
#define CAN_ESR_BOFF										2
#define CAN_ESR_LEC_0										4
#define CAN_ESR_LEC_1										5
#define CAN_ESR_LEC_2										6
#define CAN_ESR_LEC_MASK								(0x07 << CAN_ESR_LEC_0)
#define CAN_ESR_TEC_0										16
#define CAN_ESR_TEC_1										17
#define CAN_ESR_TEC_2										18
#define CAN_ESR_TEC_3										19
#define CAN_ESR_TEC_4										20
#define CAN_ESR_TEC_5										21
#define CAN_ESR_TEC_6										22
#define CAN_ESR_TEC_7										23
#define CAN_ESR_TEC_MASK								(0xFF << CAN_ESR_TEC_0)
#define CAN_ESR_REC_0										24
#define CAN_ESR_REC_1										25
#define CAN_ESR_REC_2										26
#define CAN_ESR_REC_3										27
#define CAN_ESR_REC_4										28
#define CAN_ESR_REC_5										29
#define CAN_ESR_REC_6										30
#define CAN_ESR_REC_7										31
#define CAN_ESR_REC_MASK								(0xFF << CAN_ESR_REC_0)

#define CAN_BTR													0x4000641C
#define CAN_BTR_BRP_0										0
#define CAN_BTR_BRP_1										1
#define CAN_BTR_BRP_2										2
#define CAN_BTR_BRP_3										3
#define CAN_BTR_BRP_4										4
#define CAN_BTR_BRP_5										5
#define CAN_BTR_BRP_6										6
#define CAN_BTR_BRP_7										7
#define CAN_BTR_BRP_8										8
#define CAN_BTR_BRP_9										9
#define CAN_BTR_BRP_MASK								(0x3FF << CAN_BTR_BRP_0)
#define CAN_BTR_TS1_0										16
#define CAN_BTR_TS1_1										17
#define CAN_BTR_TS1_2										18
#define CAN_BTR_TS1_3										19
#define CAN_BTR_TS1_MASK								(0x0F << CAN_BTR_TS1_0)
#define CAN_BTR_TS2_0										20
#define CAN_BTR_TS2_1										21
#define CAN_BTR_TS2_2										22
#define CAN_BTR_TS2_3										23
#define CAN_BTR_TS2_MASK								(0x07 << CAN_BTR_TS2_0)
#define CAN_BTR_SJW_0										24
#define CAN_BTR_SJW_1										25
#define CAN_BTR_SJW_MASK								(0x03 << CAN_BTR_SJW_0)
#define CAN_BTR_LBKM										30
#define CAN_BTR_SILM										31

#define CAN_TIxR(n)											(0x40006580 + ((n) * 16))
#define CAN_TIxR_TXRQ										0
#define CAN_TIxR_RTR										1
#define CAN_TIxR_IDE										2
#define CAN_TIxR_STID_0									21
#define CAN_TIxR_STID_1									22
#define CAN_TIxR_STID_2									23
#define CAN_TIxR_STID_3									24
#define CAN_TIxR_STID_4									25
#define CAN_TIxR_STID_5									26
#define CAN_TIxR_STID_6									27
#define CAN_TIxR_STID_7									28
#define CAN_TIxR_STID_8									29
#define CAN_TIxR_STID_9									30
#define CAN_TIxR_STID_10								31
#define CAN_TIxR_STID_MASK							(0x7FF << CAN_TIxR_STID_0)
#define CAN_TIxR_EXID_0									3
#define CAN_TIxR_EXID_1									4
#define CAN_TIxR_EXID_2									5
#define CAN_TIxR_EXID_3									6
#define CAN_TIxR_EXID_4									7
#define CAN_TIxR_EXID_5									8
#define CAN_TIxR_EXID_6									9
#define CAN_TIxR_EXID_7									10
#define CAN_TIxR_EXID_8									11
#define CAN_TIxR_EXID_9									12
#define CAN_TIxR_EXID_10								13
#define CAN_TIxR_EXID_11								14
#define CAN_TIxR_EXID_12								15
#define CAN_TIxR_EXID_13								16
#define CAN_TIxR_EXID_14								17
#define CAN_TIxR_EXID_15								18
#define CAN_TIxR_EXID_16								19
#define CAN_TIxR_EXID_17								20
#define CAN_TIxR_EXID_18								21
#define CAN_TIxR_EXID_19								22
#define CAN_TIxR_EXID_20								23
#define CAN_TIxR_EXID_21								24
#define CAN_TIxR_EXID_22								25
#define CAN_TIxR_EXID_23								26
#define CAN_TIxR_EXID_24								27
#define CAN_TIxR_EXID_25								28
#define CAN_TIxR_EXID_26								29
#define CAN_TIxR_EXID_27								30
#define CAN_TIxR_EXID_28								31
#define CAN_TIxR_EXID_MASK							(0x1FFFFFFF << CAN_TIxR_EXID_0)

#define CAN_TDTxR(n)										(0x40006584 + ((n) * 16))
#define CAN_TDTxR_DLC_0									0
#define CAN_TDTxR_DLC_1									1
#define CAN_TDTxR_DLC_2									2
#define CAN_TDTxR_DLC_3									3
#define CAN_TDTxR_DLC_MASK							(0x0F << CAN_TDTxR_DLC_0)
#define CAN_TDTxR_TGT										8
#define CAN_TDTxR_TIME_0								16
#define CAN_TDTxR_TIME_1								17
#define CAN_TDTxR_TIME_2								18
#define CAN_TDTxR_TIME_3								19
#define CAN_TDTxR_TIME_4								20
#define CAN_TDTxR_TIME_5								21
#define CAN_TDTxR_TIME_6								22
#define CAN_TDTxR_TIME_7								23
#define CAN_TDTxR_TIME_8								24
#define CAN_TDTxR_TIME_9								25
#define CAN_TDTxR_TIME_10								26
#define CAN_TDTxR_TIME_11								27
#define CAN_TDTxR_TIME_12								28
#define CAN_TDTxR_TIME_13								29
#define CAN_TDTxR_TIME_14								30
#define CAN_TDTxR_TIME_15								31
#define CAN_TDTxR_TIME_MASK							(0xFFFF << CAN_TDTxR_TIME_0)

#define CAN_TDLxR(n)										(0x40006588 + ((n) * 16))
#define CAN_TDHxR(n)										(0x4000658C + ((n) * 16))

#define CAN_RIxR(n)											(0x400065B0 + ((n) * 16))
#define CAN_RIxR_RTR										1
#define CAN_RIxR_IDE										2
#define CAN_RIxR_STID_0									21
#define CAN_RIxR_STID_1									22
#define CAN_RIxR_STID_2									23
#define CAN_RIxR_STID_3									24
#define CAN_RIxR_STID_4									25
#define CAN_RIxR_STID_5									26
#define CAN_RIxR_STID_6									27
#define CAN_RIxR_STID_7									28
#define CAN_RIxR_STID_8									29
#define CAN_RIxR_STID_9									30
#define CAN_RIxR_STID_10								31
#define CAN_RIxR_STID_MASK							(0x7FF << CAN_RIxR_STID_0)
#define CAN_RIxR_EXID_0									3
#define CAN_RIxR_EXID_1									4
#define CAN_RIxR_EXID_2									5
#define CAN_RIxR_EXID_3									6
#define CAN_RIxR_EXID_4									7
#define CAN_RIxR_EXID_5									8
#define CAN_RIxR_EXID_6									9
#define CAN_RIxR_EXID_7									10
#define CAN_RIxR_EXID_8									11
#define CAN_RIxR_EXID_9									12
#define CAN_RIxR_EXID_10								13
#define CAN_RIxR_EXID_11								14
#define CAN_RIxR_EXID_12								15
#define CAN_RIxR_EXID_13								16
#define CAN_RIxR_EXID_14								17
#define CAN_RIxR_EXID_15								18
#define CAN_RIxR_EXID_16								19
#define CAN_RIxR_EXID_17								20
#define CAN_RIxR_EXID_18								21
#define CAN_RIxR_EXID_19								22
#define CAN_RIxR_EXID_20								23
#define CAN_RIxR_EXID_21								24
#define CAN_RIxR_EXID_22								25
#define CAN_RIxR_EXID_23								26
#define CAN_RIxR_EXID_24								27
#define CAN_RIxR_EXID_25								28
#define CAN_RIxR_EXID_26								29
#define CAN_RIxR_EXID_27								30
#define CAN_RIxR_EXID_28								31
#define CAN_RIxR_EXID_MASK							(0x1FFFFFFF << CAN_RIxR_EXID_0)

#define CAN_RDTxR(n)										(0x400065B4 + ((n) * 16))
#define CAN_RDTxR_DLC_0									0
#define CAN_RDTxR_DLC_1									1
#define CAN_RDTxR_DLC_2									2
#define CAN_RDTxR_DLC_3									3
#define CAN_RDTxR_DLC_MASK							(0x0F << CAN_RDTxR_DLC_0)
#define CAN_RDTxR_TGT										8
#define CAN_RDTxR_TIME_0								16
#define CAN_RDTxR_TIME_1								17
#define CAN_RDTxR_TIME_2								18
#define CAN_RDTxR_TIME_3								19
#define CAN_RDTxR_TIME_4								20
#define CAN_RDTxR_TIME_5								21
#define CAN_RDTxR_TIME_6								22
#define CAN_RDTxR_TIME_7								23
#define CAN_RDTxR_TIME_8								24
#define CAN_RDTxR_TIME_9								25
#define CAN_RDTxR_TIME_10								26
#define CAN_RDTxR_TIME_11								27
#define CAN_RDTxR_TIME_12								28
#define CAN_RDTxR_TIME_13								29
#define CAN_RDTxR_TIME_14								30
#define CAN_RDTxR_TIME_15								31
#define CAN_RDTxR_TIME_MASK							(0xFFFF << CAN_RDTxR_TIME_0)

#define CAN_RDLxR(n)										(0x400065B8 + ((n) * 16))
#define CAN_RDHxR(n)										(0x400065BC + ((n) * 16))

#define CAN_FMR													0x40006600
#define CAN_FMR_FINIT										0

#define CAN_FM1R												0x40006604
#define CAN_FS1R												0x4000660C
#define CAN_FFA1R												0x40006614
#define CAN_FA1R												0x4000661C
#define CAN_FxR1(n)											(0x40006640 + (n) * 8)
#define CAN_FxR2(n)											(0x40006640 + (n) * 8 + 4)
#else
#define RCC_APB1ENR											0x4002101C
#define RCC_APB1RENR_CAN1EN							25
#define RCC_APB1RENR_CAN2EN							26

#define CAN_MCR(can)											(can)
#define CAN_MCR_INRQ											0
#define CAN_MCR_SLEEP										1
#define CAN_MCR_TXFP											2
#define CAN_MCR_RFLM											3
#define CAN_MCR_NART											4
#define CAN_MCR_AWUM											5
#define CAN_MCR_ABOM											6
#define CAN_MCR_TTCM											7
#define CAN_MCR_DBF											16

#define CAN_MSR(can)											((can) + 0x04)
#define CAN_MSR_INAK											0
#define CAN_MSR_SLAK											1
#define CAN_MSR_ERRI											2
#define CAN_MSR_WKUI											3
#define CAN_MSR_SLAKI										4
#define CAN_MSR_TXM											8
#define CAN_MSR_RXM											9
#define CAN_MSR_SAMP											10
#define CAN_MSR_RX												11

#define CAN_TSR(can)											((can) + 0x08)
#define CAN_TSR_STAT_OFFSET(n)					((n) * 8)
#define CAN_TSR_STAT_MASK(n)						(0x0F << CAN_TSR_STAT_OFFSET(n))
#define CAN_TSR_RQCPx(can, n)						BITBEND((can) + 8, (n) * 8)
#define CAN_TSR_TXOKx(can, n)						BITBEND((can) + 8, (n) * 8 + 1)
#define CAN_TSR_ALSTx(can, n)						BITBEND((can) + 8, (n) * 8 + 2)
#define CAN_TSR_TEERx(can, n)						BITBEND((can) + 8, (n) * 8 + 3)
#define CAN_TSR_ABRQx(can, n)						BITBEND((can) + 8, (n) * 8 + 7)
#define CAN_TSR_CODE_OFFSET							24
#define CAN_TSR_CODE_MASK								(0x03 << CAN_TSR_CODE_OFFSET)
#define CAN_TSR_TMEx(can, n)						BITBEND((can) + 8, 26 + (n))
#define CAN_TSR_LOWx(can, n)						BITBEND((can) + 8, 29 + (n))
#define CAN_RFxR(can, n)								HWREG32((can) + 0x0C + (n) * 4)
#define CAN_RFxR_FMP_OFFSET							0
#define CAN_RFxR_FMP_MASK								(0x03 << CAN_RFxR_FMP_OFFSET)
#define CAN_RFxR_FULL(can, n)						BITBEND((can) + 0x0c + (n) * 4, 3)
#define CAN_RFxR_FOVR(can, n)						BITBEND((can) + 0x0c + (n) * 4, 4)
#define CAN_RFxR_RFOM(can, n)						BITBEND((can) + 0x0c + (n) * 4, 5)
#define CAN_IERx(can, n)								BITBEND((can) + 0x14, n)
#define CAN_ESR(can)											HWREG32((can) + 0x18)
#define CAN_ESR_EWGF(can)								BITBEND((can) + 0x18, 0)
#define CAN_ESR_EPVF(can)								BITBEND((can) + 0x18, 1)
#define CAN_ESR_BOFF(can)								BITBEND((can) + 0x18, 2)
#define CAN_ESR_LEC_OFFSET							4
#define CAN_ESR_LEC_MASK								(0x07 << CAN_ESR_LEC_OFFSET)
#define CAN_ESR_TEC_OFFSET							16
#define CAN_ESR_TEC_MASK								(0xFF << CAN_ESR_TEC_OFFSET)
#define CAN_ESR_REC_OFFSET							24
#define CAN_ESR_REC_MASK								(0xFF << CAN_ESR_REC_OFFSET)
#define CAN_BTR(can)											HWREG32((can) + 0x1C)
#define CAN_BTR_BRP_OFFSET							0
#define CAN_BTR_BRP_MASK								(0x3FF << CAN_BTR_BRP_OFFSET)
#define CAN_BTR_TS1_OFFSET							16
#define CAN_BTR_TS1_MASK								(0x0F << CAN_BTR_TS1_OFFSET)
#define CAN_BTR_TS2_OFFSET							20
#define CAN_BTR_TS2_MASK								(0x07 << CAN_BTR_TS2_OFFSET)
#define CAN_BTR_SJW_OFFSET							24
#define CAN_BTR_SJW_MASK								(0x03 << CAN_BTR_SJW_OFFSET)
#define CAN_BTR_LBKM(can)								BITBEND((can) + 0x1C, 30)
#define CAN_BTR_SILM(can)								BITBEND((can) + 0x1C, 31)
#define CAN_TIxR(can, n)								HWREG32((can) + 0x180 + ((n) << 4))
#define CAN_TIxR_TXRQ(can, n)						BITBEND((can) + 0x180 + ((n) << 4), 0)
#define CAN_TIxR_RTR(can, n)						BITBEND((can) + 0x180 + ((n) << 4), 1)
#define CAN_TIxR_IDE(can, n)						BITBEND((can) + 0x180 + ((n) << 4), 2)
#define CAN_TIxR_STID_OFFSET						21
#define CAN_TIxR_STID_MASK							(0x7FF << CAN_TIxR_STID_OFFSET)
#define CAN_TIxR_EXID_OFFSET						3
#define CAN_TIxR_EXID_MASK							(0x1FFFFFFF << CAN_TIxR_EXID_OFFSET)
#define CAN_TDTxR(can, n)								HWREG32((can) + 0x184 + ((n) << 4))
#define CAN_TDTxR_DLC_OFFSET						0
#define CAN_TDTxR_DLC_MASK							(0x0F << CAN_TDTxR_DLC_OFFSET)
#define CAN_TDTxR_TGT(can, n)						BITBEND((can) + 0x180 + ((n) << 4), 8)
#define CAN_TDTxR_TIME_OFFSET						16
#define CAN_TDTxR_TIME_MASK							(0xFFFF << CAN_TDTxR_TIME_OFFSET)
#define CAN_TDLxR(can, n)								HWREG32((can) + 0x188 + ((n) << 4))
#define CAN_TDHxR(can, n)								HWREG32((can) + 0x18C + ((n) << 4))
#define CAN_RIxR(can, n)								HWREG32((can) + 0x1B0 + ((n) << 4))
#define CAN_RIxR_RTR(can, n)						BITBEND((can) + 0x1B0 + ((n) << 4), 1)
#define CAN_RIxR_IDE(can, n)						BITBEND((can) + 0x1B0 + ((n) << 4), 2)
#define CAN_RIxR_STID_OFFSET						21
#define CAN_RIxR_STID_MASK							(0x7FF << CAN_RIxR_STID_OFFSET)
#define CAN_RIxR_EXID_OFFSET						3
#define CAN_RIxR_EXID_MASK							(0x1FFFFFFF << CAN_RIxR_EXID_OFFSET)
#define CAN_RDTxR(can, n)								HWREG32((can) + 0x1B4 + ((n) << 4))
#define CAN_RDTxR_DLC_OFFSET						0
#define CAN_RDTxR_DLC_MASK							(0x0F << CAN_RDTxR_DLC_OFFSET)
#define CAN_RDTxR_FMI_OFFSET						8
#define CAN_RDTxR_FMI_MASK							(0xFF << CAN_RDTxR_FMI_OFFSET)
#define CAN_RDTxR_TIME_OFFSET						16
#define CAN_RDTxR_TIME_MASK							(0xFFFF << CAN_RDTxR_TIME_OFFSET)
#define CAN_RDLxR(can, n)								HWREG32((can) + 0x1B8 + ((n) << 4))
#define CAN_RDHxR(can, n)								HWREG32((can) + 0x1BC + ((n) << 4))
#define CAN_FMR(can)											HWREG32((can) + 0x200)
#define CAN_FMR_FINIT(can)							BITBEND((can) + 0x200, 0)
#define CAN_FM1R(can)										HWREG32((can) + 0x204)
#define CAN_FM1R_FBMx(can, n)						BITBEND((can) + 0x204, n)
#define CAN_FS1R(can)										HWREG32((can) + 0x20C)
#define CAN_FS1R_FSCx(can, n)						BITBEND((can) + 0x20C, n)
#define CAN_FFA1R	(can)										HWREG32((can) + 0x214)
#define CAN_FFA1R_FFAx(can, n)					BITBEND((can) + 0x214, n)
#define CAN_FA1R(can)										HWREG32((can) + 0x21C)
#define CAN_FA1R_FACTx(can, n)					BITBEND((can) + 0x21C, n)
#define CAN_FxR1(can, n)								HWREG32((can) + 0x240 + (n) * 8)
#define CAN_FxR2(can, n)								HWREG32((can) + 0x240 + (n) * 8 + 4)
#endif

#if !(defined(STM32F105) || defined(STM32F107))
void CAN_Enable(void) {
	BITBEND_SET(RCC_APB1ENR, RCC_APB1ENR_CANEN, 1);
}

void CAN_Disable(void) {
	BITBEND_SET(RCC_APB1ENR, RCC_APB1ENR_CANEN, 0);
}

int CAN_IsEnabled(void) {
	return BITBEND(RCC_APB1ENR, RCC_APB1ENR_CANEN);
}

void CAN_Reset(void) {
	BITBEND_SET(RCC_APB1RSTR, RCC_APB1RSTR_CANRST, 1);
}

int CAN_SetMode(enum_can_mode mode) {
	uint32_t mcr;

#if defined(DO_PARAM_CHECKING)
	if (mode < CAN_MODE_NORMAL || mode > CAN_MODE_SLEEP)
		return -1;
#endif

	mcr = HWREG32(CAN_MCR);
	mcr &= ~0x03;
	mcr |= mode;
	HWREG32_SET(CAN_MCR, mcr);

	while (1) {
		if (mode == CAN_MODE_SLEEP || (HWREG32(CAN_MCR) & 0x03) == mode)
			break;
	}

	return 0;
}

int CAN_GetMode(void) {
	return (HWREG32(CAN_MCR) & 0x03);
}

int CAN_SetTransmissionMailboxPriority(enum_can_transmission_maibox_priority prio) {
#if defined(DO_PARAM_CHECKING)
	if (prio != CAN_TRANSMISSION_MAILBOX_PRIORITY_DRIVEN_BY_ID &&
		prio != CAN_TRANSMISSION_MAILBOX_PRIORITY_DRIVEN_BY_ORDER)
		return -1;
#endif

	BITBEND_SET(CAN_MCR, CAN_MCR_TXFP, prio);

	return 0;
}

int CAN_GetTransmissionMailboxPriority(void) {
	return BITBEND(CAN_MCR, CAN_MCR_TXFP);
}

int CAN_SetReceiptionFifoLockMode(enum_can_receiption_fifo_lock_mode mode) {
#if defined(DO_PARAM_CHECKING)
	if (mode != CAN_RECEIPTION_FIFO_UNLOCKED_ON_OVERRUN &&
		mode != CAN_RECEIPTION_FIFO_LOCKED_AGAINST_OVERRUN)
		return -1;
#endif

	BITBEND_SET(CAN_MCR, CAN_MCR_RFLM, mode);

	return 0;
}

int CAN_GetReceiptionFifoLockMode(void) {
	return BITBEND(CAN_MCR, CAN_MCR_RFLM);
}

void CAN_EnableAutoRetransimit(void) {
	BITBEND_SET(CAN_MCR, CAN_MCR_RFLM, 0);
}

void CAN_DisableAutoRetransimit(void) {
	BITBEND_SET(CAN_MCR, CAN_MCR_RFLM, 1);
}

int CAN_IsAutoRetransimitEnabled(void) {
	return (BITBEND(CAN_MCR, CAN_MCR_RFLM) ? 0 : 1);
}

void CAN_EnableAutoWakeup(void) {
	BITBEND_SET(CAN_MCR, CAN_MCR_AWUM, 1);
}

void CAN_DisableAutoWakeup(void) {
	BITBEND_SET(CAN_MCR, CAN_MCR_AWUM, 0);
}

int CAN_IsAutoWakeupEnabled(void) {
	return BITBEND(CAN_MCR, CAN_MCR_AWUM);
}

void CAN_EnableAutoBuslink(void) {
	BITBEND_SET(CAN_MCR, CAN_MCR_ABOM, 1);
}

void CAN_DisableAutoBuslink(void) {
	BITBEND_SET(CAN_MCR, CAN_MCR_ABOM, 0);
}

int CAN_IsAutoBuslinkEnabled(void) {
	return BITBEND(CAN_MCR, CAN_MCR_ABOM);
}

void CAN_EnableDebugFreeze(void) {
	BITBEND_SET(CAN_MCR, CAN_MCR_DBF, 1);
}

void CAN_DisableDebugFreeze(void) {
	BITBEND_SET(CAN_MCR, CAN_MCR_DBF, 0);
}

int CAN_IsDebugFreezeEnabled(void) {
	return BITBEND(CAN_MCR, CAN_MCR_DBF);
}

int CAN_SetBitRate(unsigned int bps, unsigned int sjw) {
	uint32_t btr;
	unsigned int psc, ntq, ntq2, diff, diff_min;
	unsigned int ntq_try, psc_try;

#if defined(DO_PARAM_CHECKING)
	if (bps > 1000000 || bps < 1000 || sjw < 1 || sjw > 4)
		return -1;
#endif

	diff_min = bps;
	diff = bps;
	ntq = 25;
	psc = MAX(1, RCC_GetApb1Clk() / bps / 25);

	for (ntq_try = 25; ntq_try >= 8; ntq_try--) {
		for (psc_try = MAX(1, RCC_GetApb1Clk() / bps / ntq_try); psc_try < 0x3FF; psc_try++) {
			diff = bps - RCC_GetApb1Clk() / psc_try / ntq_try;

			if (diff == 0)
				break;

			if (diff < diff_min) {
				diff_min = diff;
				psc = psc_try;
				ntq = ntq_try;
			}
		}

		if (diff == 0) {
			psc = psc_try;
			ntq = ntq_try;
			break;
		}
	}

	ntq2 = MIN(8, (ntq - 1) / 2);
	ntq = MIN(16, ntq - 1 - ntq2);

	btr = HWREG32(CAN_BTR);
	btr &= ~CAN_BTR_BRP_MASK;
	btr |= ((psc - 1) << CAN_BTR_BRP_0);
	btr &= ~CAN_BTR_TS1_MASK;
	btr |= ((ntq - 1) << CAN_BTR_TS1_0);
	btr &= ~CAN_BTR_TS2_MASK;
	btr |= ((ntq2 - 1) << CAN_BTR_TS2_0);
	btr &= ~CAN_BTR_SJW_MASK;
	btr |= (sjw << CAN_BTR_SJW_0);
	HWREG32_SET(CAN_BTR, btr);

	return 0;
}

int CAN_GetBitRate(void) {
	unsigned int psc, ntq, ntq2;

	ntq = ((HWREG32(CAN_BTR) & CAN_BTR_TS1_MASK) >> CAN_BTR_TS1_0) + 1;
	ntq2 = ((HWREG32(CAN_BTR) & CAN_BTR_TS2_MASK) >> CAN_BTR_TS2_0) + 1;
	psc = ((HWREG32(CAN_BTR) & CAN_BTR_BRP_MASK) >> CAN_BTR_BRP_0) + 1;

	return (RCC_GetApb1Clk() / psc / (1 + ntq + ntq2));
}

int CAN_GetSJW(void) {
	return (((HWREG32(CAN_BTR) & CAN_BTR_SJW_MASK) >> CAN_BTR_SJW_0) + 1);
}

void CAN_EnableLoopbackMode(void) {
	BITBEND_SET(CAN_BTR, CAN_BTR_LBKM, 1);
}

void CAN_DisableLoopbackMode(void) {
	BITBEND_SET(CAN_BTR, CAN_BTR_LBKM, 0);
}

int CAN_IsLoopbackModeEnabled(void) {
	return BITBEND(CAN_BTR, CAN_BTR_LBKM);
}

void CAN_EnableSilentMode(void) {
	BITBEND_SET(CAN_BTR, CAN_BTR_SILM, 1);
}

void CAN_DisableSilentMode(void) {
	BITBEND_SET(CAN_BTR, CAN_BTR_SILM, 0);
}

int CAN_IsSlientModeEnabled(void) {
	return BITBEND(CAN_BTR, CAN_BTR_SILM);
}

int CAN_GetErrorStat(void) {
	return (HWREG32(CAN_ESR) & 0x07);
}
#else
int CAN_Enable(enum_can can) {
	if (can == CAN1) {
		BITBEND_SET(RCC_APB1ENR, RCC_APB1RENR_CAN1EN, 1);
	} else if (can == CAN2) {
		BITBEND_SET(RCC_APB1ENR, RCC_APB1RENR_CAN2EN, 1);
	} else
		return -1;

	return 0;
}

int CAN_Disable(enum_can can) {
	if (can == CAN1) {
		BITBEND_SET(RCC_APB1ENR, RCC_APB1RENR_CAN1EN, 0);
	} else if (can == CAN2) {
		BITBEND_SET(RCC_APB1ENR, RCC_APB1RENR_CAN2EN, 0);
	} else
		return -1;

	return 0;
}

int CAN_IsEnabled(enum_can can) {
	if (can == CAN1)
		return BITBEND(RCC_APB1ENR, RCC_APB1RENR_CAN1EN);
	else if (can == CAN2)
		return BITBEND(RCC_APB1ENR, RCC_APB1RENR_CAN2EN);

	return -1;
}

int CAN_Reset(enum_can can) {
	return 0;
}

int CAN_SetMode(enum_can can, enum_can_mode mode) {
	uint32_t mcr;

#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;

	if (mode < CAN_MODE_NORMAL || mode > CAN_MODE_SLEEP)
		return -1;
#endif

	mcr = HWREG32(CAN_MCR(can));
	mcr &= ~0x03;
	mcr |= mode;
	HWREG32_SET(CAN_MCR(can), mcr);

	while (1) {
		if (mode == CAN_MODE_SLEEP || (HWREG32(CAN_MCR(can)) & 0x03) == mode)
			break;
	}

	return 0;
}

int CAN_GetMode(enum_can can) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;
#endif

	return (HWREG32(CAN_MCR(can)) & 0x03);
}

int CAN_SetTransmissionMailboxPriority(enum_can can, enum_can_transmission_maibox_priority prio) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;

	if (prio != CAN_TRANSMISSION_MAILBOX_PRIORITY_DRIVEN_BY_ID &&
		prio != CAN_TRANSMISSION_MAILBOX_PRIORITY_DRIVEN_BY_ORDER)
		return -1;
#endif

	BITBEND_SET(CAN_MCR(can), CAN_MCR_TXFP, prio);

	return 0;
}

int CAN_GetTransmissionMailboxPriority(enum_can can) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;
#endif

	return BITBEND(CAN_MCR(can), CAN_MCR_TXFP);
}

int CAN_SetReceiptionFifoLockMode(enum_can can, enum_can_receiption_fifo_lock_mode mode) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;

	if (mode != CAN_RECEIPTION_FIFO_UNLOCKED_ON_OVERRUN &&
		mode != CAN_RECEIPTION_FIFO_LOCKED_AGAINST_OVERRUN)
		return -1;
#endif

	BITBEND_SET(CAN_MCR(can), CAN_MCR_RFLM, mode);

	return 0;
}

int CAN_GetReceiptionFifoLockMode(enum_can can) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;
#endif

	return BITBEND(CAN_MCR(can), CAN_MCR_RFLM);
}

int CAN_EnableAutoRetransimit(enum_can can) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;
#endif

	BITBEND_SET(CAN_MCR(can), CAN_MCR_RFLM, 0);

	return 0;
}

int CAN_DisableAutoRetransimit(enum_can can) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;
#endif

	BITBEND_SET(CAN_MCR(can), CAN_MCR_RFLM, 1);

	return 0;
}

int CAN_IsAutoRetransimitEnabled(enum_can can) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;
#endif

	return (BITBEND(CAN_MCR(can), CAN_MCR_RFLM) ? 0 : 1);
}

int CAN_EnableAutoWakeup(enum_can can) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;
#endif

	BITBEND_SET(CAN_MCR(can), CAN_MCR_AWUM, 1);

	return 0;
}

int CAN_DisableAutoWakeup(enum_can can) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;
#endif

	BITBEND_SET(CAN_MCR(can), CAN_MCR_AWUM, 0);

	return 0;
}

int CAN_IsAutoWakeupEnabled(enum_can can) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;
#endif

	return BITBEND(CAN_MCR(can), CAN_MCR_AWUM);
}

int CAN_EnableAutoBuslink(enum_can can) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;
#endif

	BITBEND_SET(CAN_MCR(can), CAN_MCR_ABOM, 1);

	return 0;
}

int CAN_DisableAutoBuslink(enum_can can) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;
#endif

	BITBEND_SET(CAN_MCR(can), CAN_MCR_ABOM, 0);

	return 0;
}

int CAN_IsAutoBuslinkEnabled(enum_can can) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;
#endif

	return BITBEND(CAN_MCR(can), CAN_MCR_ABOM);
}

int CAN_EnableDebugFreeze(enum_can can) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;
#endif

	BITBEND_SET(CAN_MCR(can), CAN_MCR_DBF, 1);

	return 0;
}

int CAN_DisableDebugFreeze(enum_can can) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;
#endif

	BITBEND_SET(CAN_MCR(can), CAN_MCR_DBF, 0);

	return 0;
}

int CAN_IsDebugFreezeEnabled(enum_can can) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;
#endif

	return BITBEND(CAN_MCR(can), CAN_MCR_DBF);
}

int CAN_SetBitRate(enum_can can, unsigned int bps, unsigned int sjw) {
	uint32_t btr;
	unsigned int psc, ntq, ntq2, diff, diff_min;
	unsigned int ntq_try, psc_try;

#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;

	if (bps > 1000000 || bps < 1000 || sjw < 1 || sjw > 4)
		return -1;
#endif

	diff_min = bps;
	diff = bps;
	ntq = 25;
	psc = MAX(1, RCC_GetApb1Clk() / bps / 25);

	for (ntq_try = 25; ntq_try >= 8; ntq_try--) {
		for (psc_try = MAX(1, RCC_GetApb1Clk() / bps / ntq_try); psc_try < 0x3FF; psc_try++) {
			diff = bps - RCC_GetApb1Clk() / psc_try / ntq_try;

			if (diff == 0)
				break;

			if (diff < diff_min) {
				diff_min = diff;
				psc = psc_try;
				ntq = ntq_try;
			}
		}

		if (diff == 0) {
			psc = psc_try;
			ntq = ntq_try;
			break;
		}
	}

	ntq2 = MIN(8, (ntq - 1) / 2);
	ntq = MIN(16, ntq - 1 - ntq2);

	btr = HWREG32(CAN_BTR(can));
	btr &= ~CAN_BTR_BRP_MASK;
	btr |= ((psc - 1) << CAN_BTR_BRP_OFFSET);
	btr &= ~CAN_BTR_TS1_MASK;
	btr |= ((ntq - 1) << CAN_BTR_TS1_OFFSET);
	btr &= ~CAN_BTR_TS2_MASK;
	btr |= ((ntq2 - 1) << CAN_BTR_TS2_OFFSET);
	btr &= ~CAN_BTR_SJW_MASK;
	btr |= (sjw << CAN_BTR_SJW_OFFSET);
	HWREG32_SET(CAN_BTR(can), btr);

	return 0;
}

int CAN_GetBitRate(enum_can can) {
	unsigned int psc, ntq, ntq2;

#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;
#endif

	ntq = ((HWREG32(CAN_BTR(can)) & CAN_BTR_TS1_MASK) >> CAN_BTR_TS1_OFFSET) + 1;
	ntq2 = ((HWREG32(CAN_BTR(can)) & CAN_BTR_TS2_MASK) >> CAN_BTR_TS2_OFFSET) + 1;
	psc = ((HWREG32(CAN_BTR(can)) & CAN_BTR_BRP_MASK) >> CAN_BTR_BRP_OFFSET) + 1;

	return (RCC_GetApb1Clk() / psc / (1 + ntq + ntq2));
}

int CAN_GetSJW(enum_can can) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;
#endif

	return (((HWREG32(CAN_BTR(can)) & CAN_BTR_SJW_MASK) >> CAN_BTR_SJW_OFFSET) + 1);
}

int CAN_EnableLoopbackMode(enum_can can) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;
#endif

	BITBEND_SET(CAN_BTR(can), CAN_BTR_LBKM, 1);

	return 0;
}

int CAN_DisableLoopbackMode(enum_can can) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;
#endif

	BITBEND_SET(CAN_BTR(can), CAN_BTR_LBKM, 0);

	return 0;
}

int CAN_IsLoopbackModeEnabled(enum_can can) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;
#endif

	return BITBEND(CAN_BTR(can), CAN_BTR_LBKM);
}

int CAN_EnableSilentMode(enum_can can) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;
#endif

	BITBEND_SET(CAN_BTR(can), CAN_BTR_SILM, 1);

	return 0;
}

int CAN_DisableSilentMode(enum_can can) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;
#endif

	BITBEND_SET(CAN_BTR(can), CAN_BTR_SILM, 0);

	return 0;
}

int CAN_IsSlientModeEnabled(enum_can can) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;
#endif

	return BITBEND(CAN_BTR(can), CAN_BTR_SILM);
}

int CAN_GetErrorStat(enum_can can) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;
#endif

	return (HWREG32(CAN_ESR(can)) & 0x07);
}

// TODO: Go on modifying the following code
int CAN_GetTransmissionStat(enum_can can, unsigned int mailbox) {
	int ret_val;

#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;

	if (mailbox > 2)
		return -1;
#endif

	ret_val = (HWREG32(CAN_TSR(can)) & CAN_TSR_STAT_MASK(mailbox)) >> CAN_TSR_STAT_0(mailbox));
	if (ret_val == 0) {
		if (BITBEND(CAN_TSR(can), CAN_TSR_TMEx(mailbox)))
			return CAN_TRANSMISSION_STAT_IDLE;
	}

	return (ret_val + 1);
}

int CAN_ResetTransmissionMailbox(enum_can can, unsigned int mailbox) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;

	if (mailbox > 2)
		return -1;
#endif

	BITBEND_SET(CAN_TSR, CAN_TSR_RQCPx(mailbox), 1);

	return 0;
}

int CAN_LoadMessageToTransmissionMailbox(enum_can can, unsigned int mailbox, struct can_message *message) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;

	if (mailbox > 2 || message == NULL)
		return -1;

	if (message->data_len > 8)
		return -1;
#endif

	if (CAN_TIxR_TXRQ(can, mailbox))
		return -1;

	if (CAN_ID_IS_EXID(message->id)) {
		CAN_TIxR(can, mailbox) = CAN_ID_GET_ID(message->id) << CAN_TIxR_EXID_OFFSET;
		CAN_TIxR_IDE(can, mailbox) = 1;
	} else
		CAN_TIxR(can, mailbox) = CAN_ID_GET_ID(message->id) << CAN_TIxR_STID_OFFSET;

	if (message->type == CAN_DATA_MESSAGE) {
		CAN_TDLxR(can, mailbox) = message->data32[0];
		CAN_TDHxR(can, mailbox) = message->data32[1];
		CAN_TDTxR(can, mailbox) = message->data_len;
	} else if (message->type == CAN_REMOTE_MESSAGE) {
		CAN_TIxR_RTR(can, mailbox) = 1;
		CAN_TDTxR(can, mailbox) = 0;
	}
	else
		return -1;

	DSB();
	ISB();

	return 0;
}

int CAN_StartTransmission(enum_can can, unsigned int mailbox) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;

	if (mailbox > 2)
		return -1;
#endif

	if (CAN_TIxR_TXRQ(can, mailbox))
		return -1;

	CAN_TIxR_TXRQ(can, mailbox) = 1;
	return 0;
}

int CAN_AbortTransmission(enum_can can, unsigned int mailbox) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;

	if (mailbox > 2)
		return -1;
#endif

	CAN_TSR_ABRQx(can, mailbox) = 1;
	return 0;
}

// TODO: Go on modifying the following code
int CAN_IsReceiptionFifoFull(enum_can can, unsigned int fifo) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;

	if (fifo > 1)
		return -1;
#endif

	return CAN_RFxR_FULL(can, fifo);
}

int CAN_IsReceiptionFifoOverrun(enum_can can, unsigned int fifo) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;

	if (fifo > 1)
		return -1;
#endif

	return CAN_RFxR_FOVR(can, fifo);
}

int CAN_ResetReceiptionFifo(enum_can can, unsigned int fifo) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;

	if (fifo > 1)
		return -1;
#endif

	CAN_RFxR_FULL(can, fifo) = 1;
	CAN_RFxR_FOVR(can, fifo) = 1;

	return 0;
}

int CAN_CountReceiptedMessage(enum_can can, unsigned int fifo) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;

	if (fifo > 1)
		return -1;
#endif

	return (CAN_RFxR(can, fifo) & 0x03);
}

int CAN_QueryReceiptionMessage(enum_can can, unsigned int fifo, struct can_message *message) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;

	if (fifo > 1 || message == NULL)
		return -1;
#endif

	if (CAN_RIxR_IDE(can, fifo))
		message->id = CAN_ID_MAKE_ID(CAN_ID_EXID, (CAN_RIxR(can, fifo) & CAN_RIxR_EXID_MASK) >> CAN_RIxR_EXID_OFFSET);
	else
		message->id = CAN_ID_MAKE_ID(CAN_ID_STID, (CAN_RIxR(can, fifo) & CAN_RIxR_STID_MASK) >> CAN_RIxR_STID_OFFSET);

	if (CAN_RIxR_RTR(can, fifo)) {
		message->type = CAN_REMOTE_MESSAGE;
		message->data_len = 0;
	}
	else {
		message->type = CAN_DATA_MESSAGE;
		message->data_len = (CAN_RDTxR(can, fifo) & CAN_RDTxR_DLC_MASK) >> CAN_RDTxR_DLC_OFFSET;
		message->data32[0] = CAN_RDLxR(can, fifo);
		message->data32[1] = CAN_RDHxR(can, fifo);
	}

	return 0;
}

int CAN_ReleaseReceiptionMessage(enum_can can, unsigned int fifo) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;

	if (fifo > 1)
		return -1;
#endif

	CAN_RFxR_RFOM(can, fifo) = 1;
	return 0;
}

int CAN_SetTypeOfReceiptionFilter(enum_can can, unsigned int filter, enum_can_receiption_filter_type type) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;

	if (filter > 27 || type < CAN_16BIT_ID_MASK_FILTER || type > CAN_32BIT_ID_LIST_FILTER)
		return -1;
#endif

	if (CAN_FA1R_FACTx(can, filter))
		return -1;

	CAN_FMR_FINIT(can) = 1;
	DSB();
	ISB();

	CAN_FS1R_FSCx(can, filter) = (type & 0x02) >> 1;
	CAN_FM1R_FBMx(can, filter) = (type & 0x01);

	CAN_FMR_FINIT(can) = 0;
	DSB();
	ISB();

	return 0;
}

int CAN_GetTypeOfReceiptionFilter(enum_can can, unsigned int filter) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;

	if (filter > 27)
		return -1;
#endif

	return ((CAN_FS1R_FSCx(can, filter) << 1) | CAN_FM1R_FBMx(can, filter));
}

int CAN_SetReceiptionFilter(enum_can can, unsigned int i, unsigned int slot, struct can_receiption_filter *filter) {
	uint32 addr;

#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;
#endif

	if (filter == NULL || filter->filter_type != CAN_GetTypeOfReceiptionFilter(can, i))
		return -1;

	if (filter->filter_type == CAN_16BIT_ID_MASK_FILTER && slot < 2) {
		if (CAN_ID_IS_EXID(filter->mask) && (CAN_ID_GET_ID(filter->mask) & 0x3FFC7FFF))
			return -1;

		if (CAN_ID_IS_EXID(filter->id) && (CAN_ID_GET_ID(filter->id) & 0x3FFC7FFF))
			return -1;

		addr = can + 0x240 + i * 8 + slot * 4;
		CAN_FMR_FINIT(can) = 1;
		DSB();
		ISB();

		if (CAN_ID_IS_EXID(filter->mask))
			HWREG32(addr) = ((CAN_ID_GET_ID(filter->mask) >> 15) | BV(3)) << 16;
		else
			HWREG32(addr) = ((CAN_ID_GET_ID(filter->mask) << 5) << 16);

		if (CAN_ID_IS_EXID(filter->id))
			HWREG32(addr) |= (CAN_ID_GET_ID(filter->id) >> 15) | BV(3);
		else
			HWREG32(addr) |= CAN_ID_GET_ID(filter->id) << 5;

		if (filter->message_type == CAN_REMOTE_MESSAGE) {
			HWREG32(addr) |= BV(20) | BV(4);

			CAN_FMR_FINIT(can) = 0;
			DSB();
			ISB();
		}
		else if (filter->message_type == CAN_DATA_MESSAGE) {
			HWREG32(addr) |= BV(20);

			CAN_FMR_FINIT(can) = 0;
			DSB();
			ISB();
		}
		else if (filter->message_type != CAN_ALL_SORTS_OF_MESSAGE) {
			CAN_FMR_FINIT(can) = 0;
			DSB();
			ISB();
			return -1;
		}
	} else if (filter->filter_type == CAN_16BIT_ID_LIST_FILTER && slot < 4) {
		if (CAN_ID_IS_EXID(filter->id) && (CAN_ID_GET_ID(filter->id) & 0x3FFC7FFF))
			return -1;

		addr = 0x40006640 + i * 8 + (slot / 2) * 4;

		CAN_FMR_FINIT(can) = 1;
		DSB();
		ISB();

		HWREG32(addr) &= ~(0xFFFF << ((slot & 0x01) * 16));

		if (CAN_ID_IS_EXID(filter->id))
			HWREG32(addr) |= ((CAN_ID_GET_ID(filter->id) >> 15) | BV(3)) << ((slot & 0x01) * 16);
		else
			HWREG32(addr) |= ((CAN_ID_GET_ID(filter->id) << 5) << ((slot & 0x01) * 16));

		if (filter->message_type == CAN_REMOTE_MESSAGE) {
			HWREG32(addr) |= BV(4 + (slot & 0x01) * 16);

			CAN_FMR_FINIT(can) = 0;
			DSB();
			ISB();
		}
		else if (filter->message_type != CAN_DATA_MESSAGE) {
			CAN_FMR_FINIT(can) = 0;
			DSB();
			ISB();
			return -1;
		}
	} else if (filter->filter_type == CAN_32BIT_ID_MASK_FILTER && slot < 1) {
		if (CAN_ID_IS_EXID(filter->mask) && (CAN_ID_GET_ID(filter->mask) & 0x3FFC0000))
			return -1;

		if (CAN_ID_IS_EXID(filter->id) && (CAN_ID_GET_ID(filter->id) & 0x3FFC0000))
			return -1;

		CAN_FMR_FINIT(can) = 1;
		DSB();
		ISB();

		if (CAN_ID_IS_EXID(filter->mask))
			CAN_FxR2(can, i) = ((CAN_ID_GET_ID(filter->mask) & 0x3FFFF) << 3) | BV(2);
		else
			CAN_FxR2(can, i) = CAN_ID_GET_ID(filter->mask) << 20;

		if (CAN_ID_IS_EXID(filter->id))
			CAN_FxR1(can, i) = (CAN_ID_GET_ID(filter->id) << 3) | BV(2);
		else
			CAN_FxR1(can, i) = CAN_ID_GET_ID(filter->id) << 20;

		if (filter->message_type == CAN_REMOTE_MESSAGE) {
			CAN_FxR2(can, i) |= BV(1);
			CAN_FxR1(can, i) |= BV(1);

			CAN_FMR_FINIT(can) = 0;
			DSB();
			ISB();
		} else if (filter->message_type == CAN_DATA_MESSAGE) {
			CAN_FxR2(can, i) |= BV(1);

			CAN_FMR_FINIT(can) = 0;
			DSB();
			ISB();
		}
		else if (filter->message_type != CAN_ALL_SORTS_OF_MESSAGE) {
			CAN_FMR_FINIT(can) = 0;
			DSB();
			ISB();

			return -1;
		}
	} else if (filter->filter_type == CAN_32BIT_ID_LIST_FILTER && slot < 2) {
		if (CAN_ID_IS_EXID(filter->id) && (CAN_ID_GET_ID(filter->id) & 0x3FFC0000))
			return -1;

		addr = 0x40006640 + i * 8 + slot * 4;
		CAN_FMR_FINIT(can) = 1;
		DSB();
		ISB();

		if (CAN_ID_IS_EXID(filter->id))
			HWREG32(addr) = (CAN_ID_GET_ID(filter->id) << 3) | BV(2);
		else
			HWREG32(addr) = CAN_ID_GET_ID(filter->id) << 20;

		if (filter->message_type == CAN_REMOTE_MESSAGE) {
			HWREG32(addr) |= BV(1);

			CAN_FMR_FINIT(can) = 0;
			DSB();
			ISB();
		}
		else if (filter->message_type != CAN_DATA_MESSAGE) {
			CAN_FMR_FINIT(can) = 0;
			DSB();
			ISB();

			return -1;
		}
	} else
		return -1;

	return 0;
}

int CAN_GetReceiptionFilter(enum_can can, unsigned int i, unsigned int slot, struct can_receiption_filter *filter) {
	uint32 addr;

#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;

	if (filter == NULL)
		return -1;
#endif

	if (CAN_GetTypeOfReceiptionFilter(can, i) == CAN_16BIT_ID_MASK_FILTER && slot < 2) {
		filter->filter_type = CAN_16BIT_ID_MASK_FILTER;
		addr = can + 0x240 + i * 8 + slot * 4;

		if (HWREG32(addr) & BV(3))
			filter->id = CAN_ID_MAKE_ID(CAN_ID_EXID, (HWREG32(addr) & 0x07) << 15);
		else
			filter->id = CAN_ID_MAKE_ID(CAN_ID_STID, (HWREG32(addr) >> 5) & 0x7FF);

		if (HWREG32(addr) & BV(19))
			filter->mask = CAN_ID_MAKE_ID(CAN_ID_EXID, ((HWREG32(addr) >> 16) & 0x07) << 15);
		else
			filter->mask = CAN_ID_MAKE_ID(CAN_ID_STID, (HWREG32(addr) >> 21) & 0x7FF);

		if (HWREG32(addr) & BV(20)) {
			if (HWREG32(addr) & BV(4))
				filter->message_type = CAN_REMOTE_MESSAGE;
			else
				filter->message_type = CAN_DATA_MESSAGE;
		} else
			filter->message_type = CAN_ALL_SORTS_OF_MESSAGE;
	} else if (CAN_GetTypeOfReceiptionFilter(can, i) == CAN_16BIT_ID_LIST_FILTER && slot < 4) {
		filter->filter_type = CAN_16BIT_ID_LIST_FILTER;
		addr = 0x40006640 + i * 8 + (slot / 2) * 4;

		if (HWREG32(addr) & BV((slot & 0x01) * 16 + 3))
			filter->id = CAN_ID_MAKE_ID(CAN_ID_EXID, ((HWREG32(addr) >> ((slot & 0x01) * 16)) & 0x07) << 15);
		else
			filter->id = CAN_ID_MAKE_ID(CAN_ID_STID, (HWREG32(addr) >> ((slot & 0x01) * 16 + 5)) & 0x7FF);

		if (HWREG32(addr) & BV((slot & 0x01) * 16 + 4))
			filter->message_type = CAN_REMOTE_MESSAGE;
		else
			filter->message_type = CAN_DATA_MESSAGE;
	} else if (CAN_GetTypeOfReceiptionFilter(can, i) == CAN_32BIT_ID_MASK_FILTER && slot < 1) {
		filter->filter_type = CAN_32BIT_ID_MASK_FILTER;

		if (CAN_FxR1(can, i) & BV(2))
			filter->id = CAN_ID_MAKE_ID(CAN_ID_EXID, (CAN_FxR1(can, i) >> 3) & 0x3FFFF);
		else
			filter->id = CAN_ID_MAKE_ID(CAN_ID_STID, (CAN_FxR1(can, i) >> 21) & 0x7FF);

		if (CAN_FxR2(can, i) & BV(2))
			filter->mask = CAN_ID_MAKE_ID(CAN_ID_EXID, (CAN_FxR2(can, i) >> 3) & 0x3FFFF);
		else
			filter->mask = CAN_ID_MAKE_ID(CAN_ID_STID, (CAN_FxR2(can, i) >> 21) & 0x7FF);

		if (CAN_FxR2(can, i) & BV(1)) {
			if (CAN_FxR1(can, i) & BV(1))
				filter->message_type = CAN_REMOTE_MESSAGE;
			else
				filter->message_type = CAN_DATA_MESSAGE;
		} else
			filter->message_type = CAN_ALL_SORTS_OF_MESSAGE;
	} else if (CAN_GetTypeOfReceiptionFilter(can, i) == CAN_32BIT_ID_LIST_FILTER && slot < 2) {
		filter->filter_type = CAN_32BIT_ID_LIST_FILTER;
		addr = 0x40006640 + i * 8 + slot * 4;

		if (HWREG32(addr) & BV(2))
			filter->id = CAN_ID_MAKE_ID(CAN_ID_EXID, (HWREG32(addr) >> 3) & 0x3FFFF);
		else
			filter->id = CAN_ID_MAKE_ID(CAN_ID_STID, (HWREG32(addr) >> 21) & 0x7FF);

		if (HWREG32(addr) & BV(1))
			filter->message_type = CAN_REMOTE_MESSAGE;
		else
			filter->message_type = CAN_DATA_MESSAGE;
	} else
		return -1;

	return 0;
}

int CAN_AssignReceiptionFilterToFifo(enum_can can, unsigned int i, unsigned int fifo) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;

	if (i > 27 || fifo > 1)
		return -1;
#endif

	CAN_FMR_FINIT(can) = 1;
	DSB();
	ISB();

	CAN_FFA1R_FFAx(can, i) = fifo;
	CAN_FMR_FINIT(can) = 0;
	DSB();
	ISB();

	return 0;
}

int CAN_GetAssocitedFilterIdOfReceiptionMessage(enum_can can, unsigned int i) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;

	if (i > 1)
		return -1;
#endif

	return ((CAN_RDTxR(can, i) & CAN_RDTxR_FMI_MASK) >> CAN_RDTxR_FMI_OFFSET);
}

int CAN_GetFifoReceiptionFilterAssignedTo(enum_can can, unsigned int i) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;

	if (i > 27)
		return -1;
#endif

	return CAN_FFA1R_FFAx(can, i);
}

int CAN_ActivateReceiptionFilter(enum_can can, unsigned int i) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;

	if (i > 27)
		return -1;
#endif

	CAN_FMR_FINIT(can) = 1;
	DSB();
	ISB();

	CAN_FA1R_FACTx(can, i) = 1;
	CAN_FMR_FINIT(can) = 0;
	DSB();
	ISB();

	return 0;
}

int CAN_DeactivateReceiptionFilter(enum_can can, unsigned int i) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;

	if (i > 27)
		return -1;
#endif

	CAN_FMR_FINIT(can) = 1;
	DSB();
	ISB();

	CAN_FA1R_FACTx(can, i) = 0;
	CAN_FMR_FINIT(can) = 0;
	DSB();
	ISB();

	return 0;
}

int CAN_IsReceiptionFilterActive(enum_can can, unsigned int i) {
#if defined(DO_PARAM_CHECKING)
	if (can != CAN1 && can != CAN2)
		return -1;

	if (i > 27)
		return -1;
#endif

	return CAN_FA1R_FACTx(can, i);
}
#endif
