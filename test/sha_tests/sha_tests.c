//
// Created by ian on 4/26/2016.
//

#include <unity.h>

#include "portable_sha256.h"

sha256_ctx g_ctx;

void setUp(void)
{
    sha256_init(&g_ctx);
}

void tearDown(void)
{
    sha256_init(&g_ctx);
}

void test_sha256_zero_message(void)
{
    char *exp_hex = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";
    uint8_t exp[32];
    hex_to_buf(exp_hex, exp);

    uint8_t actual[32];
    sha256_final(actual, &g_ctx);

    TEST_ASSERT_EQUAL_HEX8_ARRAY(exp, actual, 32);
}

void test_sha256_01(void)
{
    char *exp_hex = "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad";
    uint8_t exp[32];
    hex_to_buf(exp_hex, exp);
    char message[] = "abc";

    sha256_update(message, strlen(message), &g_ctx);

    uint8_t actual[32];
    sha256_final(actual, &g_ctx);

    TEST_ASSERT_EQUAL_HEX8_ARRAY(exp, actual, 32);
}

void test_sha256_02(void)
{
    char *exp_hex = "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1";
    uint8_t exp[32];
    hex_to_buf(exp_hex, exp);
    char message[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";

    sha256_update(message, strlen(message), &g_ctx);

    uint8_t actual[32];
    sha256_final(actual, &g_ctx);

    TEST_ASSERT_EQUAL_HEX8_ARRAY(exp, actual, 32);
}

void test_sha256_03(void)
{
    char *exp_hex = "cf5b16a778af8380036ce59e7b0492370b249b11e8f07a51afac45037afee9d1";
    uint8_t exp[32];
    hex_to_buf(exp_hex, exp);
    char message[] = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmno"
        "ijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";

    sha256_update(message, strlen(message), &g_ctx);

    uint8_t actual[32];
    sha256_final(actual, &g_ctx);

    TEST_ASSERT_EQUAL_HEX8_ARRAY(exp, actual, 32);
}

void test_sha256_04(void)
{
    char *exp_hex = "cdc76e5c9914fb9281a1c7e284d73e67f1809a48a497200e046d39ccc7112cd0";
    uint8_t exp[32];
    hex_to_buf(exp_hex, exp);
    char message[] = "aaaaaaaaaa";

    for (int i = 0; i < 100000; ++i) {
        sha256_update(message, strlen(message), &g_ctx);
    }

    uint8_t actual[32];
    sha256_final(actual, &g_ctx);

    TEST_ASSERT_EQUAL_HEX8_ARRAY(exp, actual, 32);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_sha256_zero_message);
    RUN_TEST(test_sha256_01);
    RUN_TEST(test_sha256_02);
    RUN_TEST(test_sha256_03);
    RUN_TEST(test_sha256_04);

    return UNITY_END();
}