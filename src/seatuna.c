
#include "seatuna.h"
#include "portable_sha256.h"
#include "seatuna_chacha20.h"

bool seatuna_init(SeaTuna_t *state, int num_pools)
{
	if (state == NULL) {
		return false;
	}
	
	state->pools = malloc(sizeof(*state->pools) * num_pools);
	state->pcount = num_pools;
	
	state->seeded = false;
	
	return true;
}

bool seatuna_seed(const uint8_t *seed, size_t seed_size, SeaTuna_t *state)
{
    if (!seed || !state || !seed_size) {
        return false;
	}

	uint8_t seedhash[32];
	uint32_t counter = 0;
	uint8_t nonce[12] = {0};
	
    sha256_ctx ctx;
    sha256_init(&ctx);
    sha256_update(seed, seed_size, &ctx);
    sha256_final(seedhash, &ctx);
	
	seatuna_chacha20_bytes(seedhash, &counter, nonce, sizeof(*state->pools * state->pcount), (uint8_t *) state->pools);
	
	state->seeded = true;
	
	return true;
}

bool seatuna_reseed(const uint8_t *add, size_t add_size, SeaTuna_t *state)
{
    if (add == NULL || state == NULL || add_size == 0) {
        return false;
    }

    sha256_ctx ctx;
    sha256_init(&ctx);
    sha256_update((uint8_t *) state->key, 32, &ctx);
    sha256_update(add, add_size, &ctx);
    sha256_final((uint8_t *) state->key, &ctx);

    return true;
}

bool seatuna_get_bytes(uint8_t *buf, size_t buf_size, SeaTuna_t *state)
{
    if (buf_size > (1 << 20) || !buf || !state || !state->seeded) {
        return false;
    }

    return false;
}
