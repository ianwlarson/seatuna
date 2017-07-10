
#ifndef SEATUNA_CHACHA20_H
#define SEATUNA_CHACHA20_H

#include <stdint.h>
#include <stdlib.h>

void seatuna_chacha20_bytes(uint8_t *key, uint32_t *counter, uint8_t *nonce, size_t req_len, uint8_t *out);
#endif
