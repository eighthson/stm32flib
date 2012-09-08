#ifndef __FLASH_H__
#define __FLASH_H__

typedef enum {
	FLASH_LATENCY_0,
	FLASH_LATENCY_1,
	FLASH_LATENCY_2,
} enum_flash_latency;

#ifdef __cplusplus
extern "C" {
#endif

int FLASH_SetLatency(enum_flash_latency latency);
int FLASH_GetLatency(void);

void FLASH_EnableHalfAccess(void);
void FLASH_DisableHalfAccess(void);
int FLASH_IsHalfAccessEnabled(void);

void FLASH_EnablePrefetchBuffer(void);
void FLASH_DisablePrefetchBuffer(void);
int FLASH_IsPrefetchBufferEnabled(void);

void FLASH_Lock(void);
int FLASH_Unlock(void);
int FLASH_IsLocked(void);

int FLASH_ErasePage(void *data);
int FLASH_Write(void *addr, uint16_t halfword);
int FLASH_WriteBlock(void *addr, unsigned int n);

#ifdef __cplusplus
}
#endif

#endif // __FLASH_H__
