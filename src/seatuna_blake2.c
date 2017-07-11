
#include <stdlib.h>
#include <stdio.h>

#include "seatuna_blake2.h"


static uint64_t blake2_iv[] = {
	0xcbbb9d5dc1059ed8, 0x629a292a367cd507, 0x9159015a3070dd17, 0x152fecd8f70e5939,
	0x67332667ffc00b31, 0x8eb44a8768581511, 0xdb0c2e0d64f98fa7, 0x47b5481dbefa4fa4};

void function() {
	
	uint32_t a[4];
	
	for (int i = 0; i < 8; ++i) {
		printf("%ld\n", blake2_iv[i]);
	}
	
	for (int i = 0; i < 4; ++i) {
		a[i] = blake2_iv[i] & 0xffffffff;
		printf("%du\n", a[i]);
	}
}
