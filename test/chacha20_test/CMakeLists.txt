
add_executable(chacha20_test ${CMAKE_CURRENT_SOURCE_DIR}/chacha20_test.c)

target_link_libraries(chacha20_test seatuna cmocka)

message(STATUS "cmake target supports avx: ${CMAKE_HOST_HAS_AVX}")

if(CMAKE_HOST_HAS_AVX)
	target_compile_options(chacha20_test
		PUBLIC -mavx)
endif()

install(TARGETS chacha20_test
	RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)

add_test(TEST_CHACHA20 chacha20_test
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	COMMAND chacha20_test)

