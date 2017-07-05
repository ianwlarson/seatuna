
add_executable(sha_tests sha_tests.c)

target_link_libraries(sha_tests cmocka)

install(TARGETS sha_tests
	RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)

add_test(TEST_SHA256 sha_tests
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
	COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/bin/sha_tests)
