
if (DISABLE_THIS)
try_compile(CMAKE_HOST_HAS_AVX ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/test_avx.c
	COMPILE_DEFINITIONS -mavx
)
endif()


add_executable(blake2_test ${CMAKE_CURRENT_SOURCE_DIR}/blake2_test.c)
add_executable(chacha20_test ${CMAKE_CURRENT_SOURCE_DIR}/chacha20_test.c)
add_executable(sha_test ${CMAKE_CURRENT_SOURCE_DIR}/sha_test.c)


target_link_libraries(chacha20_test seatuna cmocka)
target_link_libraries(blake2_test seatuna cmocka)
target_link_libraries(sha_test cmocka)


add_test(TEST_CHACHA20 chacha20_test
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	COMMAND chacha20_test)
add_test(TEST_BLAKE2 blake2_test
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	COMMAND blake2_test)
add_test(TEST_SHA256 sha_test
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	COMMAND sha_test)

	
install(TARGETS chacha20_test
	RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)

install(TARGETS blake2_test
	RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)

install(TARGETS sha_test
	RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
