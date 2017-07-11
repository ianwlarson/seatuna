
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "seatuna_chacha20.h"

int main(void)
{
	uint8_t key[32] = {0};
// 	for (int i = 0; i < 16; ++i) {
// 		key[i] = 0xa0 | i;
// 	}
// 	for (int i = 16; i < 32; ++i) {
// 		key[i] = 0xb0 | (i - 16);
// 	}
// 	uint32_t counter = 0xeeeeeeee;
// 	uint8_t nonce[12] = {0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xf0, 0xf1, 0xf2, 0xf3};
	uint32_t counter = 0x1;
	uint8_t nonce[12] = {0x0};
	
	uint8_t out[128] = {0};
	
	seatuna_chacha20_bytes(key, &counter, nonce, 128, out);
	
	uint32_t *abba = (uint32_t *)out;
	for (int i = 0; i < 128/4; ++i) {
		if (i % 4 == 0) {
			printf("\n");
		}
		printf("%08x ", abba[i]);
	}
	
	printf("\n");
	
	return out[127];
}
