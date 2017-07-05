
#ifndef PORTABLE_CHACHA20_H
#define PORTABLE_CHACHA20_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "byteswap.h"
#include "static_utils.h"

static inline void cc20_quarter_round(uint32_t *state, uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    state[a] += state[b]; state[d] ^= state[a]; state[d] = rl32(state[d], 16);
    state[c] += state[d]; state[b] ^= state[c]; state[b] = rl32(state[b], 12);
    state[a] += state[b]; state[d] ^= state[a]; state[d] = rl32(state[d],  8);
    state[c] += state[d]; state[b] ^= state[c]; state[b] = rl32(state[b],  7);
}

static inline void cc20_double_round(uint32_t *state)
{
    cc20_quarter_round(state, 0, 4, 8,12);
    cc20_quarter_round(state, 1, 5, 9,13);
    cc20_quarter_round(state, 2, 6,10,14);
    cc20_quarter_round(state, 3, 7,11,15);

    cc20_quarter_round(state, 0, 5,10,15);
    cc20_quarter_round(state, 1, 6,11,12);
    cc20_quarter_round(state, 2, 7, 8,13);
    cc20_quarter_round(state, 3, 4, 9,14);
}

static bool cc20_bytes(uint8_t *key, uint32_t *counter, uint8_t *nonce, uint8_t *out, size_t size)
{
    uint32_t state[16] = {0x61707865, 0x3320646e, 0x79622d32, 0x6b206574};
    memcpy(state + 4, key, 32);
    state[12] = *counter;
    memcpy(state + 13, nonce, 12);

    for (uint32_t i = 0; i < 16; ++i) {
        state[i] = swap_32_le(state[i]);
    }

    uint32_t work[16];
    for (uint32_t i = 0; i < (size / 64); ++i) {

        memcpy(work, state, 64);

        for (uint32_t j = 0; j < 10; ++j) {
            cc20_double_round(work);
        }
        for (uint32_t j = 0; j < 16; ++j) {
            work[j] += state[j];
        }

        state[12] = swap_32_le(++(*counter));

        memcpy(out + i*64, work, 64);
    }

    memcpy(work, state, 64);
    for (uint32_t i = 0; i < 10; ++i) {
        cc20_double_round(work);
    }
    for (uint32_t i = 0; i < 16; ++i) {
        work[i] += state[i];
    }

    ++(*counter);

    memcpy(out + size - (size & 63), work, size & 63);

    return true;
}

#endif /* PORTABLE_CHACHA20_H */
