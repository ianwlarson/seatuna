
#include <immintrin.h>
#include <stdio.h>

int main(void) {

	__m256i n = _mm256_set_epi32(0, 1, 2, 3, 4, 5, 6, 7);

	__m256 m = _mm256_cvtepi32_ps(n);


	printf("%f\t%f\t%f\t%f\n", m[0], m[1], m[2], m[3]);

	return 0;
}
