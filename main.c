#include <stdio.h>

#include "psa/crypto.h"

void test1(void);

static void print_version(void)
{
    printf("PSA crypto version: %d.%d\n", PSA_CRYPTO_API_VERSION_MAJOR, PSA_CRYPTO_API_VERSION_MINOR);
}

int main(void)
{
    print_version();
    test1();

    printf("done.\n");

    return 0;
}
