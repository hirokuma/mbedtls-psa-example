#include <stdio.h>

#include "psa/crypto.h"

void test1(void);
void test2(void);
void test3(void);

static void print_version(void)
{
    printf("PSA crypto version: %d.%d\n", PSA_CRYPTO_API_VERSION_MAJOR, PSA_CRYPTO_API_VERSION_MINOR);
}

void dump(const uint8_t *p, size_t sz)
{
    for (int i = 0; i < sz; i++) {
        printf("%02x", p[i]);
    }
    printf("\n");
}

int main(void)
{
    print_version();
    test1();
    test2();
    test3();

    printf("done.\n");

    return 0;
}
