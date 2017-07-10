
add_executable(sha_test sha_test.c)

target_link_libraries(sha_test cmocka)

install(TARGETS sha_test
	RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)

add_test(TEST_SHA256 sha_test
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	COMMAND sha_test)
