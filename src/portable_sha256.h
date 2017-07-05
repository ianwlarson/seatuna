
#ifndef PORTABLE_SHA256_H
#define PORTABLE_SHA256_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "byteswap.h"
#include "static_utils.h"

static const uint32_t k256[] = {
     0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
     0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
     0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
     0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
     0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
     0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
     0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
     0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

typedef struct {
    uint32_t state[8];
    uint32_t buff[16];
    uint32_t c;
    uint64_t counter;
} sha256_ctx;

static bool sha256_init(sha256_ctx *ctxt)
{
    if (!ctxt) {
        return false;
    }

    ctxt->state[0] = 0x6a09e667;
    ctxt->state[1] = 0xbb67ae85;
    ctxt->state[2] = 0x3c6ef372;
    ctxt->state[3] = 0xa54ff53a;
    ctxt->state[4] = 0x510e527f;
    ctxt->state[5] = 0x9b05688c;
    ctxt->state[6] = 0x1f83d9ab;
    ctxt->state[7] = 0x5be0cd19;
    ctxt->c = 0;
    ctxt->counter = 0;

    return true;
}

static inline void sha256_process_block(sha256_ctx *ctxt)
{
    ctxt->c = 0;
    ctxt->counter += 64;

    uint32_t w[64];
    for (uint32_t i = 0; i < 16; ++i) {
        w[i] = swap_32_be(ctxt->buff[i]);
    }

    for (uint32_t i = 16; i < 64; ++i) {
        const uint32_t s0 = rr32(w[i - 15], 7) ^ rr32(w[i - 15], 18) ^ (w[i - 15] >> 3);
        const uint32_t s1 = rr32(w[i - 2], 17) ^ rr32(w[i - 2], 19) ^ (w[i - 2] >> 10);
        w[i] = w[i - 16] + s0 + w[i - 7] + s1;
    }

    uint32_t h[8];

    memcpy(h, ctxt->state, 32);

    for (uint32_t i = 0; i < 64; ++i) {
        const uint32_t S1 = rr32(h[4], 6) ^ rr32(h[4], 11) ^ (rr32(h[4], 25));
        const uint32_t ch = (h[4] & h[5]) ^ (~h[4] & h[6]);
        const uint32_t t1 = h[7] + S1 + ch + k256[i] + w[i];
        const uint32_t S0 = rr32(h[0], 2) ^ rr32(h[0], 13) ^ (rr32(h[0], 22));
        const uint32_t maj = (h[0] & h[1]) ^ (h[0] & h[2]) ^ (h[1] & h[2]);
        const uint32_t t2 = S0 + maj;

        h[7] = h[6];
        h[6] = h[5];
        h[5] = h[4];
        h[4] = h[3] + t1;
        h[3] = h[2];
        h[2] = h[1];
        h[1] = h[0];
        h[0] = t1 + t2;
    }

    for (uint32_t i = 0; i < 8; ++i) {
        ctxt->state[i] += h[i];
    }
}

static bool sha256_update(const uint8_t *data, size_t data_size, sha256_ctx *ctxt)
{
    if (!data || !ctxt) {
        return false;
    }

    uint8_t *l = (uint8_t *) ctxt->buff;

    for (uint32_t i = 0; i < data_size; ++i) {
        l[ctxt->c++] = data[i];
        if (ctxt->c == 64) {
            sha256_process_block(ctxt);
        }
    }

    return true;
}

static bool sha256_final(uint8_t *out, sha256_ctx *ctxt)
{
    if (!out || !ctxt) {
        return false;
    }
    const uint64_t c = ctxt->counter + ctxt->c;
    uint8_t *l = (uint8_t *) ctxt->buff;
    l[ctxt->c++] = 0x80;

    while (ctxt->c != 56) {
        if (ctxt->c == 64) {
            sha256_process_block(ctxt);
        }
        l[ctxt->c++] = 0x0;
    }

    const uint64_t bits = swap_64_be(c << 3);
    memcpy(l + 56, &bits, 8);
    sha256_process_block(ctxt);

    for (uint32_t i = 0; i < 8; ++i) {
        ctxt->state[i] = swap_32_be(ctxt->state[i]);
    }

    memcpy(out, ctxt->state, 32);

    sha256_init(ctxt);

    return true;
}


#endif /* PORTABLE_SHA256_H */
