
add_subdirectory(blake2_test)


if (DISABLE_THIS)
try_compile(CMAKE_HOST_HAS_AVX ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/test_avx.c
	COMPILE_DEFINITIONS -mavx
)
endif()

add_subdirectory(chacha20_test)
add_subdirectory(sha_test)
