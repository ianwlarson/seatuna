
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "portable_sha256.h"

static int setup(void **state)
{
	sha256_ctx *s = malloc(sizeof(*s));
    sha256_init(s);
	
	*state = s;
	
	return 0;
}

static int teardown(void **state)
{
	free(*state);
	
	return 0;
}

static void test_sha256_zero_message(void **state)
{	
    char *exp_hex = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";
    uint8_t exp[32];
    hex_to_buf(exp_hex, exp);

    uint8_t actual[32];
    sha256_final(actual, *state);

    assert_memory_equal(exp, actual, 32);
}

static void test_sha256_00(void **state)
{
    char *exp_hex = "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad";
    uint8_t exp[32];
    hex_to_buf(exp_hex, exp);
    char message[] = "abc";

    sha256_update(message, strlen(message), *state);

    uint8_t actual[32];
    sha256_final(actual, *state);

    assert_memory_equal(exp, actual, 32);
}

static void test_sha256_01(void **state)
{
    char *exp_hex = "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1";
    uint8_t exp[32];
    hex_to_buf(exp_hex, exp);
    char message[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";

    sha256_update(message, strlen(message), *state);

    uint8_t actual[32];
    sha256_final(actual, *state);

    assert_memory_equal(exp, actual, 32);
}

static void test_sha256_02(void **state)
{
    char *exp_hex = "cf5b16a778af8380036ce59e7b0492370b249b11e8f07a51afac45037afee9d1";
    uint8_t exp[32];
    hex_to_buf(exp_hex, exp);
    char message[] = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmno"
        "ijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";

    sha256_update(message, strlen(message), *state);

    uint8_t actual[32];
    sha256_final(actual, *state);

    assert_memory_equal(exp, actual, 32);
}

static void test_sha256_03(void **state)
{
    char *exp_hex = "cdc76e5c9914fb9281a1c7e284d73e67f1809a48a497200e046d39ccc7112cd0";
    uint8_t exp[32];
    hex_to_buf(exp_hex, exp);
    char message[] = "aaaaaaaaaa";

    for (int i = 0; i < 100000; ++i) {
        sha256_update(message, strlen(message), *state);
    }

    uint8_t actual[32];
    sha256_final(actual, *state);

    assert_memory_equal(exp, actual, 32);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_sha256_zero_message),
        cmocka_unit_test(test_sha256_00),
        cmocka_unit_test(test_sha256_01),
        cmocka_unit_test(test_sha256_02),
        cmocka_unit_test(test_sha256_03),
    };
    return cmocka_run_group_tests(tests, setup, teardown);
}
