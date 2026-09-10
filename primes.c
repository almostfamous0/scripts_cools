#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

static bool is_prime(long long n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    /* All primes > 3 are of the form 6k ± 1.
       Step by 6, check both i and i+2 each iteration. */
    long long lim = (long long)sqrt((double)n);
    for (long long i = 5; i <= lim; i += 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;

    return true;
}

int main(int argc, char *argv[]) {
    long long limit = 10000000;
    if (argc > 1) limit = atoll(argv[1]);

    printf("Primes up to %lld:\n", limit);
    long long count = 0;
    for (long long n = 2; n <= limit; n++) {
        if (is_prime(n)) {
            printf("%lld ", n);
            count++;
        }
    }
    printf("\n\nTotal: %lld primes\n", count);
    return 0;
}
