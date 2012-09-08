#include "stm32flib.h"

uint64_t DIV64(uint64_t a, uint64_t b, uint64_t *mod) {
	uint64_t t, result = 0;
	register unsigned int width_a, width_b;
	register unsigned int i;

	if (a >= 0xFFFFFFFF)
		width_a = MSBi((uint32_t)(a >> 32)) + 32 + 1;
	else
		width_a = MSBi((uint32_t)a) + 1;

	if (b >= 0xFFFFFFFF)
		width_b = MSBi((uint32_t)(b >> 32)) + 32 + 1;
	else
		width_b = MSBi((uint32_t)b) + 1;

	if (b == 0) {
		result = (uint64_t) - 1;
		a = (uint64_t) - 1;
	} else if ((((uint64_t)1) << (width_b - 1)) == b) {
		result = a >> (width_b - 1);
		a = 0;
	} else {
		for (i = width_a; i >= width_b; i--) {
			result = result << 1;

			t = b << (i - width_b);
			if (a > t) {
				a -= t;
				result |= 1;
			} else if (a == t) {
				a -= t;
				result = (result | 1) << (i - width_b);
				break;
			}
		}
	}

	if (mod != NULL)
		*mod = a;

	return result;
}
