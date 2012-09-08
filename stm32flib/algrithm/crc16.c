#include "stm32flib.h"

uint16_t __inline__ CRC16(uint16_t crc, uint8_t byte, uint16_t ploynomial) {
	register unsigned int i;

	crc ^= byte;
	for(i = 0; i < 8; i++) {
		if (crc & 0x01)
			crc =(crc >> 1) ^ ploynomial;
		else
			crc = crc >> 1;
	}

	return crc;
}

uint16_t CRC16_blk(void *data, unsigned int n, uint16_t ploynomial) {
	register uint16_t crc = 0xFFFF;
	register unsigned int i;

#if defined(DO_PARAM_CHECKING)
	if (data == NULL)
		return -1;
#endif

	for (i = 0; i < n; i++) {
		crc = CRC16(crc, *((uint8_t *)data), ploynomial);
		data += 1;
	}

	return crc;
}
