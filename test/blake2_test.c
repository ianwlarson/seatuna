
// Test vectors from RFC 7693

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static void null_test(void **state)
{	
	// Empty
}

int main(void)
{
    const struct CMUnitTest tests[] = {
		cmocka_unit_test(null_test),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
