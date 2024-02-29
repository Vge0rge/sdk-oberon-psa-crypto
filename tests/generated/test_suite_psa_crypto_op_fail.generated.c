#line 2 "suites/main_test.function"
/*
 * *** THIS FILE HAS BEEN MACHINE GENERATED ***
 *
 * This file has been machine generated using the script:
 * generate_test_code.py
 *
 * Test file      : ./test_suite_psa_crypto_op_fail.generated.c
 *
 * The following files were used to create this file.
 *
 *      Main code file      : tests/suites/main_test.function
 *      Platform code file  : tests/suites/host_test.function
 *      Helper file         : tests/suites/helpers.function
 *      Test suite file     : tests/suites/test_suite_psa_crypto_op_fail.function
 *      Test suite data     : tests/suites/test_suite_psa_crypto_op_fail.generated.data
 *
 */

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#if !defined(_POSIX_C_SOURCE)
#define _POSIX_C_SOURCE 200112L // for fileno() from <stdio.h>
#endif
#endif

#include "mbedtls/build_info.h"

/* Test code may use deprecated identifiers only if the preprocessor symbol
 * MBEDTLS_TEST_DEPRECATED is defined. When building tests, set
 * MBEDTLS_TEST_DEPRECATED explicitly if MBEDTLS_DEPRECATED_WARNING is
 * enabled but the corresponding warnings are not treated as errors.
 */
#if !defined(MBEDTLS_DEPRECATED_REMOVED) && !defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_TEST_DEPRECATED
#endif

/*----------------------------------------------------------------------------*/
/* Common helper code */

#line 2 "suites/helpers.function"
/*----------------------------------------------------------------------------*/
/* Headers */

#include <test/arguments.h>
#include <test/helpers.h>
#include <test/macros.h>
#include <test/random.h>
#include <test/bignum_helpers.h>
#include <test/psa_crypto_helpers.h>

#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#if defined(MBEDTLS_ERROR_C)
#include "mbedtls/error.h"
#endif
#include "mbedtls/platform.h"

#if defined(MBEDTLS_MEMORY_BUFFER_ALLOC_C)
#include "mbedtls/memory_buffer_alloc.h"
#endif

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#include <unistd.h>
#endif

/*----------------------------------------------------------------------------*/
/* Status and error constants */

#define DEPENDENCY_SUPPORTED            0   /* Dependency supported by build */
#define KEY_VALUE_MAPPING_FOUND         0   /* Integer expression found */
#define DISPATCH_TEST_SUCCESS           0   /* Test dispatch successful */

#define KEY_VALUE_MAPPING_NOT_FOUND     -1  /* Integer expression not found */
#define DEPENDENCY_NOT_SUPPORTED        -2  /* Dependency not supported */
#define DISPATCH_TEST_FN_NOT_FOUND      -3  /* Test function not found */
#define DISPATCH_INVALID_TEST_DATA      -4  /* Invalid test parameter type.
                                               Only int, string, binary data
                                               and integer expressions are
                                               allowed */
#define DISPATCH_UNSUPPORTED_SUITE      -5  /* Test suite not supported by the
                                               build */

/*----------------------------------------------------------------------------*/
/* Global variables */

/*----------------------------------------------------------------------------*/
/* Helper flags for complex dependencies */

/* Indicates whether we expect mbedtls_entropy_init
 * to initialize some strong entropy source. */
#if !defined(MBEDTLS_NO_DEFAULT_ENTROPY_SOURCES) && \
    (!defined(MBEDTLS_NO_PLATFORM_ENTROPY) ||      \
    defined(MBEDTLS_ENTROPY_HARDWARE_ALT) ||    \
    defined(ENTROPY_NV_SEED))
#define ENTROPY_HAVE_STRONG
#endif


/*----------------------------------------------------------------------------*/
/* Helper Functions */

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
static int redirect_output(FILE *out_stream, const char *path)
{
    int out_fd, dup_fd;
    FILE *path_stream;

    out_fd = fileno(out_stream);
    dup_fd = dup(out_fd);

    if (dup_fd == -1) {
        return -1;
    }

    path_stream = fopen(path, "w");
    if (path_stream == NULL) {
        close(dup_fd);
        return -1;
    }

    fflush(out_stream);
    if (dup2(fileno(path_stream), out_fd) == -1) {
        close(dup_fd);
        fclose(path_stream);
        return -1;
    }

    fclose(path_stream);
    return dup_fd;
}

static int restore_output(FILE *out_stream, int dup_fd)
{
    int out_fd = fileno(out_stream);

    fflush(out_stream);
    if (dup2(dup_fd, out_fd) == -1) {
        close(out_fd);
        close(dup_fd);
        return -1;
    }

    close(dup_fd);
    return 0;
}
#endif /* __unix__ || __APPLE__ __MACH__ */


#line 43 "suites/main_test.function"


/*----------------------------------------------------------------------------*/
/* Test Suite Code */


#define TEST_SUITE_ACTIVE

#if defined(MBEDTLS_PSA_CRYPTO_C)
#line 2 "tests/suites/test_suite_psa_crypto_op_fail.function"

#include "psa/crypto.h"
#include "test/psa_crypto_helpers.h"

static int test_equal_status(const char *test,
                             int line_no, const char *filename,
                             psa_status_t value1,
                             psa_status_t value2)
{
    if ((value1 == PSA_ERROR_INVALID_ARGUMENT &&
         value2 == PSA_ERROR_NOT_SUPPORTED) ||
        (value1 == PSA_ERROR_NOT_SUPPORTED &&
         value2 == PSA_ERROR_INVALID_ARGUMENT)) {
        return 1;
    }
    return mbedtls_test_equal(test, line_no, filename, value1, value2);
}

/** Like #TEST_EQUAL, but expects #psa_status_t values and treats
 * #PSA_ERROR_INVALID_ARGUMENT and #PSA_ERROR_NOT_SUPPORTED as
 * interchangeable.
 *
 * This test suite currently allows NOT_SUPPORTED and INVALID_ARGUMENT
 * to be interchangeable in places where the library's behavior does not
 * match the strict expectations of the test case generator. In the long
 * run, it would be better to clarify the expectations and reconcile the
 * library and the test case generator.
 */
#define TEST_STATUS(expr1, expr2)                                     \
    do {                                                                \
        if (!test_equal_status( #expr1 " == " #expr2, __LINE__, __FILE__, \
                                expr1, expr2))                       \
        goto exit;                                                  \
    } while (0)

#line 45 "tests/suites/test_suite_psa_crypto_op_fail.function"
void test_hash_fail(int alg_arg, int expected_status_arg)
{
    psa_status_t expected_status = expected_status_arg;
    psa_algorithm_t alg = alg_arg;
    psa_hash_operation_t operation = PSA_HASH_OPERATION_INIT;
    uint8_t input[1] = { 'A' };
    uint8_t output[PSA_HASH_MAX_SIZE] = { 0 };
    size_t length = SIZE_MAX;

    PSA_INIT();

    TEST_EQUAL(expected_status,
               psa_hash_setup(&operation, alg));
    TEST_EQUAL(expected_status,
               psa_hash_compute(alg, input, sizeof(input),
                                output, sizeof(output), &length));
    TEST_EQUAL(expected_status,
               psa_hash_compare(alg, input, sizeof(input),
                                output, sizeof(output)));

exit:
    psa_hash_abort(&operation);
    PSA_DONE();
}

void test_hash_fail_wrapper( void ** params )
{

    test_hash_fail( ((mbedtls_test_argument_t *) params[0])->sint, ((mbedtls_test_argument_t *) params[1])->sint );
}
#line 72 "tests/suites/test_suite_psa_crypto_op_fail.function"
void test_mac_fail(int key_type_arg, data_t *key_data,
              int alg_arg, int expected_status_arg)
{
    psa_status_t expected_status = expected_status_arg;
    psa_key_type_t key_type = key_type_arg;
    psa_algorithm_t alg = alg_arg;
    psa_mac_operation_t operation = PSA_MAC_OPERATION_INIT;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    mbedtls_svc_key_id_t key_id = MBEDTLS_SVC_KEY_ID_INIT;
    uint8_t input[1] = { 'A' };
    uint8_t output[PSA_MAC_MAX_SIZE] = { 0 };
    size_t length = SIZE_MAX;

    PSA_INIT();

    psa_set_key_type(&attributes, key_type);
    psa_set_key_usage_flags(&attributes,
                            PSA_KEY_USAGE_SIGN_HASH |
                            PSA_KEY_USAGE_VERIFY_HASH);
    psa_set_key_algorithm(&attributes, alg);
    PSA_ASSERT(psa_import_key(&attributes,
                              key_data->x, key_data->len,
                              &key_id));

    TEST_STATUS(expected_status,
                psa_mac_sign_setup(&operation, key_id, alg));
    TEST_STATUS(expected_status,
                psa_mac_verify_setup(&operation, key_id, alg));
    TEST_STATUS(expected_status,
                psa_mac_compute(key_id, alg,
                                input, sizeof(input),
                                output, sizeof(output), &length));
    TEST_STATUS(expected_status,
                psa_mac_verify(key_id, alg,
                               input, sizeof(input),
                               output, sizeof(output)));

exit:
    psa_mac_abort(&operation);
    psa_destroy_key(key_id);
    psa_reset_key_attributes(&attributes);
    PSA_DONE();
}

void test_mac_fail_wrapper( void ** params )
{
    data_t data1 = {(uint8_t *) params[1], ((mbedtls_test_argument_t *) params[2])->len};

    test_mac_fail( ((mbedtls_test_argument_t *) params[0])->sint, &data1, ((mbedtls_test_argument_t *) params[3])->sint, ((mbedtls_test_argument_t *) params[4])->sint );
}
#line 118 "tests/suites/test_suite_psa_crypto_op_fail.function"
void test_cipher_fail(int key_type_arg, data_t *key_data,
                 int alg_arg, int expected_status_arg)
{
    psa_status_t expected_status = expected_status_arg;
    psa_key_type_t key_type = key_type_arg;
    psa_algorithm_t alg = alg_arg;
    psa_cipher_operation_t operation = PSA_CIPHER_OPERATION_INIT;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    mbedtls_svc_key_id_t key_id = MBEDTLS_SVC_KEY_ID_INIT;
    uint8_t input[1] = { 'A' };
    uint8_t output[64] = { 0 };
    size_t length = SIZE_MAX;

    PSA_INIT();

    psa_set_key_type(&attributes, key_type);
    psa_set_key_usage_flags(&attributes,
                            PSA_KEY_USAGE_ENCRYPT |
                            PSA_KEY_USAGE_DECRYPT);
    psa_set_key_algorithm(&attributes, alg);
    PSA_ASSERT(psa_import_key(&attributes,
                              key_data->x, key_data->len,
                              &key_id));

    TEST_STATUS(expected_status,
                psa_cipher_encrypt_setup(&operation, key_id, alg));
    TEST_STATUS(expected_status,
                psa_cipher_decrypt_setup(&operation, key_id, alg));
    TEST_STATUS(expected_status,
                psa_cipher_encrypt(key_id, alg,
                                   input, sizeof(input),
                                   output, sizeof(output), &length));
    TEST_STATUS(expected_status,
                psa_cipher_decrypt(key_id, alg,
                                   input, sizeof(input),
                                   output, sizeof(output), &length));

exit:
    psa_cipher_abort(&operation);
    psa_destroy_key(key_id);
    psa_reset_key_attributes(&attributes);
    PSA_DONE();
}

void test_cipher_fail_wrapper( void ** params )
{
    data_t data1 = {(uint8_t *) params[1], ((mbedtls_test_argument_t *) params[2])->len};

    test_cipher_fail( ((mbedtls_test_argument_t *) params[0])->sint, &data1, ((mbedtls_test_argument_t *) params[3])->sint, ((mbedtls_test_argument_t *) params[4])->sint );
}
#line 164 "tests/suites/test_suite_psa_crypto_op_fail.function"
void test_aead_fail(int key_type_arg, data_t *key_data,
               int alg_arg, int expected_status_arg)
{
    psa_status_t expected_status = expected_status_arg;
    psa_key_type_t key_type = key_type_arg;
    psa_algorithm_t alg = alg_arg;
    psa_aead_operation_t operation = PSA_AEAD_OPERATION_INIT;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    mbedtls_svc_key_id_t key_id = MBEDTLS_SVC_KEY_ID_INIT;
    uint8_t input[16] = "ABCDEFGHIJKLMNO";
    uint8_t output[64] = { 0 };
    size_t length = SIZE_MAX;

    PSA_INIT();

    psa_set_key_type(&attributes, key_type);
    psa_set_key_usage_flags(&attributes,
                            PSA_KEY_USAGE_ENCRYPT |
                            PSA_KEY_USAGE_DECRYPT);
    psa_set_key_algorithm(&attributes, alg);
    PSA_ASSERT(psa_import_key(&attributes,
                              key_data->x, key_data->len,
                              &key_id));

    TEST_STATUS(expected_status,
                psa_aead_encrypt_setup(&operation, key_id, alg));
    TEST_STATUS(expected_status,
                psa_aead_decrypt_setup(&operation, key_id, alg));
    TEST_STATUS(expected_status,
                psa_aead_encrypt(key_id, alg,
                                 input, sizeof(input),
                                 NULL, 0, input, sizeof(input),
                                 output, sizeof(output), &length));
    TEST_STATUS(expected_status,
                psa_aead_decrypt(key_id, alg,
                                 input, sizeof(input),
                                 NULL, 0, input, sizeof(input),
                                 output, sizeof(output), &length));

exit:
    psa_aead_abort(&operation);
    psa_destroy_key(key_id);
    psa_reset_key_attributes(&attributes);
    PSA_DONE();
}

void test_aead_fail_wrapper( void ** params )
{
    data_t data1 = {(uint8_t *) params[1], ((mbedtls_test_argument_t *) params[2])->len};

    test_aead_fail( ((mbedtls_test_argument_t *) params[0])->sint, &data1, ((mbedtls_test_argument_t *) params[3])->sint, ((mbedtls_test_argument_t *) params[4])->sint );
}
#line 212 "tests/suites/test_suite_psa_crypto_op_fail.function"
void test_sign_fail(int key_type_arg, data_t *key_data,
               int alg_arg, int private_only,
               int expected_status_arg)
{
    psa_status_t expected_status = expected_status_arg;
    psa_key_type_t key_type = key_type_arg;
    psa_algorithm_t alg = alg_arg;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    mbedtls_svc_key_id_t key_id = MBEDTLS_SVC_KEY_ID_INIT;
    uint8_t input[1] = { 'A' };
    uint8_t output[PSA_SIGNATURE_MAX_SIZE] = { 0 };
    size_t length = SIZE_MAX;
    psa_sign_hash_interruptible_operation_t sign_operation =
        psa_sign_hash_interruptible_operation_init();

    psa_verify_hash_interruptible_operation_t verify_operation =
        psa_verify_hash_interruptible_operation_init();



    PSA_INIT();

    psa_set_key_type(&attributes, key_type);
    psa_set_key_usage_flags(&attributes,
                            PSA_KEY_USAGE_SIGN_HASH |
                            PSA_KEY_USAGE_VERIFY_HASH);
    psa_set_key_algorithm(&attributes, alg);
    PSA_ASSERT(psa_import_key(&attributes,
                              key_data->x, key_data->len,
                              &key_id));

    TEST_STATUS(expected_status,
                psa_sign_hash(key_id, alg,
                              input, sizeof(input),
                              output, sizeof(output), &length));

    TEST_STATUS(expected_status,
                psa_sign_hash_start(&sign_operation, key_id, alg,
                                    input, sizeof(input)));

    PSA_ASSERT(psa_sign_hash_abort(&sign_operation));

    if (!private_only) {
        /* Determine a plausible signature size to avoid an INVALID_SIGNATURE
         * error based on this. */
        PSA_ASSERT(psa_get_key_attributes(key_id, &attributes));
        size_t key_bits = psa_get_key_bits(&attributes);
        size_t output_length = sizeof(output);
        if (PSA_KEY_TYPE_IS_RSA(key_type)) {
            output_length = PSA_BITS_TO_BYTES(key_bits);
        } else if (PSA_KEY_TYPE_IS_ECC(key_type)) {
            output_length = 2 * PSA_BITS_TO_BYTES(key_bits);
        }
        TEST_ASSERT(output_length <= sizeof(output));
        TEST_STATUS(expected_status,
                    psa_verify_hash(key_id, alg,
                                    input, sizeof(input),
                                    output, output_length));

        TEST_STATUS(expected_status,
                    psa_verify_hash_start(&verify_operation, key_id, alg,
                                          input, sizeof(input),
                                          output, output_length));

        PSA_ASSERT(psa_verify_hash_abort(&verify_operation));
    }

exit:
    psa_destroy_key(key_id);
    psa_reset_key_attributes(&attributes);
    PSA_DONE();
}

void test_sign_fail_wrapper( void ** params )
{
    data_t data1 = {(uint8_t *) params[1], ((mbedtls_test_argument_t *) params[2])->len};

    test_sign_fail( ((mbedtls_test_argument_t *) params[0])->sint, &data1, ((mbedtls_test_argument_t *) params[3])->sint, ((mbedtls_test_argument_t *) params[4])->sint, ((mbedtls_test_argument_t *) params[5])->sint );
}
#line 287 "tests/suites/test_suite_psa_crypto_op_fail.function"
void test_asymmetric_encryption_fail(int key_type_arg, data_t *key_data,
                                int alg_arg, int private_only,
                                int expected_status_arg)
{
    psa_status_t expected_status = expected_status_arg;
    psa_key_type_t key_type = key_type_arg;
    psa_algorithm_t alg = alg_arg;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    mbedtls_svc_key_id_t key_id = MBEDTLS_SVC_KEY_ID_INIT;
    uint8_t plaintext[PSA_ASYMMETRIC_DECRYPT_OUTPUT_MAX_SIZE] = { 0 };
    uint8_t ciphertext[PSA_ASYMMETRIC_ENCRYPT_OUTPUT_MAX_SIZE] = { 0 };
    size_t length = SIZE_MAX;

    PSA_INIT();

    psa_set_key_type(&attributes, key_type);
    psa_set_key_usage_flags(&attributes,
                            PSA_KEY_USAGE_ENCRYPT |
                            PSA_KEY_USAGE_DECRYPT);
    psa_set_key_algorithm(&attributes, alg);
    PSA_ASSERT(psa_import_key(&attributes,
                              key_data->x, key_data->len,
                              &key_id));

    if (!private_only) {
        TEST_STATUS(expected_status,
                    psa_asymmetric_encrypt(key_id, alg,
                                           plaintext, 1,
                                           NULL, 0,
                                           ciphertext, sizeof(ciphertext),
                                           &length));
    }
    TEST_STATUS(expected_status,
                psa_asymmetric_decrypt(key_id, alg,
                                       ciphertext, sizeof(ciphertext),
                                       NULL, 0,
                                       plaintext, sizeof(plaintext),
                                       &length));

exit:
    psa_destroy_key(key_id);
    psa_reset_key_attributes(&attributes);
    PSA_DONE();
}

void test_asymmetric_encryption_fail_wrapper( void ** params )
{
    data_t data1 = {(uint8_t *) params[1], ((mbedtls_test_argument_t *) params[2])->len};

    test_asymmetric_encryption_fail( ((mbedtls_test_argument_t *) params[0])->sint, &data1, ((mbedtls_test_argument_t *) params[3])->sint, ((mbedtls_test_argument_t *) params[4])->sint, ((mbedtls_test_argument_t *) params[5])->sint );
}
#line 334 "tests/suites/test_suite_psa_crypto_op_fail.function"
void test_key_derivation_fail(int alg_arg, int expected_status_arg)
{
    psa_status_t expected_status = expected_status_arg;
    psa_algorithm_t alg = alg_arg;
    psa_key_derivation_operation_t operation = PSA_KEY_DERIVATION_OPERATION_INIT;

    PSA_INIT();

    TEST_EQUAL(expected_status,
               psa_key_derivation_setup(&operation, alg));

exit:
    psa_key_derivation_abort(&operation);
    PSA_DONE();
}

void test_key_derivation_fail_wrapper( void ** params )
{

    test_key_derivation_fail( ((mbedtls_test_argument_t *) params[0])->sint, ((mbedtls_test_argument_t *) params[1])->sint );
}
#line 352 "tests/suites/test_suite_psa_crypto_op_fail.function"
void test_key_agreement_fail(int key_type_arg, data_t *key_data,
                        int alg_arg, int private_only,
                        int expected_status_arg)
{
    psa_status_t expected_status = expected_status_arg;
    psa_key_type_t key_type = key_type_arg;
    psa_algorithm_t alg = alg_arg;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    mbedtls_svc_key_id_t key_id = MBEDTLS_SVC_KEY_ID_INIT;
    uint8_t public_key[PSA_EXPORT_PUBLIC_KEY_MAX_SIZE] = { 0 };
    size_t public_key_length = SIZE_MAX;
    uint8_t output[PSA_RAW_KEY_AGREEMENT_OUTPUT_MAX_SIZE] = { 0 };
    size_t length = SIZE_MAX;
    psa_key_derivation_operation_t operation = PSA_KEY_DERIVATION_OPERATION_INIT;

    PSA_INIT();

    psa_set_key_type(&attributes, key_type);
    psa_set_key_usage_flags(&attributes,
                            PSA_KEY_USAGE_DERIVE);
    psa_set_key_algorithm(&attributes, alg);
    PSA_ASSERT(psa_import_key(&attributes,
                              key_data->x, key_data->len,
                              &key_id));
    if (PSA_KEY_TYPE_IS_KEY_PAIR(key_type) ||
        PSA_KEY_TYPE_IS_PUBLIC_KEY(key_type)) {
        PSA_ASSERT(psa_export_public_key(key_id,
                                         public_key, sizeof(public_key),
                                         &public_key_length));
    }

    TEST_STATUS(expected_status,
                psa_raw_key_agreement(alg, key_id,
                                      public_key, public_key_length,
                                      output, sizeof(output), &length));

#if defined(PSA_WANT_ALG_HKDF) && defined(PSA_WANT_ALG_SHA_256)
    PSA_ASSERT(psa_key_derivation_setup(&operation,
                                        PSA_ALG_HKDF(PSA_ALG_SHA_256)));
    TEST_STATUS(expected_status,
                psa_key_derivation_key_agreement(
                    &operation,
                    PSA_KEY_DERIVATION_INPUT_SECRET,
                    key_id,
                    public_key, public_key_length));
#endif

    /* There are no public-key operations. */
    (void) private_only;

exit:
    psa_key_derivation_abort(&operation);
    psa_destroy_key(key_id);
    psa_reset_key_attributes(&attributes);
    PSA_DONE();
}

void test_key_agreement_fail_wrapper( void ** params )
{
    data_t data1 = {(uint8_t *) params[1], ((mbedtls_test_argument_t *) params[2])->len};

    test_key_agreement_fail( ((mbedtls_test_argument_t *) params[0])->sint, &data1, ((mbedtls_test_argument_t *) params[3])->sint, ((mbedtls_test_argument_t *) params[4])->sint, ((mbedtls_test_argument_t *) params[5])->sint );
}
#endif /* MBEDTLS_PSA_CRYPTO_C */


#line 54 "suites/main_test.function"


/*----------------------------------------------------------------------------*/
/* Test dispatch code */


/**
 * \brief       Evaluates an expression/macro into its literal integer value.
 *              For optimizing space for embedded targets each expression/macro
 *              is identified by a unique identifier instead of string literals.
 *              Identifiers and evaluation code is generated by script:
 *              generate_test_code.py
 *
 * \param exp_id    Expression identifier.
 * \param out_value Pointer to int to hold the integer.
 *
 * \return       0 if exp_id is found. 1 otherwise.
 */
int get_expression(int32_t exp_id, intmax_t *out_value)
{
    int ret = KEY_VALUE_MAPPING_FOUND;

    (void) exp_id;
    (void) out_value;

    switch (exp_id) {
    
#if defined(MBEDTLS_PSA_CRYPTO_C)

        case 0:
            {
                *out_value = PSA_ALG_AEAD_WITH_AT_LEAST_THIS_LENGTH_TAG(PSA_ALG_CCM,1);
            }
            break;
        case 1:
            {
                *out_value = PSA_ERROR_INVALID_ARGUMENT;
            }
            break;
        case 2:
            {
                *out_value = PSA_KEY_TYPE_AES;
            }
            break;
        case 3:
            {
                *out_value = PSA_KEY_TYPE_ARIA;
            }
            break;
        case 4:
            {
                *out_value = PSA_KEY_TYPE_CAMELLIA;
            }
            break;
        case 5:
            {
                *out_value = PSA_KEY_TYPE_CHACHA20;
            }
            break;
        case 6:
            {
                *out_value = PSA_KEY_TYPE_DERIVE;
            }
            break;
        case 7:
            {
                *out_value = PSA_KEY_TYPE_DES;
            }
            break;
        case 8:
            {
                *out_value = PSA_KEY_TYPE_DH_KEY_PAIR(PSA_DH_FAMILY_RFC7919);
            }
            break;
        case 9:
            {
                *out_value = PSA_KEY_TYPE_DH_PUBLIC_KEY(PSA_DH_FAMILY_RFC7919);
            }
            break;
        case 10:
            {
                *out_value = PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_BRAINPOOL_P_R1);
            }
            break;
        case 11:
            {
                *out_value = PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_MONTGOMERY);
            }
            break;
        case 12:
            {
                *out_value = PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_K1);
            }
            break;
        case 13:
            {
                *out_value = PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1);
            }
            break;
        case 14:
            {
                *out_value = PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R2);
            }
            break;
        case 15:
            {
                *out_value = PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECT_K1);
            }
            break;
        case 16:
            {
                *out_value = PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECT_R1);
            }
            break;
        case 17:
            {
                *out_value = PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECT_R2);
            }
            break;
        case 18:
            {
                *out_value = PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_TWISTED_EDWARDS);
            }
            break;
        case 19:
            {
                *out_value = PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_BRAINPOOL_P_R1);
            }
            break;
        case 20:
            {
                *out_value = PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_MONTGOMERY);
            }
            break;
        case 21:
            {
                *out_value = PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_SECP_K1);
            }
            break;
        case 22:
            {
                *out_value = PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_SECP_R1);
            }
            break;
        case 23:
            {
                *out_value = PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_SECP_R2);
            }
            break;
        case 24:
            {
                *out_value = PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_SECT_K1);
            }
            break;
        case 25:
            {
                *out_value = PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_SECT_R1);
            }
            break;
        case 26:
            {
                *out_value = PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_SECT_R2);
            }
            break;
        case 27:
            {
                *out_value = PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_TWISTED_EDWARDS);
            }
            break;
        case 28:
            {
                *out_value = PSA_KEY_TYPE_HMAC;
            }
            break;
        case 29:
            {
                *out_value = PSA_KEY_TYPE_PASSWORD;
            }
            break;
        case 30:
            {
                *out_value = PSA_KEY_TYPE_PASSWORD_HASH;
            }
            break;
        case 31:
            {
                *out_value = PSA_KEY_TYPE_PEPPER;
            }
            break;
        case 32:
            {
                *out_value = PSA_KEY_TYPE_RAW_DATA;
            }
            break;
        case 33:
            {
                *out_value = PSA_KEY_TYPE_RSA_KEY_PAIR;
            }
            break;
        case 34:
            {
                *out_value = PSA_KEY_TYPE_RSA_PUBLIC_KEY;
            }
            break;
        case 35:
            {
                *out_value = PSA_ALG_AEAD_WITH_AT_LEAST_THIS_LENGTH_TAG(PSA_ALG_CHACHA20_POLY1305,1);
            }
            break;
        case 36:
            {
                *out_value = PSA_ALG_AEAD_WITH_AT_LEAST_THIS_LENGTH_TAG(PSA_ALG_GCM,1);
            }
            break;
        case 37:
            {
                *out_value = PSA_ALG_AEAD_WITH_AT_LEAST_THIS_LENGTH_TAG(PSA_ALG_CCM,4);
            }
            break;
        case 38:
            {
                *out_value = PSA_ALG_AEAD_WITH_AT_LEAST_THIS_LENGTH_TAG(PSA_ALG_CCM,13);
            }
            break;
        case 39:
            {
                *out_value = PSA_ALG_AEAD_WITH_AT_LEAST_THIS_LENGTH_TAG(PSA_ALG_CCM,14);
            }
            break;
        case 40:
            {
                *out_value = PSA_ALG_AEAD_WITH_AT_LEAST_THIS_LENGTH_TAG(PSA_ALG_CCM,16);
            }
            break;
        case 41:
            {
                *out_value = PSA_ALG_AEAD_WITH_AT_LEAST_THIS_LENGTH_TAG(PSA_ALG_CCM,63);
            }
            break;
        case 42:
            {
                *out_value = PSA_ALG_AEAD_WITH_SHORTENED_TAG(PSA_ALG_CCM,1);
            }
            break;
        case 43:
            {
                *out_value = PSA_ALG_AEAD_WITH_SHORTENED_TAG(PSA_ALG_CHACHA20_POLY1305,1);
            }
            break;
        case 44:
            {
                *out_value = PSA_ALG_AEAD_WITH_SHORTENED_TAG(PSA_ALG_GCM,1);
            }
            break;
        case 45:
            {
                *out_value = PSA_ALG_AEAD_WITH_SHORTENED_TAG(PSA_ALG_CCM,4);
            }
            break;
        case 46:
            {
                *out_value = PSA_ERROR_NOT_SUPPORTED;
            }
            break;
        case 47:
            {
                *out_value = PSA_ALG_AEAD_WITH_SHORTENED_TAG(PSA_ALG_CCM,13);
            }
            break;
        case 48:
            {
                *out_value = PSA_ALG_AEAD_WITH_SHORTENED_TAG(PSA_ALG_CCM,14);
            }
            break;
        case 49:
            {
                *out_value = PSA_ALG_AEAD_WITH_SHORTENED_TAG(PSA_ALG_CCM,16);
            }
            break;
        case 50:
            {
                *out_value = PSA_ALG_AEAD_WITH_SHORTENED_TAG(PSA_ALG_CCM,63);
            }
            break;
        case 51:
            {
                *out_value = PSA_ALG_ANY_HASH;
            }
            break;
        case 52:
            {
                *out_value = PSA_ALG_AT_LEAST_THIS_LENGTH_MAC(PSA_ALG_CBC_MAC,1);
            }
            break;
        case 53:
            {
                *out_value = PSA_ALG_AT_LEAST_THIS_LENGTH_MAC(PSA_ALG_CMAC,1);
            }
            break;
        case 54:
            {
                *out_value = PSA_ALG_AT_LEAST_THIS_LENGTH_MAC(PSA_ALG_HMAC(PSA_ALG_MD5),1);
            }
            break;
        case 55:
            {
                *out_value = PSA_ALG_AT_LEAST_THIS_LENGTH_MAC(PSA_ALG_HMAC(PSA_ALG_RIPEMD160),1);
            }
            break;
        case 56:
            {
                *out_value = PSA_ALG_AT_LEAST_THIS_LENGTH_MAC(PSA_ALG_HMAC(PSA_ALG_SHA_1),1);
            }
            break;
        case 57:
            {
                *out_value = PSA_ALG_AT_LEAST_THIS_LENGTH_MAC(PSA_ALG_HMAC(PSA_ALG_SHA_224),1);
            }
            break;
        case 58:
            {
                *out_value = PSA_ALG_AT_LEAST_THIS_LENGTH_MAC(PSA_ALG_HMAC(PSA_ALG_SHA_256),1);
            }
            break;
        case 59:
            {
                *out_value = PSA_ALG_AT_LEAST_THIS_LENGTH_MAC(PSA_ALG_HMAC(PSA_ALG_SHA_384),1);
            }
            break;
        case 60:
            {
                *out_value = PSA_ALG_AT_LEAST_THIS_LENGTH_MAC(PSA_ALG_HMAC(PSA_ALG_SHA_512),1);
            }
            break;
        case 61:
            {
                *out_value = PSA_ALG_AT_LEAST_THIS_LENGTH_MAC(PSA_ALG_CBC_MAC,4);
            }
            break;
        case 62:
            {
                *out_value = PSA_ALG_AT_LEAST_THIS_LENGTH_MAC(PSA_ALG_CBC_MAC,13);
            }
            break;
        case 63:
            {
                *out_value = PSA_ALG_AT_LEAST_THIS_LENGTH_MAC(PSA_ALG_CBC_MAC,14);
            }
            break;
        case 64:
            {
                *out_value = PSA_ALG_AT_LEAST_THIS_LENGTH_MAC(PSA_ALG_CBC_MAC,16);
            }
            break;
        case 65:
            {
                *out_value = PSA_ALG_AT_LEAST_THIS_LENGTH_MAC(PSA_ALG_CBC_MAC,63);
            }
            break;
        case 66:
            {
                *out_value = PSA_ALG_CBC_MAC;
            }
            break;
        case 67:
            {
                *out_value = PSA_ALG_CBC_NO_PADDING;
            }
            break;
        case 68:
            {
                *out_value = PSA_ALG_CBC_PKCS7;
            }
            break;
        case 69:
            {
                *out_value = PSA_ALG_CCM;
            }
            break;
        case 70:
            {
                *out_value = PSA_ALG_CCM_STAR_NO_TAG;
            }
            break;
        case 71:
            {
                *out_value = PSA_ALG_CFB;
            }
            break;
        case 72:
            {
                *out_value = PSA_ALG_CHACHA20_POLY1305;
            }
            break;
        case 73:
            {
                *out_value = PSA_ALG_CMAC;
            }
            break;
        case 74:
            {
                *out_value = PSA_ALG_CTR;
            }
            break;
        case 75:
            {
                *out_value = PSA_ALG_DETERMINISTIC_DSA(PSA_ALG_MD5);
            }
            break;
        case 76:
            {
                *out_value = PSA_ALG_DETERMINISTIC_DSA(PSA_ALG_RIPEMD160);
            }
            break;
        case 77:
            {
                *out_value = PSA_ALG_DETERMINISTIC_DSA(PSA_ALG_SHA3_224);
            }
            break;
        case 78:
            {
                *out_value = PSA_ALG_DETERMINISTIC_DSA(PSA_ALG_SHA3_256);
            }
            break;
        case 79:
            {
                *out_value = PSA_ALG_DETERMINISTIC_DSA(PSA_ALG_SHA3_384);
            }
            break;
        case 80:
            {
                *out_value = PSA_ALG_DETERMINISTIC_DSA(PSA_ALG_SHA3_512);
            }
            break;
        case 81:
            {
                *out_value = PSA_ALG_DETERMINISTIC_DSA(PSA_ALG_SHA_1);
            }
            break;
        case 82:
            {
                *out_value = PSA_ALG_DETERMINISTIC_DSA(PSA_ALG_SHA_224);
            }
            break;
        case 83:
            {
                *out_value = PSA_ALG_DETERMINISTIC_DSA(PSA_ALG_SHA_256);
            }
            break;
        case 84:
            {
                *out_value = PSA_ALG_DETERMINISTIC_DSA(PSA_ALG_SHA_384);
            }
            break;
        case 85:
            {
                *out_value = PSA_ALG_DETERMINISTIC_DSA(PSA_ALG_SHA_512);
            }
            break;
        case 86:
            {
                *out_value = PSA_ALG_DETERMINISTIC_ECDSA(PSA_ALG_MD5);
            }
            break;
        case 87:
            {
                *out_value = PSA_ALG_DETERMINISTIC_ECDSA(PSA_ALG_RIPEMD160);
            }
            break;
        case 88:
            {
                *out_value = PSA_ALG_DETERMINISTIC_ECDSA(PSA_ALG_SHA3_224);
            }
            break;
        case 89:
            {
                *out_value = PSA_ALG_DETERMINISTIC_ECDSA(PSA_ALG_SHA3_256);
            }
            break;
        case 90:
            {
                *out_value = PSA_ALG_DETERMINISTIC_ECDSA(PSA_ALG_SHA3_384);
            }
            break;
        case 91:
            {
                *out_value = PSA_ALG_DETERMINISTIC_ECDSA(PSA_ALG_SHA3_512);
            }
            break;
        case 92:
            {
                *out_value = PSA_ALG_DETERMINISTIC_ECDSA(PSA_ALG_SHA_1);
            }
            break;
        case 93:
            {
                *out_value = PSA_ALG_DETERMINISTIC_ECDSA(PSA_ALG_SHA_224);
            }
            break;
        case 94:
            {
                *out_value = PSA_ALG_DETERMINISTIC_ECDSA(PSA_ALG_SHA_256);
            }
            break;
        case 95:
            {
                *out_value = PSA_ALG_DETERMINISTIC_ECDSA(PSA_ALG_SHA_384);
            }
            break;
        case 96:
            {
                *out_value = PSA_ALG_DETERMINISTIC_ECDSA(PSA_ALG_SHA_512);
            }
            break;
        case 97:
            {
                *out_value = PSA_ALG_DETERMINISTIC_ECDSA(PSA_ALG_ANY_HASH);
            }
            break;
        case 98:
            {
                *out_value = PSA_ALG_DSA(PSA_ALG_MD5);
            }
            break;
        case 99:
            {
                *out_value = PSA_ALG_DSA(PSA_ALG_RIPEMD160);
            }
            break;
        case 100:
            {
                *out_value = PSA_ALG_DSA(PSA_ALG_SHA3_224);
            }
            break;
        case 101:
            {
                *out_value = PSA_ALG_DSA(PSA_ALG_SHA3_256);
            }
            break;
        case 102:
            {
                *out_value = PSA_ALG_DSA(PSA_ALG_SHA3_384);
            }
            break;
        case 103:
            {
                *out_value = PSA_ALG_DSA(PSA_ALG_SHA3_512);
            }
            break;
        case 104:
            {
                *out_value = PSA_ALG_DSA(PSA_ALG_SHA_1);
            }
            break;
        case 105:
            {
                *out_value = PSA_ALG_DSA(PSA_ALG_SHA_224);
            }
            break;
        case 106:
            {
                *out_value = PSA_ALG_DSA(PSA_ALG_SHA_256);
            }
            break;
        case 107:
            {
                *out_value = PSA_ALG_DSA(PSA_ALG_SHA_384);
            }
            break;
        case 108:
            {
                *out_value = PSA_ALG_DSA(PSA_ALG_SHA_512);
            }
            break;
        case 109:
            {
                *out_value = PSA_ALG_ECB_NO_PADDING;
            }
            break;
        case 110:
            {
                *out_value = PSA_ALG_ECDH;
            }
            break;
        case 111:
            {
                *out_value = PSA_ALG_ECDSA(PSA_ALG_MD5);
            }
            break;
        case 112:
            {
                *out_value = PSA_ALG_ECDSA(PSA_ALG_RIPEMD160);
            }
            break;
        case 113:
            {
                *out_value = PSA_ALG_ECDSA(PSA_ALG_SHA3_224);
            }
            break;
        case 114:
            {
                *out_value = PSA_ALG_ECDSA(PSA_ALG_SHA3_256);
            }
            break;
        case 115:
            {
                *out_value = PSA_ALG_ECDSA(PSA_ALG_SHA3_384);
            }
            break;
        case 116:
            {
                *out_value = PSA_ALG_ECDSA(PSA_ALG_SHA3_512);
            }
            break;
        case 117:
            {
                *out_value = PSA_ALG_ECDSA(PSA_ALG_SHA_1);
            }
            break;
        case 118:
            {
                *out_value = PSA_ALG_ECDSA(PSA_ALG_SHA_224);
            }
            break;
        case 119:
            {
                *out_value = PSA_ALG_ECDSA(PSA_ALG_SHA_256);
            }
            break;
        case 120:
            {
                *out_value = PSA_ALG_ECDSA(PSA_ALG_SHA_384);
            }
            break;
        case 121:
            {
                *out_value = PSA_ALG_ECDSA(PSA_ALG_SHA_512);
            }
            break;
        case 122:
            {
                *out_value = PSA_ALG_ECDSA(PSA_ALG_ANY_HASH);
            }
            break;
        case 123:
            {
                *out_value = PSA_ALG_ECDSA_ANY;
            }
            break;
        case 124:
            {
                *out_value = PSA_ALG_ED25519PH;
            }
            break;
        case 125:
            {
                *out_value = PSA_ALG_ED448PH;
            }
            break;
        case 126:
            {
                *out_value = PSA_ALG_FFDH;
            }
            break;
        case 127:
            {
                *out_value = PSA_ALG_GCM;
            }
            break;
        case 128:
            {
                *out_value = PSA_ALG_HKDF(PSA_ALG_MD5);
            }
            break;
        case 129:
            {
                *out_value = PSA_ALG_HKDF(PSA_ALG_RIPEMD160);
            }
            break;
        case 130:
            {
                *out_value = PSA_ALG_HKDF(PSA_ALG_SHA3_224);
            }
            break;
        case 131:
            {
                *out_value = PSA_ALG_HKDF(PSA_ALG_SHA3_256);
            }
            break;
        case 132:
            {
                *out_value = PSA_ALG_HKDF(PSA_ALG_SHA3_384);
            }
            break;
        case 133:
            {
                *out_value = PSA_ALG_HKDF(PSA_ALG_SHA3_512);
            }
            break;
        case 134:
            {
                *out_value = PSA_ALG_HKDF(PSA_ALG_SHA_1);
            }
            break;
        case 135:
            {
                *out_value = PSA_ALG_HKDF(PSA_ALG_SHA_224);
            }
            break;
        case 136:
            {
                *out_value = PSA_ALG_HKDF(PSA_ALG_SHA_256);
            }
            break;
        case 137:
            {
                *out_value = PSA_ALG_HKDF(PSA_ALG_SHA_384);
            }
            break;
        case 138:
            {
                *out_value = PSA_ALG_HKDF(PSA_ALG_SHA_512);
            }
            break;
        case 139:
            {
                *out_value = PSA_ALG_HKDF_EXPAND(PSA_ALG_MD5);
            }
            break;
        case 140:
            {
                *out_value = PSA_ALG_HKDF_EXPAND(PSA_ALG_RIPEMD160);
            }
            break;
        case 141:
            {
                *out_value = PSA_ALG_HKDF_EXPAND(PSA_ALG_SHA3_224);
            }
            break;
        case 142:
            {
                *out_value = PSA_ALG_HKDF_EXPAND(PSA_ALG_SHA3_256);
            }
            break;
        case 143:
            {
                *out_value = PSA_ALG_HKDF_EXPAND(PSA_ALG_SHA3_384);
            }
            break;
        case 144:
            {
                *out_value = PSA_ALG_HKDF_EXPAND(PSA_ALG_SHA3_512);
            }
            break;
        case 145:
            {
                *out_value = PSA_ALG_HKDF_EXPAND(PSA_ALG_SHA_1);
            }
            break;
        case 146:
            {
                *out_value = PSA_ALG_HKDF_EXPAND(PSA_ALG_SHA_224);
            }
            break;
        case 147:
            {
                *out_value = PSA_ALG_HKDF_EXPAND(PSA_ALG_SHA_256);
            }
            break;
        case 148:
            {
                *out_value = PSA_ALG_HKDF_EXPAND(PSA_ALG_SHA_384);
            }
            break;
        case 149:
            {
                *out_value = PSA_ALG_HKDF_EXPAND(PSA_ALG_SHA_512);
            }
            break;
        case 150:
            {
                *out_value = PSA_ALG_HKDF_EXTRACT(PSA_ALG_MD5);
            }
            break;
        case 151:
            {
                *out_value = PSA_ALG_HKDF_EXTRACT(PSA_ALG_RIPEMD160);
            }
            break;
        case 152:
            {
                *out_value = PSA_ALG_HKDF_EXTRACT(PSA_ALG_SHA3_224);
            }
            break;
        case 153:
            {
                *out_value = PSA_ALG_HKDF_EXTRACT(PSA_ALG_SHA3_256);
            }
            break;
        case 154:
            {
                *out_value = PSA_ALG_HKDF_EXTRACT(PSA_ALG_SHA3_384);
            }
            break;
        case 155:
            {
                *out_value = PSA_ALG_HKDF_EXTRACT(PSA_ALG_SHA3_512);
            }
            break;
        case 156:
            {
                *out_value = PSA_ALG_HKDF_EXTRACT(PSA_ALG_SHA_1);
            }
            break;
        case 157:
            {
                *out_value = PSA_ALG_HKDF_EXTRACT(PSA_ALG_SHA_224);
            }
            break;
        case 158:
            {
                *out_value = PSA_ALG_HKDF_EXTRACT(PSA_ALG_SHA_256);
            }
            break;
        case 159:
            {
                *out_value = PSA_ALG_HKDF_EXTRACT(PSA_ALG_SHA_384);
            }
            break;
        case 160:
            {
                *out_value = PSA_ALG_HKDF_EXTRACT(PSA_ALG_SHA_512);
            }
            break;
        case 161:
            {
                *out_value = PSA_ALG_HMAC(PSA_ALG_MD5);
            }
            break;
        case 162:
            {
                *out_value = PSA_ALG_HMAC(PSA_ALG_RIPEMD160);
            }
            break;
        case 163:
            {
                *out_value = PSA_ALG_HMAC(PSA_ALG_SHA3_224);
            }
            break;
        case 164:
            {
                *out_value = PSA_ALG_HMAC(PSA_ALG_SHA3_256);
            }
            break;
        case 165:
            {
                *out_value = PSA_ALG_HMAC(PSA_ALG_SHA3_384);
            }
            break;
        case 166:
            {
                *out_value = PSA_ALG_HMAC(PSA_ALG_SHA3_512);
            }
            break;
        case 167:
            {
                *out_value = PSA_ALG_HMAC(PSA_ALG_SHA_1);
            }
            break;
        case 168:
            {
                *out_value = PSA_ALG_HMAC(PSA_ALG_SHA_224);
            }
            break;
        case 169:
            {
                *out_value = PSA_ALG_HMAC(PSA_ALG_SHA_256);
            }
            break;
        case 170:
            {
                *out_value = PSA_ALG_HMAC(PSA_ALG_SHA_384);
            }
            break;
        case 171:
            {
                *out_value = PSA_ALG_HMAC(PSA_ALG_SHA_512);
            }
            break;
        case 172:
            {
                *out_value = PSA_ALG_JPAKE;
            }
            break;
        case 173:
            {
                *out_value = PSA_ALG_KEY_AGREEMENT(PSA_ALG_ECDH,PSA_ALG_HKDF(PSA_ALG_SHA_256));
            }
            break;
        case 174:
            {
                *out_value = PSA_ALG_KEY_AGREEMENT(PSA_ALG_FFDH,PSA_ALG_HKDF(PSA_ALG_SHA_256));
            }
            break;
        case 175:
            {
                *out_value = PSA_ALG_KEY_AGREEMENT(PSA_ALG_ECDH,PSA_ALG_HKDF(PSA_ALG_SHA_384));
            }
            break;
        case 176:
            {
                *out_value = PSA_ALG_KEY_AGREEMENT(PSA_ALG_ECDH,PSA_ALG_HKDF_EXPAND(PSA_ALG_SHA_256));
            }
            break;
        case 177:
            {
                *out_value = PSA_ALG_KEY_AGREEMENT(PSA_ALG_ECDH,PSA_ALG_HKDF_EXPAND(PSA_ALG_SHA_384));
            }
            break;
        case 178:
            {
                *out_value = PSA_ALG_KEY_AGREEMENT(PSA_ALG_ECDH,PSA_ALG_HKDF_EXTRACT(PSA_ALG_SHA_256));
            }
            break;
        case 179:
            {
                *out_value = PSA_ALG_KEY_AGREEMENT(PSA_ALG_ECDH,PSA_ALG_HKDF_EXTRACT(PSA_ALG_SHA_384));
            }
            break;
        case 180:
            {
                *out_value = PSA_ALG_KEY_AGREEMENT(PSA_ALG_ECDH,PSA_ALG_TLS12_ECJPAKE_TO_PMS);
            }
            break;
        case 181:
            {
                *out_value = PSA_ALG_KEY_AGREEMENT(PSA_ALG_ECDH,PSA_ALG_TLS12_PRF(PSA_ALG_SHA_256));
            }
            break;
        case 182:
            {
                *out_value = PSA_ALG_KEY_AGREEMENT(PSA_ALG_ECDH,PSA_ALG_TLS12_PRF(PSA_ALG_SHA_384));
            }
            break;
        case 183:
            {
                *out_value = PSA_ALG_KEY_AGREEMENT(PSA_ALG_ECDH,PSA_ALG_TLS12_PSK_TO_MS(PSA_ALG_SHA_256));
            }
            break;
        case 184:
            {
                *out_value = PSA_ALG_KEY_AGREEMENT(PSA_ALG_ECDH,PSA_ALG_TLS12_PSK_TO_MS(PSA_ALG_SHA_384));
            }
            break;
        case 185:
            {
                *out_value = PSA_ALG_KEY_AGREEMENT(PSA_ALG_FFDH,PSA_ALG_HKDF(PSA_ALG_SHA_384));
            }
            break;
        case 186:
            {
                *out_value = PSA_ALG_MD5;
            }
            break;
        case 187:
            {
                *out_value = PSA_ALG_OFB;
            }
            break;
        case 188:
            {
                *out_value = PSA_ALG_PBKDF2_AES_CMAC_PRF_128;
            }
            break;
        case 189:
            {
                *out_value = PSA_ALG_PBKDF2_HMAC(PSA_ALG_MD5);
            }
            break;
        case 190:
            {
                *out_value = PSA_ALG_PBKDF2_HMAC(PSA_ALG_RIPEMD160);
            }
            break;
        case 191:
            {
                *out_value = PSA_ALG_PBKDF2_HMAC(PSA_ALG_SHA3_224);
            }
            break;
        case 192:
            {
                *out_value = PSA_ALG_PBKDF2_HMAC(PSA_ALG_SHA3_256);
            }
            break;
        case 193:
            {
                *out_value = PSA_ALG_PBKDF2_HMAC(PSA_ALG_SHA3_384);
            }
            break;
        case 194:
            {
                *out_value = PSA_ALG_PBKDF2_HMAC(PSA_ALG_SHA3_512);
            }
            break;
        case 195:
            {
                *out_value = PSA_ALG_PBKDF2_HMAC(PSA_ALG_SHA_1);
            }
            break;
        case 196:
            {
                *out_value = PSA_ALG_PBKDF2_HMAC(PSA_ALG_SHA_224);
            }
            break;
        case 197:
            {
                *out_value = PSA_ALG_PBKDF2_HMAC(PSA_ALG_SHA_256);
            }
            break;
        case 198:
            {
                *out_value = PSA_ALG_PBKDF2_HMAC(PSA_ALG_SHA_384);
            }
            break;
        case 199:
            {
                *out_value = PSA_ALG_PBKDF2_HMAC(PSA_ALG_SHA_512);
            }
            break;
        case 200:
            {
                *out_value = PSA_ALG_PURE_EDDSA;
            }
            break;
        case 201:
            {
                *out_value = PSA_ALG_RIPEMD160;
            }
            break;
        case 202:
            {
                *out_value = PSA_ALG_RSA_OAEP(PSA_ALG_MD5);
            }
            break;
        case 203:
            {
                *out_value = PSA_ALG_RSA_OAEP(PSA_ALG_RIPEMD160);
            }
            break;
        case 204:
            {
                *out_value = PSA_ALG_RSA_OAEP(PSA_ALG_SHA3_224);
            }
            break;
        case 205:
            {
                *out_value = PSA_ALG_RSA_OAEP(PSA_ALG_SHA3_256);
            }
            break;
        case 206:
            {
                *out_value = PSA_ALG_RSA_OAEP(PSA_ALG_SHA3_384);
            }
            break;
        case 207:
            {
                *out_value = PSA_ALG_RSA_OAEP(PSA_ALG_SHA3_512);
            }
            break;
        case 208:
            {
                *out_value = PSA_ALG_RSA_OAEP(PSA_ALG_SHA_1);
            }
            break;
        case 209:
            {
                *out_value = PSA_ALG_RSA_OAEP(PSA_ALG_SHA_224);
            }
            break;
        case 210:
            {
                *out_value = PSA_ALG_RSA_OAEP(PSA_ALG_SHA_256);
            }
            break;
        case 211:
            {
                *out_value = PSA_ALG_RSA_OAEP(PSA_ALG_SHA_384);
            }
            break;
        case 212:
            {
                *out_value = PSA_ALG_RSA_OAEP(PSA_ALG_SHA_512);
            }
            break;
        case 213:
            {
                *out_value = PSA_ALG_RSA_PKCS1V15_CRYPT;
            }
            break;
        case 214:
            {
                *out_value = PSA_ALG_RSA_PKCS1V15_SIGN(PSA_ALG_MD5);
            }
            break;
        case 215:
            {
                *out_value = PSA_ALG_RSA_PKCS1V15_SIGN(PSA_ALG_RIPEMD160);
            }
            break;
        case 216:
            {
                *out_value = PSA_ALG_RSA_PKCS1V15_SIGN(PSA_ALG_SHA3_224);
            }
            break;
        case 217:
            {
                *out_value = PSA_ALG_RSA_PKCS1V15_SIGN(PSA_ALG_SHA3_256);
            }
            break;
        case 218:
            {
                *out_value = PSA_ALG_RSA_PKCS1V15_SIGN(PSA_ALG_SHA3_384);
            }
            break;
        case 219:
            {
                *out_value = PSA_ALG_RSA_PKCS1V15_SIGN(PSA_ALG_SHA3_512);
            }
            break;
        case 220:
            {
                *out_value = PSA_ALG_RSA_PKCS1V15_SIGN(PSA_ALG_SHA_1);
            }
            break;
        case 221:
            {
                *out_value = PSA_ALG_RSA_PKCS1V15_SIGN(PSA_ALG_SHA_224);
            }
            break;
        case 222:
            {
                *out_value = PSA_ALG_RSA_PKCS1V15_SIGN(PSA_ALG_SHA_256);
            }
            break;
        case 223:
            {
                *out_value = PSA_ALG_RSA_PKCS1V15_SIGN(PSA_ALG_SHA_384);
            }
            break;
        case 224:
            {
                *out_value = PSA_ALG_RSA_PKCS1V15_SIGN(PSA_ALG_SHA_512);
            }
            break;
        case 225:
            {
                *out_value = PSA_ALG_RSA_PKCS1V15_SIGN(PSA_ALG_ANY_HASH);
            }
            break;
        case 226:
            {
                *out_value = PSA_ALG_RSA_PKCS1V15_SIGN_RAW;
            }
            break;
        case 227:
            {
                *out_value = PSA_ALG_RSA_PSS(PSA_ALG_MD5);
            }
            break;
        case 228:
            {
                *out_value = PSA_ALG_RSA_PSS(PSA_ALG_RIPEMD160);
            }
            break;
        case 229:
            {
                *out_value = PSA_ALG_RSA_PSS(PSA_ALG_SHA3_224);
            }
            break;
        case 230:
            {
                *out_value = PSA_ALG_RSA_PSS(PSA_ALG_SHA3_256);
            }
            break;
        case 231:
            {
                *out_value = PSA_ALG_RSA_PSS(PSA_ALG_SHA3_384);
            }
            break;
        case 232:
            {
                *out_value = PSA_ALG_RSA_PSS(PSA_ALG_SHA3_512);
            }
            break;
        case 233:
            {
                *out_value = PSA_ALG_RSA_PSS(PSA_ALG_SHA_1);
            }
            break;
        case 234:
            {
                *out_value = PSA_ALG_RSA_PSS(PSA_ALG_SHA_224);
            }
            break;
        case 235:
            {
                *out_value = PSA_ALG_RSA_PSS(PSA_ALG_SHA_256);
            }
            break;
        case 236:
            {
                *out_value = PSA_ALG_RSA_PSS(PSA_ALG_SHA_384);
            }
            break;
        case 237:
            {
                *out_value = PSA_ALG_RSA_PSS(PSA_ALG_SHA_512);
            }
            break;
        case 238:
            {
                *out_value = PSA_ALG_RSA_PSS(PSA_ALG_ANY_HASH);
            }
            break;
        case 239:
            {
                *out_value = PSA_ALG_RSA_PSS_ANY_SALT(PSA_ALG_MD5);
            }
            break;
        case 240:
            {
                *out_value = PSA_ALG_RSA_PSS_ANY_SALT(PSA_ALG_RIPEMD160);
            }
            break;
        case 241:
            {
                *out_value = PSA_ALG_RSA_PSS_ANY_SALT(PSA_ALG_SHA3_224);
            }
            break;
        case 242:
            {
                *out_value = PSA_ALG_RSA_PSS_ANY_SALT(PSA_ALG_SHA3_256);
            }
            break;
        case 243:
            {
                *out_value = PSA_ALG_RSA_PSS_ANY_SALT(PSA_ALG_SHA3_384);
            }
            break;
        case 244:
            {
                *out_value = PSA_ALG_RSA_PSS_ANY_SALT(PSA_ALG_SHA3_512);
            }
            break;
        case 245:
            {
                *out_value = PSA_ALG_RSA_PSS_ANY_SALT(PSA_ALG_SHA_1);
            }
            break;
        case 246:
            {
                *out_value = PSA_ALG_RSA_PSS_ANY_SALT(PSA_ALG_SHA_224);
            }
            break;
        case 247:
            {
                *out_value = PSA_ALG_RSA_PSS_ANY_SALT(PSA_ALG_SHA_256);
            }
            break;
        case 248:
            {
                *out_value = PSA_ALG_RSA_PSS_ANY_SALT(PSA_ALG_SHA_384);
            }
            break;
        case 249:
            {
                *out_value = PSA_ALG_RSA_PSS_ANY_SALT(PSA_ALG_SHA_512);
            }
            break;
        case 250:
            {
                *out_value = PSA_ALG_RSA_PSS_ANY_SALT(PSA_ALG_ANY_HASH);
            }
            break;
        case 251:
            {
                *out_value = PSA_ALG_SHA3_224;
            }
            break;
        case 252:
            {
                *out_value = PSA_ALG_SHA3_256;
            }
            break;
        case 253:
            {
                *out_value = PSA_ALG_SHA3_384;
            }
            break;
        case 254:
            {
                *out_value = PSA_ALG_SHA3_512;
            }
            break;
        case 255:
            {
                *out_value = PSA_ALG_SHAKE256_512;
            }
            break;
        case 256:
            {
                *out_value = PSA_ALG_SHA_1;
            }
            break;
        case 257:
            {
                *out_value = PSA_ALG_SHA_224;
            }
            break;
        case 258:
            {
                *out_value = PSA_ALG_SHA_256;
            }
            break;
        case 259:
            {
                *out_value = PSA_ALG_SHA_384;
            }
            break;
        case 260:
            {
                *out_value = PSA_ALG_SHA_512;
            }
            break;
        case 261:
            {
                *out_value = PSA_ALG_SHA_512_224;
            }
            break;
        case 262:
            {
                *out_value = PSA_ALG_SHA_512_256;
            }
            break;
        case 263:
            {
                *out_value = PSA_ALG_STREAM_CIPHER;
            }
            break;
        case 264:
            {
                *out_value = PSA_ALG_TLS12_ECJPAKE_TO_PMS;
            }
            break;
        case 265:
            {
                *out_value = PSA_ALG_TLS12_PRF(PSA_ALG_MD5);
            }
            break;
        case 266:
            {
                *out_value = PSA_ALG_TLS12_PRF(PSA_ALG_RIPEMD160);
            }
            break;
        case 267:
            {
                *out_value = PSA_ALG_TLS12_PRF(PSA_ALG_SHA3_224);
            }
            break;
        case 268:
            {
                *out_value = PSA_ALG_TLS12_PRF(PSA_ALG_SHA3_256);
            }
            break;
        case 269:
            {
                *out_value = PSA_ALG_TLS12_PRF(PSA_ALG_SHA3_384);
            }
            break;
        case 270:
            {
                *out_value = PSA_ALG_TLS12_PRF(PSA_ALG_SHA3_512);
            }
            break;
        case 271:
            {
                *out_value = PSA_ALG_TLS12_PRF(PSA_ALG_SHA_1);
            }
            break;
        case 272:
            {
                *out_value = PSA_ALG_TLS12_PRF(PSA_ALG_SHA_224);
            }
            break;
        case 273:
            {
                *out_value = PSA_ALG_TLS12_PRF(PSA_ALG_SHA_256);
            }
            break;
        case 274:
            {
                *out_value = PSA_ALG_TLS12_PRF(PSA_ALG_SHA_384);
            }
            break;
        case 275:
            {
                *out_value = PSA_ALG_TLS12_PRF(PSA_ALG_SHA_512);
            }
            break;
        case 276:
            {
                *out_value = PSA_ALG_TLS12_PSK_TO_MS(PSA_ALG_MD5);
            }
            break;
        case 277:
            {
                *out_value = PSA_ALG_TLS12_PSK_TO_MS(PSA_ALG_RIPEMD160);
            }
            break;
        case 278:
            {
                *out_value = PSA_ALG_TLS12_PSK_TO_MS(PSA_ALG_SHA3_224);
            }
            break;
        case 279:
            {
                *out_value = PSA_ALG_TLS12_PSK_TO_MS(PSA_ALG_SHA3_256);
            }
            break;
        case 280:
            {
                *out_value = PSA_ALG_TLS12_PSK_TO_MS(PSA_ALG_SHA3_384);
            }
            break;
        case 281:
            {
                *out_value = PSA_ALG_TLS12_PSK_TO_MS(PSA_ALG_SHA3_512);
            }
            break;
        case 282:
            {
                *out_value = PSA_ALG_TLS12_PSK_TO_MS(PSA_ALG_SHA_1);
            }
            break;
        case 283:
            {
                *out_value = PSA_ALG_TLS12_PSK_TO_MS(PSA_ALG_SHA_224);
            }
            break;
        case 284:
            {
                *out_value = PSA_ALG_TLS12_PSK_TO_MS(PSA_ALG_SHA_256);
            }
            break;
        case 285:
            {
                *out_value = PSA_ALG_TLS12_PSK_TO_MS(PSA_ALG_SHA_384);
            }
            break;
        case 286:
            {
                *out_value = PSA_ALG_TLS12_PSK_TO_MS(PSA_ALG_SHA_512);
            }
            break;
        case 287:
            {
                *out_value = PSA_ALG_TRUNCATED_MAC(PSA_ALG_CBC_MAC,1);
            }
            break;
        case 288:
            {
                *out_value = PSA_ALG_TRUNCATED_MAC(PSA_ALG_CMAC,1);
            }
            break;
        case 289:
            {
                *out_value = PSA_ALG_TRUNCATED_MAC(PSA_ALG_HMAC(PSA_ALG_MD5),1);
            }
            break;
        case 290:
            {
                *out_value = PSA_ALG_TRUNCATED_MAC(PSA_ALG_HMAC(PSA_ALG_RIPEMD160),1);
            }
            break;
        case 291:
            {
                *out_value = PSA_ALG_TRUNCATED_MAC(PSA_ALG_HMAC(PSA_ALG_SHA_1),1);
            }
            break;
        case 292:
            {
                *out_value = PSA_ALG_TRUNCATED_MAC(PSA_ALG_HMAC(PSA_ALG_SHA_224),1);
            }
            break;
        case 293:
            {
                *out_value = PSA_ALG_TRUNCATED_MAC(PSA_ALG_HMAC(PSA_ALG_SHA_256),1);
            }
            break;
        case 294:
            {
                *out_value = PSA_ALG_TRUNCATED_MAC(PSA_ALG_HMAC(PSA_ALG_SHA_384),1);
            }
            break;
        case 295:
            {
                *out_value = PSA_ALG_TRUNCATED_MAC(PSA_ALG_HMAC(PSA_ALG_SHA_512),1);
            }
            break;
        case 296:
            {
                *out_value = PSA_ALG_TRUNCATED_MAC(PSA_ALG_CBC_MAC,4);
            }
            break;
        case 297:
            {
                *out_value = PSA_ALG_TRUNCATED_MAC(PSA_ALG_CBC_MAC,13);
            }
            break;
        case 298:
            {
                *out_value = PSA_ALG_TRUNCATED_MAC(PSA_ALG_CBC_MAC,14);
            }
            break;
        case 299:
            {
                *out_value = PSA_ALG_TRUNCATED_MAC(PSA_ALG_CBC_MAC,16);
            }
            break;
        case 300:
            {
                *out_value = PSA_ALG_TRUNCATED_MAC(PSA_ALG_CBC_MAC,63);
            }
            break;
        case 301:
            {
                *out_value = PSA_ALG_XTS;
            }
            break;
#endif

#line 82 "suites/main_test.function"
        default:
        {
            ret = KEY_VALUE_MAPPING_NOT_FOUND;
        }
        break;
    }
    return ret;
}


/**
 * \brief       Checks if the dependency i.e. the compile flag is set.
 *              For optimizing space for embedded targets each dependency
 *              is identified by a unique identifier instead of string literals.
 *              Identifiers and check code is generated by script:
 *              generate_test_code.py
 *
 * \param dep_id    Dependency identifier.
 *
 * \return       DEPENDENCY_SUPPORTED if set else DEPENDENCY_NOT_SUPPORTED
 */
int dep_check(int dep_id)
{
    int ret = DEPENDENCY_NOT_SUPPORTED;

    (void) dep_id;

    switch (dep_id) {
    
#if defined(MBEDTLS_PSA_CRYPTO_C)

        case 0:
            {
#if defined(PSA_WANT_ALG_CCM)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 1:
            {
#if defined(PSA_WANT_KEY_TYPE_AES)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 2:
            {
#if defined(PSA_WANT_KEY_TYPE_ARIA)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 3:
            {
#if defined(PSA_WANT_KEY_TYPE_CAMELLIA)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 4:
            {
#if defined(PSA_WANT_KEY_TYPE_CHACHA20)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 5:
            {
#if defined(PSA_WANT_KEY_TYPE_DERIVE)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 6:
            {
#if defined(PSA_WANT_KEY_TYPE_DES)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 7:
            {
#if defined(PSA_WANT_KEY_TYPE_DH_KEY_PAIR_BASIC)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 8:
            {
#if defined(PSA_WANT_KEY_TYPE_DH_KEY_PAIR_IMPORT)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 9:
            {
#if defined(PSA_WANT_KEY_TYPE_DH_KEY_PAIR_EXPORT)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 10:
            {
#if defined(PSA_WANT_KEY_TYPE_DH_PUBLIC_KEY)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 11:
            {
#if defined(PSA_WANT_ECC_FAMILY_BRAINPOOL_P_R1)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 12:
            {
#if defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_BASIC)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 13:
            {
#if defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_IMPORT)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 14:
            {
#if defined(PSA_WANT_KEY_TYPE_ECC_KEY_PAIR_EXPORT)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 15:
            {
#if defined(PSA_WANT_ECC_FAMILY_MONTGOMERY)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 16:
            {
#if defined(PSA_WANT_ECC_FAMILY_SECP_K1)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 17:
            {
#if defined(PSA_WANT_ECC_FAMILY_SECP_R1)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 18:
            {
#if defined(PSA_WANT_ECC_FAMILY_SECP_R2)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 19:
            {
#if defined(PSA_WANT_ECC_FAMILY_SECT_K1)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 20:
            {
#if defined(PSA_WANT_ECC_FAMILY_SECT_R1)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 21:
            {
#if defined(PSA_WANT_ECC_FAMILY_SECT_R2)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 22:
            {
#if defined(PSA_WANT_ECC_FAMILY_TWISTED_EDWARDS)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 23:
            {
#if defined(PSA_WANT_KEY_TYPE_ECC_PUBLIC_KEY)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 24:
            {
#if defined(PSA_WANT_KEY_TYPE_HMAC)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 25:
            {
#if defined(PSA_WANT_KEY_TYPE_PASSWORD)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 26:
            {
#if defined(PSA_WANT_KEY_TYPE_PASSWORD_HASH)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 27:
            {
#if defined(PSA_WANT_KEY_TYPE_PEPPER)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 28:
            {
#if defined(PSA_WANT_KEY_TYPE_RAW_DATA)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 29:
            {
#if defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_BASIC)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 30:
            {
#if defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_IMPORT)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 31:
            {
#if defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_EXPORT)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 32:
            {
#if defined(PSA_WANT_KEY_TYPE_RSA_PUBLIC_KEY)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 33:
            {
#if defined(PSA_WANT_ALG_CHACHA20_POLY1305)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 34:
            {
#if defined(PSA_WANT_ALG_GCM)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 35:
            {
#if !defined(PSA_WANT_ALG_CCM)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 36:
            {
#if defined(PSA_WANT_ALG_CBC_MAC)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 37:
            {
#if defined(PSA_WANT_ALG_CMAC)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 38:
            {
#if defined(PSA_WANT_ALG_HMAC)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 39:
            {
#if defined(PSA_WANT_ALG_MD5)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 40:
            {
#if defined(PSA_WANT_ALG_RIPEMD160)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 41:
            {
#if defined(PSA_WANT_ALG_SHA_1)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 42:
            {
#if defined(PSA_WANT_ALG_SHA_224)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 43:
            {
#if defined(PSA_WANT_ALG_SHA_256)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 44:
            {
#if defined(PSA_WANT_ALG_SHA_384)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 45:
            {
#if defined(PSA_WANT_ALG_SHA_512)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 46:
            {
#if !defined(PSA_WANT_ALG_CBC_MAC)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 47:
            {
#if defined(PSA_WANT_ALG_CBC_NO_PADDING)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 48:
            {
#if !defined(PSA_WANT_ALG_CBC_NO_PADDING)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 49:
            {
#if defined(PSA_WANT_ALG_CBC_PKCS7)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 50:
            {
#if !defined(PSA_WANT_ALG_CBC_PKCS7)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 51:
            {
#if defined(PSA_WANT_ALG_CCM_STAR_NO_TAG)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 52:
            {
#if !defined(PSA_WANT_ALG_CCM_STAR_NO_TAG)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 53:
            {
#if defined(PSA_WANT_ALG_CFB)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 54:
            {
#if !defined(PSA_WANT_ALG_CFB)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 55:
            {
#if !defined(PSA_WANT_ALG_CHACHA20_POLY1305)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 56:
            {
#if !defined(PSA_WANT_ALG_CMAC)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 57:
            {
#if defined(PSA_WANT_ALG_CTR)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 58:
            {
#if !defined(PSA_WANT_ALG_CTR)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 59:
            {
#if defined(PSA_WANT_ALG_DETERMINISTIC_DSA)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 60:
            {
#if defined(PSA_WANT_ALG_SHA3_224)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 61:
            {
#if defined(PSA_WANT_ALG_SHA3_256)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 62:
            {
#if defined(PSA_WANT_ALG_SHA3_384)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 63:
            {
#if defined(PSA_WANT_ALG_SHA3_512)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 64:
            {
#if defined(PSA_WANT_ALG_DETERMINISTIC_ECDSA)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 65:
            {
#if !defined(PSA_WANT_ALG_DETERMINISTIC_ECDSA)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 66:
            {
#if !defined(PSA_WANT_ALG_MD5)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 67:
            {
#if !defined(PSA_WANT_ALG_RIPEMD160)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 68:
            {
#if !defined(PSA_WANT_ALG_SHA3_224)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 69:
            {
#if !defined(PSA_WANT_ALG_SHA3_256)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 70:
            {
#if !defined(PSA_WANT_ALG_SHA3_384)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 71:
            {
#if !defined(PSA_WANT_ALG_SHA3_512)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 72:
            {
#if !defined(PSA_WANT_ALG_SHA_1)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 73:
            {
#if !defined(PSA_WANT_ALG_SHA_224)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 74:
            {
#if !defined(PSA_WANT_ALG_SHA_256)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 75:
            {
#if !defined(PSA_WANT_ALG_SHA_384)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 76:
            {
#if !defined(PSA_WANT_ALG_SHA_512)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 77:
            {
#if defined(PSA_WANT_ALG_DSA)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 78:
            {
#if defined(PSA_WANT_ALG_ECB_NO_PADDING)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 79:
            {
#if !defined(PSA_WANT_ALG_ECB_NO_PADDING)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 80:
            {
#if defined(PSA_WANT_ALG_ECDH)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 81:
            {
#if !defined(PSA_WANT_ALG_ECDH)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 82:
            {
#if defined(PSA_WANT_ALG_ECDSA)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 83:
            {
#if !defined(PSA_WANT_ALG_ECDSA)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 84:
            {
#if defined(PSA_WANT_ALG_ECDSA_ANY)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 85:
            {
#if !defined(PSA_WANT_ALG_ECDSA_ANY)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 86:
            {
#if defined(PSA_WANT_ALG_ED25519PH)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 87:
            {
#if !defined(PSA_WANT_ALG_ED25519PH)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 88:
            {
#if defined(PSA_WANT_ALG_ED448PH)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 89:
            {
#if !defined(PSA_WANT_ALG_ED448PH)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 90:
            {
#if defined(PSA_WANT_ALG_FFDH)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 91:
            {
#if !defined(PSA_WANT_ALG_FFDH)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 92:
            {
#if !defined(PSA_WANT_ALG_GCM)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 93:
            {
#if defined(PSA_WANT_ALG_HKDF)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 94:
            {
#if !defined(PSA_WANT_ALG_HKDF)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 95:
            {
#if defined(PSA_WANT_ALG_HKDF_EXPAND)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 96:
            {
#if !defined(PSA_WANT_ALG_HKDF_EXPAND)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 97:
            {
#if defined(PSA_WANT_ALG_HKDF_EXTRACT)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 98:
            {
#if !defined(PSA_WANT_ALG_HKDF_EXTRACT)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 99:
            {
#if !defined(PSA_WANT_ALG_HMAC)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 100:
            {
#if defined(PSA_WANT_ALG_JPAKE)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 101:
            {
#if defined(PSA_WANT_ALG_TLS12_ECJPAKE_TO_PMS)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 102:
            {
#if defined(PSA_WANT_ALG_TLS12_PRF)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 103:
            {
#if !defined(PSA_WANT_ALG_TLS12_PRF)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 104:
            {
#if defined(PSA_WANT_ALG_TLS12_PSK_TO_MS)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 105:
            {
#if !defined(PSA_WANT_ALG_TLS12_PSK_TO_MS)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 106:
            {
#if defined(PSA_WANT_ALG_OFB)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 107:
            {
#if !defined(PSA_WANT_ALG_OFB)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 108:
            {
#if defined(PSA_WANT_ALG_PBKDF2_AES_CMAC_PRF_128)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 109:
            {
#if !defined(PSA_WANT_ALG_PBKDF2_AES_CMAC_PRF_128)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 110:
            {
#if defined(PSA_WANT_ALG_PBKDF2_HMAC)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 111:
            {
#if !defined(PSA_WANT_ALG_PBKDF2_HMAC)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 112:
            {
#if defined(PSA_WANT_ALG_PURE_EDDSA)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 113:
            {
#if !defined(PSA_WANT_ALG_PURE_EDDSA)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 114:
            {
#if defined(PSA_WANT_ALG_RSA_OAEP)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 115:
            {
#if !defined(PSA_WANT_ALG_RSA_OAEP)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 116:
            {
#if defined(PSA_WANT_ALG_RSA_PKCS1V15_CRYPT)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 117:
            {
#if !defined(PSA_WANT_ALG_RSA_PKCS1V15_CRYPT)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 118:
            {
#if defined(PSA_WANT_ALG_RSA_PKCS1V15_SIGN)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 119:
            {
#if !defined(PSA_WANT_ALG_RSA_PKCS1V15_SIGN)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 120:
            {
#if defined(PSA_WANT_ALG_RSA_PKCS1V15_SIGN_RAW)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 121:
            {
#if !defined(PSA_WANT_ALG_RSA_PKCS1V15_SIGN_RAW)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 122:
            {
#if defined(PSA_WANT_ALG_RSA_PSS)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 123:
            {
#if !defined(PSA_WANT_ALG_RSA_PSS)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 124:
            {
#if defined(PSA_WANT_ALG_RSA_PSS_ANY_SALT)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 125:
            {
#if !defined(PSA_WANT_ALG_RSA_PSS_ANY_SALT)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 126:
            {
#if !defined(PSA_WANT_ALG_SHAKE256_512)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 127:
            {
#if defined(PSA_WANT_ALG_SHAKE256_512)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 128:
            {
#if !defined(PSA_WANT_ALG_SHA_512_224)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 129:
            {
#if defined(PSA_WANT_ALG_SHA_512_224)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 130:
            {
#if !defined(PSA_WANT_ALG_SHA_512_256)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 131:
            {
#if defined(PSA_WANT_ALG_SHA_512_256)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 132:
            {
#if defined(PSA_WANT_ALG_STREAM_CIPHER)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 133:
            {
#if !defined(PSA_WANT_ALG_STREAM_CIPHER)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 134:
            {
#if !defined(PSA_WANT_ALG_TLS12_ECJPAKE_TO_PMS)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 135:
            {
#if defined(PSA_WANT_ALG_XTS)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
        case 136:
            {
#if !defined(PSA_WANT_ALG_XTS)
                ret = DEPENDENCY_SUPPORTED;
#else
                ret = DEPENDENCY_NOT_SUPPORTED;
#endif
            }
            break;
#endif

#line 112 "suites/main_test.function"
        default:
            break;
    }
    return ret;
}


/**
 * \brief       Function pointer type for test function wrappers.
 *
 * A test function wrapper decodes the parameters and passes them to the
 * underlying test function. Both the wrapper and the underlying function
 * return void. Test wrappers assume that they are passed a suitable
 * parameter array and do not perform any error detection.
 *
 * \param param_array   The array of parameters. Each element is a `void *`
 *                      which the wrapper casts to the correct type and
 *                      dereferences. Each wrapper function hard-codes the
 *                      number and types of the parameters.
 */
typedef void (*TestWrapper_t)(void **param_array);


/**
 * \brief       Table of test function wrappers. Used by dispatch_test().
 *              This table is populated by script:
 *              generate_test_code.py
 *
 */
TestWrapper_t test_funcs[] =
{
    /* Function Id: 0 */

#if defined(MBEDTLS_PSA_CRYPTO_C)
    test_hash_fail_wrapper,
#else
    NULL,
#endif
/* Function Id: 1 */

#if defined(MBEDTLS_PSA_CRYPTO_C)
    test_mac_fail_wrapper,
#else
    NULL,
#endif
/* Function Id: 2 */

#if defined(MBEDTLS_PSA_CRYPTO_C)
    test_cipher_fail_wrapper,
#else
    NULL,
#endif
/* Function Id: 3 */

#if defined(MBEDTLS_PSA_CRYPTO_C)
    test_aead_fail_wrapper,
#else
    NULL,
#endif
/* Function Id: 4 */

#if defined(MBEDTLS_PSA_CRYPTO_C)
    test_sign_fail_wrapper,
#else
    NULL,
#endif
/* Function Id: 5 */

#if defined(MBEDTLS_PSA_CRYPTO_C)
    test_asymmetric_encryption_fail_wrapper,
#else
    NULL,
#endif
/* Function Id: 6 */

#if defined(MBEDTLS_PSA_CRYPTO_C)
    test_key_derivation_fail_wrapper,
#else
    NULL,
#endif
/* Function Id: 7 */

#if defined(MBEDTLS_PSA_CRYPTO_C)
    test_key_agreement_fail_wrapper,
#else
    NULL,
#endif

#line 145 "suites/main_test.function"
};

/**
 * \brief        Dispatches test functions based on function index.
 *
 * \param func_idx    Test function index.
 * \param params      The array of parameters to pass to the test function.
 *                    It will be decoded by the #TestWrapper_t wrapper function.
 *
 * \return       DISPATCH_TEST_SUCCESS if found
 *               DISPATCH_TEST_FN_NOT_FOUND if not found
 *               DISPATCH_UNSUPPORTED_SUITE if not compile time enabled.
 */
int dispatch_test(size_t func_idx, void **params)
{
    int ret = DISPATCH_TEST_SUCCESS;
    TestWrapper_t fp = NULL;

    if (func_idx < (int) (sizeof(test_funcs) / sizeof(TestWrapper_t))) {
        fp = test_funcs[func_idx];
        if (fp) {
            #if defined(MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG)
            mbedtls_test_enable_insecure_external_rng();
            #endif

            fp(params);

            #if defined(MBEDTLS_TEST_MUTEX_USAGE)
            mbedtls_test_mutex_usage_check();
            #endif /* MBEDTLS_TEST_MUTEX_USAGE */
        } else {
            ret = DISPATCH_UNSUPPORTED_SUITE;
        }
    } else {
        ret = DISPATCH_TEST_FN_NOT_FOUND;
    }

    return ret;
}


/**
 * \brief       Checks if test function is supported in this build-time
 *              configuration.
 *
 * \param func_idx    Test function index.
 *
 * \return       DISPATCH_TEST_SUCCESS if found
 *               DISPATCH_TEST_FN_NOT_FOUND if not found
 *               DISPATCH_UNSUPPORTED_SUITE if not compile time enabled.
 */
int check_test(size_t func_idx)
{
    int ret = DISPATCH_TEST_SUCCESS;
    TestWrapper_t fp = NULL;

    if (func_idx < (int) (sizeof(test_funcs)/sizeof(TestWrapper_t))) {
        fp = test_funcs[func_idx];
        if (fp == NULL) {
            ret = DISPATCH_UNSUPPORTED_SUITE;
        }
    } else {
        ret = DISPATCH_TEST_FN_NOT_FOUND;
    }

    return ret;
}


#line 2 "suites/host_test.function"

/**
 * \brief       Verifies that string is in string parameter format i.e. "<str>"
 *              It also strips enclosing '"' from the input string.
 *
 * \param str   String parameter.
 *
 * \return      0 if success else 1
 */
int verify_string(char **str)
{
    if ((*str)[0] != '"' ||
        (*str)[strlen(*str) - 1] != '"') {
        mbedtls_fprintf(stderr,
                        "Expected string (with \"\") for parameter and got: %s\n", *str);
        return -1;
    }

    (*str)++;
    (*str)[strlen(*str) - 1] = '\0';

    return 0;
}

/**
 * \brief       Verifies that string is an integer. Also gives the converted
 *              integer value.
 *
 * \param str   Input string.
 * \param p_value Pointer to output value.
 *
 * \return      0 if success else 1
 */
int verify_int(char *str, intmax_t *p_value)
{
    char *end = NULL;
    errno = 0;
    /* Limit the range to long: for large integers, the test framework will
     * use expressions anyway. */
    long value = strtol(str, &end, 0);
    if (errno == EINVAL || *end != '\0') {
        mbedtls_fprintf(stderr,
                        "Expected integer for parameter and got: %s\n", str);
        return KEY_VALUE_MAPPING_NOT_FOUND;
    }
    if (errno == ERANGE) {
        mbedtls_fprintf(stderr, "Integer out of range: %s\n", str);
        return KEY_VALUE_MAPPING_NOT_FOUND;
    }
    *p_value = value;
    return 0;
}


/**
 * \brief       Usage string.
 *
 */
#define USAGE \
    "Usage: %s [OPTIONS] files...\n\n" \
    "   Command line arguments:\n" \
    "     files...          One or more test data files. If no file is\n" \
    "                       specified the following default test case\n" \
    "                       file is used:\n" \
    "                           %s\n\n" \
    "   Options:\n" \
    "     -v | --verbose    Display full information about each test\n" \
    "     -h | --help       Display this information\n\n", \
    argv[0], \
    "TESTCASE_FILENAME"


/**
 * \brief       Read a line from the passed file pointer.
 *
 * \param f     FILE pointer
 * \param buf   Pointer to memory to hold read line.
 * \param len   Length of the buf.
 *
 * \return      0 if success else -1
 */
int get_line(FILE *f, char *buf, size_t len)
{
    char *ret;
    int i = 0, str_len = 0, has_string = 0;

    /* Read until we get a valid line */
    do {
        ret = fgets(buf, len, f);
        if (ret == NULL) {
            return -1;
        }

        str_len = strlen(buf);

        /* Skip empty line and comment */
        if (str_len == 0 || buf[0] == '#') {
            continue;
        }
        has_string = 0;
        for (i = 0; i < str_len; i++) {
            char c = buf[i];
            if (c != ' ' && c != '\t' && c != '\n' &&
                c != '\v' && c != '\f' && c != '\r') {
                has_string = 1;
                break;
            }
        }
    } while (!has_string);

    /* Strip new line and carriage return */
    ret = buf + strlen(buf);
    if (ret-- > buf && *ret == '\n') {
        *ret = '\0';
    }
    if (ret-- > buf && *ret == '\r') {
        *ret = '\0';
    }

    return 0;
}

/**
 * \brief       Splits string delimited by ':'. Ignores '\:'.
 *
 * \param buf           Input string
 * \param len           Input string length
 * \param params        Out params found
 * \param params_len    Out params array len
 *
 * \return      Count of strings found.
 */
static int parse_arguments(char *buf, size_t len, char **params,
                           size_t params_len)
{
    size_t cnt = 0, i;
    char *cur = buf;
    char *p = buf, *q;

    params[cnt++] = cur;

    while (*p != '\0' && p < (buf + len)) {
        if (*p == '\\') {
            p++;
            p++;
            continue;
        }
        if (*p == ':') {
            if (p + 1 < buf + len) {
                cur = p + 1;
                TEST_HELPER_ASSERT(cnt < params_len);
                params[cnt++] = cur;
            }
            *p = '\0';
        }

        p++;
    }

    /* Replace backslash escapes in strings */
    for (i = 0; i < cnt; i++) {
        p = params[i];
        q = params[i];

        while (*p != '\0') {
            if (*p == '\\') {
                ++p;
                switch (*p) {
                    case 'n':
                        *p = '\n';
                        break;
                    default:
                        // Fall through to copying *p
                        break;
                }
            }
            *(q++) = *(p++);
        }
        *q = '\0';
    }

    return cnt;
}

/**
 * \brief       Converts parameters into test function consumable parameters.
 *              Example: Input:  {"int", "0", "char*", "Hello",
 *                                "hex", "abef", "exp", "1"}
 *                      Output:  {
 *                                0,                // Verified int
 *                                "Hello",          // Verified string
 *                                2, { 0xab, 0xef },// Converted len,hex pair
 *                                9600              // Evaluated expression
 *                               }
 *
 *
 * \param cnt               Parameter array count.
 * \param params            Out array of found parameters.
 * \param int_params_store  Memory for storing processed integer parameters.
 *
 * \return      0 for success else 1
 */
static int convert_params(size_t cnt, char **params,
                          mbedtls_test_argument_t *int_params_store)
{
    char **cur = params;
    char **out = params;
    int ret = DISPATCH_TEST_SUCCESS;

    while (cur < params + cnt) {
        char *type = *cur++;
        char *val = *cur++;

        if (strcmp(type, "char*") == 0) {
            if (verify_string(&val) == 0) {
                *out++ = val;
            } else {
                ret = (DISPATCH_INVALID_TEST_DATA);
                break;
            }
        } else if (strcmp(type, "int") == 0) {
            if (verify_int(val, &int_params_store->sint) == 0) {
                *out++ = (char *) int_params_store++;
            } else {
                ret = (DISPATCH_INVALID_TEST_DATA);
                break;
            }
        } else if (strcmp(type, "hex") == 0) {
            if (verify_string(&val) == 0) {
                size_t len;

                TEST_HELPER_ASSERT(
                    mbedtls_test_unhexify((unsigned char *) val, strlen(val),
                                          val, &len) == 0);

                int_params_store->len = len;
                *out++ = val;
                *out++ = (char *) (int_params_store++);
            } else {
                ret = (DISPATCH_INVALID_TEST_DATA);
                break;
            }
        } else if (strcmp(type, "exp") == 0) {
            int exp_id = strtol(val, NULL, 10);
            if (get_expression(exp_id, &int_params_store->sint) == 0) {
                *out++ = (char *) int_params_store++;
            } else {
                ret = (DISPATCH_INVALID_TEST_DATA);
                break;
            }
        } else {
            ret = (DISPATCH_INVALID_TEST_DATA);
            break;
        }
    }
    return ret;
}

/**
 * \brief       Tests snprintf implementation with test input.
 *
 * \note
 * At high optimization levels (e.g. gcc -O3), this function may be
 * inlined in run_test_snprintf. This can trigger a spurious warning about
 * potential misuse of snprintf from gcc -Wformat-truncation (observed with
 * gcc 7.2). This warning makes tests in run_test_snprintf redundant on gcc
 * only. They are still valid for other compilers. Avoid this warning by
 * forbidding inlining of this function by gcc.
 *
 * \param n         Buffer test length.
 * \param ref_buf   Expected buffer.
 * \param ref_ret   Expected snprintf return value.
 *
 * \return      0 for success else 1
 */
#if defined(__GNUC__)
__attribute__((__noinline__))
#endif
static int test_snprintf(size_t n, const char *ref_buf, int ref_ret)
{
    int ret;
    char buf[10] = "xxxxxxxxx";
    const char ref[10] = "xxxxxxxxx";

    if (n >= sizeof(buf)) {
        return -1;
    }
    ret = mbedtls_snprintf(buf, n, "%s", "123");
    if (ret < 0 || (size_t) ret >= n) {
        ret = -1;
    }

    if (strncmp(ref_buf, buf, sizeof(buf)) != 0 ||
        ref_ret != ret ||
        memcmp(buf + n, ref + n, sizeof(buf) - n) != 0) {
        return 1;
    }

    return 0;
}

/**
 * \brief       Tests snprintf implementation.
 *
 * \return      0 for success else 1
 */
static int run_test_snprintf(void)
{
    return test_snprintf(0, "xxxxxxxxx",  -1) != 0 ||
           test_snprintf(1, "",           -1) != 0 ||
           test_snprintf(2, "1",          -1) != 0 ||
           test_snprintf(3, "12",         -1) != 0 ||
           test_snprintf(4, "123",         3) != 0 ||
           test_snprintf(5, "123",         3) != 0;
}

/** \brief Write the description of the test case to the outcome CSV file.
 *
 * \param outcome_file  The file to write to.
 *                      If this is \c NULL, this function does nothing.
 * \param argv0         The test suite name.
 * \param test_case     The test case description.
 */
static void write_outcome_entry(FILE *outcome_file,
                                const char *argv0,
                                const char *test_case)
{
    /* The non-varying fields are initialized on first use. */
    static const char *platform = NULL;
    static const char *configuration = NULL;
    static const char *test_suite = NULL;

    if (outcome_file == NULL) {
        return;
    }

    if (platform == NULL) {
        platform = getenv("MBEDTLS_TEST_PLATFORM");
        if (platform == NULL) {
            platform = "unknown";
        }
    }
    if (configuration == NULL) {
        configuration = getenv("MBEDTLS_TEST_CONFIGURATION");
        if (configuration == NULL) {
            configuration = "unknown";
        }
    }
    if (test_suite == NULL) {
        test_suite = strrchr(argv0, '/');
        if (test_suite != NULL) {
            test_suite += 1; // skip the '/'
        } else {
            test_suite = argv0;
        }
    }

    /* Write the beginning of the outcome line.
     * Ignore errors: writing the outcome file is on a best-effort basis. */
    mbedtls_fprintf(outcome_file, "%s;%s;%s;%s;",
                    platform, configuration, test_suite, test_case);
}

/** \brief Write the result of the test case to the outcome CSV file.
 *
 * \param outcome_file  The file to write to.
 *                      If this is \c NULL, this function does nothing.
 * \param unmet_dep_count            The number of unmet dependencies.
 * \param unmet_dependencies         The array of unmet dependencies.
 * \param missing_unmet_dependencies Non-zero if there was a problem tracking
 *                                   all unmet dependencies, 0 otherwise.
 * \param ret                        The test dispatch status (DISPATCH_xxx).
 * \param info                       A pointer to the test info structure.
 */
static void write_outcome_result(FILE *outcome_file,
                                 size_t unmet_dep_count,
                                 int unmet_dependencies[],
                                 int missing_unmet_dependencies,
                                 int ret,
                                 const mbedtls_test_info_t *info)
{
    if (outcome_file == NULL) {
        return;
    }

    /* Write the end of the outcome line.
     * Ignore errors: writing the outcome file is on a best-effort basis. */
    switch (ret) {
        case DISPATCH_TEST_SUCCESS:
            if (unmet_dep_count > 0) {
                size_t i;
                mbedtls_fprintf(outcome_file, "SKIP");
                for (i = 0; i < unmet_dep_count; i++) {
                    mbedtls_fprintf(outcome_file, "%c%d",
                                    i == 0 ? ';' : ':',
                                    unmet_dependencies[i]);
                }
                if (missing_unmet_dependencies) {
                    mbedtls_fprintf(outcome_file, ":...");
                }
                break;
            }
            switch (info->result) {
                case MBEDTLS_TEST_RESULT_SUCCESS:
                    mbedtls_fprintf(outcome_file, "PASS;");
                    break;
                case MBEDTLS_TEST_RESULT_SKIPPED:
                    mbedtls_fprintf(outcome_file, "SKIP;Runtime skip");
                    break;
                default:
                    mbedtls_fprintf(outcome_file, "FAIL;%s:%d:%s",
                                    info->filename, info->line_no,
                                    info->test);
                    break;
            }
            break;
        case DISPATCH_TEST_FN_NOT_FOUND:
            mbedtls_fprintf(outcome_file, "FAIL;Test function not found");
            break;
        case DISPATCH_INVALID_TEST_DATA:
            mbedtls_fprintf(outcome_file, "FAIL;Invalid test data");
            break;
        case DISPATCH_UNSUPPORTED_SUITE:
            mbedtls_fprintf(outcome_file, "SKIP;Unsupported suite");
            break;
        default:
            mbedtls_fprintf(outcome_file, "FAIL;Unknown cause");
            break;
    }
    mbedtls_fprintf(outcome_file, "\n");
    fflush(outcome_file);
}

/**
 * \brief       Desktop implementation of execute_tests().
 *              Parses command line and executes tests from
 *              supplied or default data file.
 *
 * \param argc  Command line argument count.
 * \param argv  Argument array.
 *
 * \return      Program exit status.
 */
int execute_tests(int argc, const char **argv)
{
    /* Local Configurations and options */
    const char *default_filename = "./test_suite_psa_crypto_op_fail.generated.datax";
    const char *test_filename = NULL;
    const char **test_files = NULL;
    size_t testfile_count = 0;
    int option_verbose = 0;
    size_t function_id = 0;

    /* Other Local variables */
    int arg_index = 1;
    const char *next_arg;
    size_t testfile_index, i, cnt;
    int ret;
    unsigned total_errors = 0, total_tests = 0, total_skipped = 0;
    FILE *file;
    char buf[5000];
    char *params[50];
    /* Store for processed integer params. */
    mbedtls_test_argument_t int_params[50];
    void *pointer;
#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
    int stdout_fd = -1;
#endif /* __unix__ || __APPLE__ __MACH__ */
    const char *outcome_file_name = getenv("MBEDTLS_TEST_OUTCOME_FILE");
    FILE *outcome_file = NULL;

#if defined(MBEDTLS_MEMORY_BUFFER_ALLOC_C) && \
    !defined(TEST_SUITE_MEMORY_BUFFER_ALLOC)
    unsigned char alloc_buf[1000000];
    mbedtls_memory_buffer_alloc_init(alloc_buf, sizeof(alloc_buf));
#endif

#if defined(MBEDTLS_TEST_MUTEX_USAGE)
    mbedtls_test_mutex_usage_init();
#endif

    /*
     * The C standard doesn't guarantee that all-bits-0 is the representation
     * of a NULL pointer. We do however use that in our code for initializing
     * structures, which should work on every modern platform. Let's be sure.
     */
    memset(&pointer, 0, sizeof(void *));
    if (pointer != NULL) {
        mbedtls_fprintf(stderr, "all-bits-zero is not a NULL pointer\n");
        return 1;
    }

    /*
     * Make sure we have a snprintf that correctly zero-terminates
     */
    if (run_test_snprintf() != 0) {
        mbedtls_fprintf(stderr, "the snprintf implementation is broken\n");
        return 1;
    }

    if (outcome_file_name != NULL && *outcome_file_name != '\0') {
        outcome_file = fopen(outcome_file_name, "a");
        if (outcome_file == NULL) {
            mbedtls_fprintf(stderr, "Unable to open outcome file. Continuing anyway.\n");
        }
    }

    while (arg_index < argc) {
        next_arg = argv[arg_index];

        if (strcmp(next_arg, "--verbose") == 0 ||
            strcmp(next_arg, "-v") == 0) {
            option_verbose = 1;
        } else if (strcmp(next_arg, "--help") == 0 ||
                   strcmp(next_arg, "-h") == 0) {
            mbedtls_fprintf(stdout, USAGE);
            mbedtls_exit(EXIT_SUCCESS);
        } else {
            /* Not an option, therefore treat all further arguments as the file
             * list.
             */
            test_files = &argv[arg_index];
            testfile_count = argc - arg_index;
            break;
        }

        arg_index++;
    }

    /* If no files were specified, assume a default */
    if (test_files == NULL || testfile_count == 0) {
        test_files = &default_filename;
        testfile_count = 1;
    }

    /* Initialize the struct that holds information about the last test */
    mbedtls_test_info_reset();

    /* Now begin to execute the tests in the testfiles */
    for (testfile_index = 0;
         testfile_index < testfile_count;
         testfile_index++) {
        size_t unmet_dep_count = 0;
        int unmet_dependencies[20];
        int missing_unmet_dependencies = 0;

        test_filename = test_files[testfile_index];

        file = fopen(test_filename, "r");
        if (file == NULL) {
            mbedtls_fprintf(stderr, "Failed to open test file: %s\n",
                            test_filename);
            if (outcome_file != NULL) {
                fclose(outcome_file);
            }
            return 1;
        }

        while (!feof(file)) {
            if (unmet_dep_count > 0) {
                mbedtls_fprintf(stderr,
                                "FATAL: Dep count larger than zero at start of loop\n");
                mbedtls_exit(MBEDTLS_EXIT_FAILURE);
            }
            unmet_dep_count = 0;
            missing_unmet_dependencies = 0;

            if ((ret = get_line(file, buf, sizeof(buf))) != 0) {
                break;
            }
            mbedtls_fprintf(stdout, "%s%.66s",
                            mbedtls_test_info.result == MBEDTLS_TEST_RESULT_FAILED ?
                            "\n" : "", buf);
            mbedtls_fprintf(stdout, " ");
            for (i = strlen(buf) + 1; i < 67; i++) {
                mbedtls_fprintf(stdout, ".");
            }
            mbedtls_fprintf(stdout, " ");
            fflush(stdout);
            write_outcome_entry(outcome_file, argv[0], buf);

            total_tests++;

            if ((ret = get_line(file, buf, sizeof(buf))) != 0) {
                break;
            }
            cnt = parse_arguments(buf, strlen(buf), params,
                                  sizeof(params) / sizeof(params[0]));

            if (strcmp(params[0], "depends_on") == 0) {
                for (i = 1; i < cnt; i++) {
                    int dep_id = strtol(params[i], NULL, 10);
                    if (dep_check(dep_id) != DEPENDENCY_SUPPORTED) {
                        if (unmet_dep_count <
                            ARRAY_LENGTH(unmet_dependencies)) {
                            unmet_dependencies[unmet_dep_count] = dep_id;
                            unmet_dep_count++;
                        } else {
                            missing_unmet_dependencies = 1;
                        }
                    }
                }

                if ((ret = get_line(file, buf, sizeof(buf))) != 0) {
                    break;
                }
                cnt = parse_arguments(buf, strlen(buf), params,
                                      sizeof(params) / sizeof(params[0]));
            }

            // If there are no unmet dependencies execute the test
            if (unmet_dep_count == 0) {
                mbedtls_test_info_reset();

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
                /* Suppress all output from the library unless we're verbose
                 * mode
                 */
                if (!option_verbose) {
                    stdout_fd = redirect_output(stdout, "/dev/null");
                    if (stdout_fd == -1) {
                        /* Redirection has failed with no stdout so exit */
                        exit(1);
                    }
                }
#endif /* __unix__ || __APPLE__ __MACH__ */

                function_id = strtoul(params[0], NULL, 10);
                if ((ret = check_test(function_id)) == DISPATCH_TEST_SUCCESS) {
                    ret = convert_params(cnt - 1, params + 1, int_params);
                    if (DISPATCH_TEST_SUCCESS == ret) {
                        ret = dispatch_test(function_id, (void **) (params + 1));
                    }
                }

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
                if (!option_verbose && restore_output(stdout, stdout_fd)) {
                    /* Redirection has failed with no stdout so exit */
                    exit(1);
                }
#endif /* __unix__ || __APPLE__ __MACH__ */

            }

            write_outcome_result(outcome_file,
                                 unmet_dep_count, unmet_dependencies,
                                 missing_unmet_dependencies,
                                 ret, &mbedtls_test_info);
            if (unmet_dep_count > 0 || ret == DISPATCH_UNSUPPORTED_SUITE) {
                total_skipped++;
                mbedtls_fprintf(stdout, "----");

                if (1 == option_verbose && ret == DISPATCH_UNSUPPORTED_SUITE) {
                    mbedtls_fprintf(stdout, "\n   Test Suite not enabled");
                }

                if (1 == option_verbose && unmet_dep_count > 0) {
                    mbedtls_fprintf(stdout, "\n   Unmet dependencies: ");
                    for (i = 0; i < unmet_dep_count; i++) {
                        mbedtls_fprintf(stdout, "%d ",
                                        unmet_dependencies[i]);
                    }
                    if (missing_unmet_dependencies) {
                        mbedtls_fprintf(stdout, "...");
                    }
                }
                mbedtls_fprintf(stdout, "\n");
                fflush(stdout);

                unmet_dep_count = 0;
                missing_unmet_dependencies = 0;
            } else if (ret == DISPATCH_TEST_SUCCESS) {
                if (mbedtls_test_info.result == MBEDTLS_TEST_RESULT_SUCCESS) {
                    mbedtls_fprintf(stdout, "PASS\n");
                } else if (mbedtls_test_info.result == MBEDTLS_TEST_RESULT_SKIPPED) {
                    mbedtls_fprintf(stdout, "----\n");
                    total_skipped++;
                } else {
                    total_errors++;
                    mbedtls_fprintf(stdout, "FAILED\n");
                    mbedtls_fprintf(stdout, "  %s\n  at ",
                                    mbedtls_test_info.test);
                    if (mbedtls_test_info.step != (unsigned long) (-1)) {
                        mbedtls_fprintf(stdout, "step %lu, ",
                                        mbedtls_test_info.step);
                    }
                    mbedtls_fprintf(stdout, "line %d, %s",
                                    mbedtls_test_info.line_no,
                                    mbedtls_test_info.filename);
                    if (mbedtls_test_info.line1[0] != 0) {
                        mbedtls_fprintf(stdout, "\n  %s",
                                        mbedtls_test_info.line1);
                    }
                    if (mbedtls_test_info.line2[0] != 0) {
                        mbedtls_fprintf(stdout, "\n  %s",
                                        mbedtls_test_info.line2);
                    }
                }
                fflush(stdout);
            } else if (ret == DISPATCH_INVALID_TEST_DATA) {
                mbedtls_fprintf(stderr, "FAILED: FATAL PARSE ERROR\n");
                fclose(file);
                mbedtls_exit(2);
            } else if (ret == DISPATCH_TEST_FN_NOT_FOUND) {
                mbedtls_fprintf(stderr, "FAILED: FATAL TEST FUNCTION NOT FOUND\n");
                fclose(file);
                mbedtls_exit(2);
            } else {
                total_errors++;
            }
        }
        fclose(file);
    }

    if (outcome_file != NULL) {
        fclose(outcome_file);
    }

    mbedtls_fprintf(stdout,
                    "\n----------------------------------------------------------------------------\n\n");
    if (total_errors == 0) {
        mbedtls_fprintf(stdout, "PASSED");
    } else {
        mbedtls_fprintf(stdout, "FAILED");
    }

    mbedtls_fprintf(stdout, " (%u / %u tests (%u skipped))\n",
                    total_tests - total_errors, total_tests, total_skipped);

#if defined(MBEDTLS_MEMORY_BUFFER_ALLOC_C) && \
    !defined(TEST_SUITE_MEMORY_BUFFER_ALLOC)
#if defined(MBEDTLS_MEMORY_DEBUG)
    mbedtls_memory_buffer_alloc_status();
#endif
    mbedtls_memory_buffer_alloc_free();
#endif

    return total_errors != 0;
}


#line 217 "suites/main_test.function"

/*----------------------------------------------------------------------------*/
/* Main Test code */


/**
 * \brief       Program main. Invokes platform specific execute_tests().
 *
 * \param argc      Command line arguments count.
 * \param argv      Array of command line arguments.
 *
 * \return       Exit code.
 */
int main(int argc, const char *argv[])
{
#if defined(MBEDTLS_TEST_HOOKS)
    extern void (*mbedtls_test_hook_test_fail)(const char *test, int line, const char *file);
    mbedtls_test_hook_test_fail = &mbedtls_test_fail;
#if defined(MBEDTLS_ERROR_C)
    mbedtls_test_hook_error_add = &mbedtls_test_err_add_check;
#endif
#endif

    int ret = mbedtls_test_platform_setup();
    if (ret != 0) {
        mbedtls_fprintf(stderr,
                        "FATAL: Failed to initialize platform - error %d\n",
                        ret);
        return -1;
    }

    ret = execute_tests(argc, argv);
    mbedtls_test_platform_teardown();
    return ret;
}
