
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "seatuna_chacha20.h"
#include "static_utils.h"

static void test_chacha20_00(void **state)
{
	uint8_t key[32] = {0};
	uint8_t nonce[12] = {0};
	uint32_t counter = 0;

	char *exp_hex = "76b8e0ada0f13d90405d6ae55386bd28bdd219b8a08ded1aa836efcc8b770dc7da41597c5157488d7724e03fb8d84a376a43b8f41518a11cc387b669b2ee6586";
	uint8_t exp[64];
	hex_to_buf(exp_hex, exp);

	uint8_t actual[64];
	seatuna_chacha20_bytes(key, &counter, nonce, 64, actual);

	assert_int_equal(counter, 1);
	assert_memory_equal(exp, actual, 64);
}

static void test_chacha20_01(void **state)
{
	uint8_t key[32] = {0};
	uint8_t nonce[12] = {0};
	uint32_t counter = 1;

	char *exp_hex = "9f07e7be5551387a98ba977c732d080dcb0f29a048e3656912c6533e32ee7aed29b721769ce64e43d57133b074d839d531ed1f28510afb45ace10a1f4b794d6f";
	uint8_t exp[64];
	hex_to_buf(exp_hex, exp);

	uint8_t actual[64];
	seatuna_chacha20_bytes(key, &counter, nonce, 64, actual);

	assert_int_equal(counter, 2);
	assert_memory_equal(exp, actual, 64);
}

static void test_chacha20_02(void **state)
{
	uint8_t key[32] = {0};
	key[31] = 0x1;
	uint8_t nonce[12] = {0};
	uint32_t counter = 1;

	char *exp_hex = "3aeb5224ecf849929b9d828db1ced4dd832025e8018b8160b82284f3c949aa5a8eca00bbb4a73bdad192b5c42f73f2fd4e273644c8b36125a64addeb006c13a0";
	uint8_t exp[64];
	hex_to_buf(exp_hex, exp);

	uint8_t actual[64];
	seatuna_chacha20_bytes(key, &counter, nonce, 64, actual);

	assert_int_equal(counter, 2);
	assert_memory_equal(exp, actual, 64);
}



static void test_chacha20_03(void **state)
{
	uint8_t key[32] = {0};
	key[1] = 0xff;
	uint8_t nonce[12] = {0};
	uint32_t counter = 2;

	char *exp_hex = "72d54dfbf12ec44b362692df94137f328fea8da73990265ec1bbbea1ae9af0ca13b25aa26cb4a648cb9b9d1be65b2c0924a66c54d545ec1b7374f4872e99f096";
	uint8_t exp[64];
	hex_to_buf(exp_hex, exp);

	uint8_t actual[64];
	seatuna_chacha20_bytes(key, &counter, nonce, 64, actual);

	assert_int_equal(counter, 3);
	assert_memory_equal(exp, actual, 64);
}



static void test_chacha20_04(void **state)
{
	uint8_t key[32] = {0};
	uint8_t nonce[12] = {0};
	nonce[11] = 0x2;
	uint32_t counter = 0;

	char *exp_hex = "c2c64d378cd536374ae204b9ef933fcd1a8b2288b3dfa49672ab765b54ee27c78a970e0e955c14f3a88e741b97c286f75f8fc299e8148362fa198a39531bed6d";
	uint8_t exp[64];
	hex_to_buf(exp_hex, exp);

	uint8_t actual[64];
	seatuna_chacha20_bytes(key, &counter, nonce, 64, actual);

	assert_int_equal(counter, 1);
	assert_memory_equal(exp, actual, 64);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_chacha20_00),
        cmocka_unit_test(test_chacha20_01),
        cmocka_unit_test(test_chacha20_02),
        cmocka_unit_test(test_chacha20_03),
        cmocka_unit_test(test_chacha20_04),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
