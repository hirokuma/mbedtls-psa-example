#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "psa/crypto.h"

#include "mbedtls/ctr_drbg.h"
#include "mbedtls/md.h"
#include "mbedtls/sha256.h"

extern int mboom;
extern void dump(const uint8_t *p, size_t sz);

void test2(void)
{
    int rc;
    psa_hash_operation_t psa256;

    printf("\n%s start.\n", __func__);

    rc = psa_crypto_init();
    if (rc != PSA_SUCCESS) {
        printf("Failed to initialize PSA Crypto\n");
        return;
    }
    rc = psa_hash_setup(&psa256, PSA_ALG_SHA_256);
    if (rc != PSA_SUCCESS) {
        printf("fail: psa_hash_setup: %d\n", rc);
        return;
    }

    uint8_t hash_mbed[32];
    uint8_t hash_psa[32];

    // SHA256
    // $ echo -n "Hello, World!" | sha256sum
    // dffd6021bb2bd5b0af676290809ec3a53191dd81c7f70a4b28688a362182986f  -
    const uint8_t SRC[] = "Hello, World!";
    const uint8_t SRC_SHA256[] = {
        0xdf, 0xfd, 0x60, 0x21, 0xbb, 0x2b, 0xd5, 0xb0,
        0xaf, 0x67, 0x62, 0x90, 0x80, 0x9e, 0xc3, 0xa5,
        0x31, 0x91, 0xdd, 0x81, 0xc7, 0xf7, 0x0a, 0x4b,
        0x28, 0x68, 0x8a, 0x36, 0x21, 0x82, 0x98, 0x6f,
    };

    rc = mbedtls_sha256(SRC, sizeof(SRC) - 1, hash_mbed, 0);
    if (rc != 0) {
        printf("error: mbedtls_sha256: %d\n", rc);
        return;
    }
    if (memcmp(hash_mbed, SRC_SHA256, sizeof(SRC_SHA256)) != 0) {
        printf("error: sha256 result\n");
;    }

    size_t hash_psa_sz;
    rc = psa_hash_compute(PSA_ALG_SHA_256,
        SRC, sizeof(SRC) - 1,
        hash_psa, sizeof(hash_psa),
        &hash_psa_sz);
    if (rc != PSA_SUCCESS) {
        printf("error: psa_hash_compute: %d\n", rc);
        return;
    }
    if (hash_psa_sz != sizeof(hash_psa)) {
        printf("error: size length\n");
        return;
    }
    if (memcmp(hash_psa, SRC_SHA256, sizeof(SRC_SHA256)) != 0) {
        printf("error: compare\n");
        dump(hash_psa, sizeof(hash_psa));
        return;
    }

    mbedtls_psa_crypto_free();

    printf("...... done.\n");
}
