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

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_sha256_zero_message);

    return UNITY_END();
}