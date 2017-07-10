
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include "seatuna_chacha20.h"

#define GENBYTES 64*1000000
#define NSEC_PER_SEC 1000000000

int main(void)
{
	printf("-- Benchmarking ChaCha20 --\n");
	
	struct timespec st;
	struct timespec et;
	int64_t nsec;
	uint8_t *buffer = malloc(GENBYTES);
	uint8_t key[32] = {0};
	uint32_t counter = 0;
	uint8_t nonce[12] = {0};
	
	
	for (int i = 0; i < 100; ++i) {
		clock_gettime(CLOCK_MONOTONIC, &st);

		seatuna_chacha20_bytes(key, &counter, nonce, GENBYTES, buffer);
		
		clock_gettime(CLOCK_MONOTONIC, &et);
		
		nsec = (et.tv_sec - st.tv_sec) * NSEC_PER_SEC +
			(et.tv_nsec - st.tv_nsec);

		printf("%ld\t%d\n", nsec, GENBYTES);
	}
	
	free(buffer);

	return 0;
}
