/*
 * Copyright (c) 2016 - 2025 Nordic Semiconductor ASA
 * Copyright (c) since 2020 Oberon microsystems AG
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

//
// This file is based on the Arm PSA Crypto Driver API.

#ifndef CC3XX_PSA_RSA_SIGNATURES_H
#define CC3XX_PSA_RSA_SIGNATURES_H

#include <psa/crypto_driver_common.h>


#ifdef __cplusplus
extern "C" {
#endif


    psa_status_t cc3xx_export_rsa_public_key(
        const psa_key_attributes_t *attributes,
        const uint8_t *key, size_t key_length,
        uint8_t *data, size_t data_size, size_t *data_length);

    psa_status_t cc3xx_rsa_sign_hash(
        const psa_key_attributes_t *attributes,
        const uint8_t *key, size_t key_length,
        psa_algorithm_t alg,
        const uint8_t *hash, size_t hash_length,
        uint8_t *signature, size_t signature_size, size_t *signature_length);

    psa_status_t cc3xx_rsa_verify_hash(
        const psa_key_attributes_t *attributes,
        const uint8_t *key, size_t key_length,
        psa_algorithm_t alg,
        const uint8_t *hash, size_t hash_length,
        const uint8_t *signature, size_t signature_length);


    psa_status_t cc3xx_rsa_encrypt(
        const psa_key_attributes_t *attributes,
        const uint8_t *key_buffer, size_t key_buffer_size,
        psa_algorithm_t alg,
        const uint8_t *input, size_t input_length,
        const uint8_t *salt, size_t salt_length,
        uint8_t *output, size_t output_size, size_t *output_length);

    psa_status_t cc3xx_rsa_decrypt(
        const psa_key_attributes_t *attributes,
        const uint8_t *key_buffer, size_t key_buffer_size,
        psa_algorithm_t alg,
        const uint8_t *input, size_t input_length,
        const uint8_t *salt, size_t salt_length,
        uint8_t *output, size_t output_size, size_t *output_length);


#ifdef __cplusplus
}
#endif

#endif
