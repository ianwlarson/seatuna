
#include "seatuna.h"
#include "portable_sha256.h"
#include "portable_chacha20.h"

static void u128_add_u32(uint64_t *c, uint32_t a)
{
    if (c[0] + a < c[0]) {
        c[1]++;
    }
    c[0] += a;
}

bool seatuna_init(SeaTuna_t *state)
{
    if (!state)
        return false;

    state->counter[0] = 0;
    state->counter[1] = 0;

    return true;
}

bool seatuna_seed(const uint8_t *seed, size_t seed_size, SeaTuna_t *state)
{
    if (!seed || !state || !seed_size)
        return false;

    sha256_ctx ctx;
    sha256_init(&ctx);
    sha256_update(seed, seed_size, &ctx);
    sha256_final((uint8_t *) state->key, &ctx);

    state->counter[0] = 1;
    state->counter[1] = 0;
	
	return true;
}

bool seatuna_reseed(const uint8_t *add, size_t add_size, SeaTuna_t *state)
{
    if (!add || !state || !add_size) {
        return false;
    }

    sha256_ctx ctx;
    sha256_init(&ctx);
    sha256_update((uint8_t *) state->key, 32, &ctx);
    sha256_update(add, add_size, &ctx);
    sha256_final((uint8_t *) state->key, &ctx);

    state->counter[0] = 1;
    state->counter[1] = 0;

    return true;
}

bool seatuna_get_bytes(uint8_t *buf, size_t buf_size, SeaTuna_t *state)
{
    if (buf_size > (1 << 20) || !buf || !state || (state->counter[0] == 0 && state->counter[1] == 0)) {
        return false;
    }

    uint8_t old_nonce[12];
    uint8_t old_key[32];
    memcpy(old_nonce, state->nonce, 12);
    memcpy(old_key, state->key, 32);

    uint32_t counter = 0;
    cc20_bytes(old_key, &counter, old_nonce, buf, buf_size);
    cc20_bytes(old_key, &counter, old_nonce, (uint8_t *) state->key, 32);
    cc20_bytes(old_key, &counter, old_nonce, (uint8_t *) state->nonce, 12);

    u128_add_u32(state->counter, counter);

    return false;
}
