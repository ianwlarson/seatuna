
add_executable(blake2_test ${CMAKE_CURRENT_SOURCE_DIR}/blake2_test.c)

target_link_libraries(blake2_test cmocka)

install(TARGETS blake2_test
	RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)

add_test(TEST_BLAKE2 blake2_test
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	COMMAND blake2_test)

