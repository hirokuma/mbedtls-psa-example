#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "psa/crypto.h"

#include "mbedtls/ctr_drbg.h"
#include "mbedtls/md.h"
#include "mbedtls/sha256.h"

extern void dump(const uint8_t *p, size_t sz);

void test3(void)
{
    int rc;

    printf("\n%s start.\n", __func__);

    uint8_t hash_mbed[64];
    uint8_t hash_psa[64];

    // SHA512
    const uint8_t SRC[] = "Hello, World!";
    const uint8_t SRC_SHA512[] = {
        0x37, 0x4d, 0x79, 0x4a, 0x95, 0xcd, 0xcf, 0xd8,
        0xb3, 0x59, 0x93, 0x18, 0x5f, 0xef, 0x9b, 0xa3,
        0x68, 0xf1, 0x60, 0xd8, 0xda, 0xf4, 0x32, 0xd0,
        0x8b, 0xa9, 0xf1, 0xed, 0x1e, 0x5a, 0xbe, 0x6c,
        0xc6, 0x92, 0x91, 0xe0, 0xfa, 0x2f, 0xe0, 0x00,
        0x6a, 0x52, 0x57, 0x0e, 0xf1, 0x8c, 0x19, 0xde,
        0xf4, 0xe6, 0x17, 0xc3, 0x3c, 0xe5, 0x2e, 0xf0,
        0xa6, 0xe5, 0xfb, 0xe3, 0x18, 0xcb, 0x03, 0x87,
    };

    //
    // Mbed TLS
    //
    mbedtls_sha512_context ctx;

    mbedtls_sha512_init(&ctx);
    rc = mbedtls_sha512_starts(&ctx, 0);
    if (rc != 0) {
        printf("error: mbedtls_sha512_starts: %d\n", rc);
        return;
    }
    rc = mbedtls_sha512_update(&ctx, SRC, sizeof(SRC) - 1);
    if (rc != 0) {
        printf("error: mbedtls_sha512_update: %d\n", rc);
        return;
    }
    rc = mbedtls_sha512_finish(&ctx, hash_mbed);
    if (rc != 0) {
        printf("error: mbedtls_sha512_finish: %d\n", rc);
        return;
    }
    mbedtls_sha512_free(&ctx);

    if (memcmp(hash_mbed, SRC_SHA512, sizeof(SRC_SHA512)) != 0) {
        printf("error: Mbed TLS sha512 result\n");
    }

    //
    // PSA
    //
    psa_hash_operation_t psa512 = PSA_HASH_OPERATION_INIT;
    size_t hash_psa_sz;

    rc = psa_crypto_init();
    if (rc != PSA_SUCCESS) {
        printf("Failed to initialize PSA Crypto\n");
        return;
    }
    rc = psa_hash_setup(&psa512, PSA_ALG_SHA_512);
    if (rc != PSA_SUCCESS) {
        printf("fail: psa_hash_setup: %d\n", rc);
        return;
    }
    rc = psa_hash_update(&psa512,
        SRC, sizeof(SRC) - 1);
    if (rc != PSA_SUCCESS) {
        printf("error: psa_hash_update: %d\n", rc);
        return;
    }
    rc = psa_hash_finish(&psa512,
        hash_psa, sizeof(hash_psa),
        &hash_psa_sz);
    if (rc != PSA_SUCCESS) {
        printf("error: psa_hash_finish: %d\n", rc);
        return;
    }
    mbedtls_psa_crypto_free();

    if (hash_psa_sz != sizeof(SRC_SHA512)) {
        printf("error: output length\n");
        return;
    }
    if (memcmp(hash_psa, SRC_SHA512, sizeof(SRC_SHA512)) != 0) {
        printf("error: PSA sha512 result\n");
        dump(hash_psa, sizeof(hash_psa));
        return;
    }


    printf("...... done.\n");
}
