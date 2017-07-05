
add_executable(chacha20_test ${CMAKE_CURRENT_SOURCE_DIR}/chacha20_test.c)

target_link_libraries(chacha20_test cmocka)

install(TARGETS chacha20_test
	RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)

add_test(TEST_CHACHA20 chacha20_test
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	COMMAND chacha20_test)

