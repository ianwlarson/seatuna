
#ifndef BYTESWAP_H
#define BYTESWAP_H

#include <stdlib.h>

#if IS_BIG_ENDIAN

#define swap_16_be(x) (x)
#define swap_32_be(x) (x)
#define swap_64_be(x) (x)

#define swap_16_le(x) _byteswap_ushort(x)
#define swap_32_le(x) _byteswap_ulong(x)
#define swap_64_le(x) _byteswap_uint64(x)

#else

#define swap_16_be(x) _byteswap_ushort(x)
#define swap_32_be(x) _byteswap_ulong(x)
#define swap_64_be(x) _byteswap_uint64(x)

#define swap_16_le(x) (x)
#define swap_32_le(x) (x)
#define swap_64_le(x) (x)

#endif /* IS_BIG_ENDIAN */

#endif /* BYTESWAP_H */
