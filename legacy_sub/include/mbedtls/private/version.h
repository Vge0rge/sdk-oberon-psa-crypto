#ifndef TF_PSA_CRYPTO_MBEDTLS_PRIVATE_VERSION_H

#include <string.h>

/* These come from the mbedtls build_info which we don't use */

/**
 * The version number x.y.z is split into three parts.
 * Major, Minor, Patchlevel
 */
#define MBEDTLS_VERSION_MAJOR  4
#define MBEDTLS_VERSION_MINOR  1
#define MBEDTLS_VERSION_PATCH  0

/**
 * The single version number has the following structure:
 *    MMNNPP00
 *    Major version | Minor version | Patch version
 */
#define MBEDTLS_VERSION_NUMBER         0x04010000
#define MBEDTLS_VERSION_STRING         "4.1.0"
#define MBEDTLS_VERSION_STRING_FULL    "Mbed TLS 4.1.0"

inline unsigned int mbedtls_version_get_number(void)
{
    return MBEDTLS_VERSION_NUMBER;
}

inline const char *mbedtls_version_get_string(void)
{
    return MBEDTLS_VERSION_STRING;
}

inline const char *mbedtls_version_get_string_full(void)
{
    return MBEDTLS_VERSION_STRING_FULL;
}

#endif /* TF_PSA_CRYPTO_MBEDTLS_PRIVATE_VERSION_H */