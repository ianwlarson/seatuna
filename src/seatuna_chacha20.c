
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include "seatuna_chacha20.h"

#include "byteswap.h"
#include "static_utils.h"

static inline void chacha20_rounds(uint32_t state[16])
{
	// This is done to prevent excessive reading/writing to/from an array (in this case reading/writing to stack frame.)
	uint32_t a0, a1, a2, a3, b0, b1, b2, b3, c0, c1, c2, c3, d0, d1, d2, d3, tmp;
	a0 = state[0];
	a1 = state[1];
	a2 = state[2];
	a3 = state[3];
	b0 = state[4];
	b1 = state[5];
	b2 = state[6];
	b3 = state[7];
	c0 = state[8];
	c1 = state[9];
	c2 = state[10];
	c3 = state[11];
	d0 = state[12];
	d1 = state[13];
	d2 = state[14];
	d3 = state[15];
	
	for (int i = 0; i < 10; ++i) {
		a0 += b0; a1 += b1; a2 += b2; a3 += b3;
		d0 ^= a0; d1 ^= a1; d2 ^= a2; d3 ^= a3;
		d0 = rl32(d0, 16); d1 = rl32(d1, 16); d2 = rl32(d2, 16); d3 = rl32(d3, 16);
		
		c0 += d0; c1 += d1; c2 += d2; c3 += d3;
		b0 ^= c0; b1 ^= c1; b2 ^= c2; b3 ^= c3;
		b0 = rl32(b0, 12); b1 = rl32(b1, 12); b2 = rl32(b2, 12); b3 = rl32(b3, 12);
		
		a0 += b0; a1 += b1; a2 += b2; a3 += b3;
		d0 ^= a0; d1 ^= a1; d2 ^= a2; d3 ^= a3;
		d0 = rl32(d0, 8); d1 = rl32(d1, 8); d2 = rl32(d2, 8); d3 = rl32(d3, 8);
		
		c0 += d0; c1 += d1; c2 += d2; c3 += d3;
		b0 ^= c0; b1 ^= c1; b2 ^= c2; b3 ^= c3;
		b0 = rl32(b0, 7); b1 = rl32(b1, 7); b2 = rl32(b2, 7); b3 = rl32(b3, 7);
		
		tmp = b0; b0 = b1; b1 = b2; b2 = b3; b3 = tmp; // | b0 | b1 | b2 | b3 | -> | b1 | b2 | b3 | b0 |
		tmp = c0; c0 = c2; c2 = tmp; tmp = c1; c1 = c3; c3 = tmp; // | c0 | c1 | c2 | c3 | -> | c2 | c3 | c0 | c1 |
		tmp = d3; d3 = d2; d2 = d1; d1 = d0; d0 = tmp; // | d0 | d1 | d2 | d3 | -> | d3 | d0 | d1 | d2 |
		
		a0 += b0; a1 += b1; a2 += b2; a3 += b3;
		d0 ^= a0; d1 ^= a1; d2 ^= a2; d3 ^= a3;
		d0 = rl32(d0, 16); d1 = rl32(d1, 16); d2 = rl32(d2, 16); d3 = rl32(d3, 16);
		
		c0 += d0; c1 += d1; c2 += d2; c3 += d3;
		b0 ^= c0; b1 ^= c1; b2 ^= c2; b3 ^= c3;
		b0 = rl32(b0, 12); b1 = rl32(b1, 12); b2 = rl32(b2, 12); b3 = rl32(b3, 12);
		
		a0 += b0; a1 += b1; a2 += b2; a3 += b3;
		d0 ^= a0; d1 ^= a1; d2 ^= a2; d3 ^= a3;
		d0 = rl32(d0, 8); d1 = rl32(d1, 8); d2 = rl32(d2, 8); d3 = rl32(d3, 8);
		
		c0 += d0; c1 += d1; c2 += d2; c3 += d3;
		b0 ^= c0; b1 ^= c1; b2 ^= c2; b3 ^= c3;
		b0 = rl32(b0, 7); b1 = rl32(b1, 7); b2 = rl32(b2, 7); b3 = rl32(b3, 7);
		
		tmp = b3; b3 = b2; b2 = b1; b1 = b0; b0 = tmp; // | b0 | b1 | b2 | b3 | -> | b3 | b0 | b1 | b2 |
		tmp = c0; c0 = c2; c2 = tmp; tmp = c1; c1 = c3; c3 = tmp; // | c0 | c1 | c2 | c3 | -> | c2 | c3 | c0 | c1 |
		tmp = d0; d0 = d1; d1 = d2; d2 = d3; d3 = tmp; // | d0 | d1 | d2 | d3 | -> | d1 | d2 | d3 | d0 |
	}
	
	state[0] += a0;
	state[1] += a1;
	state[2] += a2;
	state[3] += a3;
	state[4] += b0;
	state[5] += b1;
	state[6] += b2;
	state[7] += b3;
	state[8] += c0;
	state[9] += c1;
	state[10] += c2;
	state[11] += c3;
	state[12] += d0;
	state[13] += d1;
	state[14] += d2;
	state[15] += d3;
}

void seatuna_chacha20_bytes(uint8_t *key, uint32_t *counter, uint8_t *nonce, size_t size, uint8_t *out)
{
	uint32_t state[16] = {0x61707865, 0x3320646e, 0x79622d32, 0x6b206574};
	uint32_t l_counter = *counter;
	memcpy(state + 4, key, 32);
	state[12] = l_counter;
	memcpy(state + 13, nonce, 12);

	for (int i = 0; i < 16; ++i) {
		state[i] = swap_32_le(state[i]);
	}

	uint32_t work[16];
	while (size > 64) {

		memcpy(work, state, 64);

		chacha20_rounds(work);

		state[12] = swap_32_le(++l_counter);

		memcpy(out, work, 64);
		out += 64;
		size -= 64;
	}

	memcpy(work, state, 64);

	chacha20_rounds(work);
	
	*counter = l_counter + 1;

	memcpy(out, work, size);
}
