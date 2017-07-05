
#ifndef STATIC_UTILS_H
#define STATIC_UTILS_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static inline uint32_t rr32(uint32_t a, unsigned int c)
{
    c &= 0x1f;
    return (a >> c) | (a << (32 - c));
}

static inline uint32_t rl32(uint32_t a, unsigned int c)
{
    c &= 0x1f;
    return (a << c) | (a >> (32 - c));
}

static inline uint32_t rr64(uint32_t a, unsigned int c)
{
    c &= 63;
    return (a >> c) | (a << (64 - c));
}

static inline uint32_t rl64(uint32_t a, unsigned int c)
{
    c &= 64;
    return (a << c) | (a >> (64 - c));
}

static inline uint8_t hex_char_switch(char token[2])
{
    char *l = token;
    uint8_t out = 0x0;
top:
    switch (*l) {
        case 'a':
        case 'A':
            out |= 0xa;
            break;
        case 'b':
        case 'B':
            out |= 0xb;
            break;
        case 'c':
        case 'C':
            out |= 0xc;
            break;
        case 'd':
        case 'D':
            out |= 0xd;
            break;
        case 'e':
        case 'E':
            out |= 0xe;
            break;
        case 'f':
        case 'F':
            out |= 0xf;
            break;
        case '0':
            break;
        case '1':
            out |= 0x1;
            break;
        case '2':
            out |= 0x2;
            break;
        case '3':
            out |= 0x3;
            break;
        case '4':
            out |= 0x4;
            break;
        case '5':
            out |= 0x5;
            break;
        case '6':
            out |= 0x6;
            break;
        case '7':
            out |= 0x7;
            break;
        case '8':
            out |= 0x8;
            break;
        case '9':
            out |= 0x9;
            break;
    }
    if (l == token + 1) {
        return out;
    }

    out <<= 4;
    l += 1;
    goto top;
}

#ifndef strnlen
static inline size_t strnlen(const char *string, size_t maxlen)
{
    size_t counter = 0;
    while (counter < maxlen && string[counter] != '\0') {
        ++counter;
    }

    return counter;
}
#endif

#define MAX_HEX_LEN 4096

static inline bool hex_to_buf(char *hex_string, uint8_t *buffer)
{
    const size_t slen = strnlen(hex_string, MAX_HEX_LEN);
    if (!hex_string || slen & 0x1 || !buffer) {
        return false;
    }

    const size_t blen = slen / 2;
    size_t j = 0;
    for (size_t i = 0; i < blen; ++i, j+=2) {
        buffer[i] = hex_char_switch(hex_string + j);
    }

    return true;
}

#endif /* STATIC_UTILS_H */
