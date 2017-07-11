
#ifndef SEATUNA_BLAKE2_H
#define SEATUNA_BLAKE2_H

#include <stdint.h>

struct seatuna_blake2_context {
	uint64_t state[8];
};

int blake2b_init();
int blake2b_update();
int blake2b_final();

#endif
