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

#ifndef BYTESWAP_H
#define BYTESWAP_H

#include <stdlib.h>

#if IS_BIG_ENDIAN

#define swap_16_be(x) (x)
#define swap_32_be(x) (x)
#define swap_64_be(x) (x)

#define swap_16_le(x) __builtin_bswap16(x)
#define swap_32_le(x) __builtin_bswap32(x)
#define swap_64_le(x) __builtin_bswap64(x)

#else

#define swap_16_be(x) __builtin_bswap16(x)
#define swap_32_be(x) __builtin_bswap32(x)
#define swap_64_be(x) __builtin_bswap64(x)

#define swap_16_le(x) (x)
#define swap_32_le(x) (x)
#define swap_64_le(x) (x)

#endif /* IS_BIG_ENDIAN */

#endif /* BYTESWAP_H */
