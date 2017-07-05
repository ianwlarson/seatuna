
#ifndef SEATUNA_H
#define SEATUNA_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint32_t key[8];
    uint32_t nonce[3];
    uint64_t counter[2];
} SeaTuna_t;

bool seatuna_init(SeaTuna_t *state);

bool seatuna_seed(const uint8_t *seed, size_t seed_size, SeaTuna_t *state);

bool seatuna_reseed(const uint8_t *add, size_t add_size, SeaTuna_t *state);

bool seatuna_get_bytes(uint8_t *buf, size_t buf_size, SeaTuna_t *state);


#endif /* SEATUNA_H */
