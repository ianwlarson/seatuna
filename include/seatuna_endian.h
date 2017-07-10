
#ifndef SEATUNA_ENDIAN_H
#define SEATUNA_ENDIAN_H


// TODO Make sure this is correct.
#if defined(__sparc__) || defined(__powerpc__) || \
    defined(__ppc__) || defined(__hppa) || \
    defined(__mips__) || defined(__s390__)
# define SEATUNA_BIG_ENDIAN 1
#else
# define SEATUNA_BIG_ENDIAN 0
#endif

#endif /* SEATUNA_ENDIAN_H */
