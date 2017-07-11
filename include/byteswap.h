
#ifndef BYTESWAP_H
#define BYTESWAP_H

#include <stdlib.h>

#include "seatuna_endian.h"

#if SEATUNA_BIG_ENDIAN

# define swap_16_be(x) (x)
# define swap_32_be(x) (x)
# define swap_64_be(x) (x)

# define swap_16_le(x) __builtin_bswap16(x)
# define swap_32_le(x) __builtin_bswap32(x)
# define swap_64_le(x) __builtin_bswap64(x)

#else

# define swap_16_be(x) __builtin_bswap16(x)
# define swap_32_be(x) __builtin_bswap32(x)
# define swap_64_be(x) __builtin_bswap64(x)

# define swap_16_le(x) (x)
# define swap_32_le(x) (x)
# define swap_64_le(x) (x)

#endif /* SEATUNA_BIG_ENDIAN */

#endif /* BYTESWAP_H */
