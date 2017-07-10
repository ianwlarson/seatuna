
add_subdirectory(blake2_test)


try_compile(CMAKE_HOST_HAS_AVX ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/test_avx.c
	COMPILE_DEFINITIONS -mavx
)

add_subdirectory(chacha20_test)
add_subdirectory(sha_test)
