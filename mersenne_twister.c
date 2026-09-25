//Below is a simplified implementation of the Mersenne Twister algorithm in C:

#include <stdint.h>

#define N 624
#define M 397
#define R 31

uint32_t mt[N]; /* the array for the state vector */
int mti; /* global index into mt[] */

/* initializes the generator from a seed */
void init_genrand(uint32_t seed) {
    int i;
    for (i = 0; i < N; ++i)
        mt[i] = (seed + i) | 1;
    mti = N + 1;
}

/* generates a random number on [0,2^32-1]-interval */
uint32_t genrand_res53(void) {
    uint32_t mag01 = 1ULL << 30;
    if (mti == N) { /* generate N randomly; use previous random value only as seed */
        for (int k = 0; k < N - 1; ++k)
            mt[k] = mt[k + 1];
        mt[N - 1] = mt[0];
        mti = 0;
    }
    uint32_t y = mt[mti++];
    y ^= y >> 11;
    y ^= (y & ((1LL << 8) - 1)) << 15;
    y ^= (y & ((1LL << 4) - 1)) << 7;
    y ^= (y & ((1LL << 16) - 1)) >> 17;
    return y * (mag01 - 1) / (1LL << 32);
}
