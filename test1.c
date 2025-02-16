#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "psa/crypto.h"

void test1(void)
{
    printf("\n%s start.\n", __func__);

    int rc = psa_crypto_init();
    if (rc != PSA_SUCCESS) {
        printf("Failed to initialize PSA Crypto\n");
        return;
    }
    mbedtls_psa_crypto_free();

    printf("...... done.\n");
}
