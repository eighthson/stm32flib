#ifndef __DIV64_H__
#define __DIV64_H__

#ifdef __cplusplus
extern "C" {
#endif

uint16_t CRC16(uint16_t crc, uint16_t ploynomial);
uint16_t CRC16_blk(void *data, unsigned int n, uint16_t ploynomial);

#ifdef __cplusplus
}
#endif

#endif // __DIV64_H__
