/** Copyright 2016 Ian W. Larson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
