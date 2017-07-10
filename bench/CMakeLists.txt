
add_executable(bench_chacha20 ${CMAKE_CURRENT_SOURCE_DIR}/bench_chacha20.c)

target_link_libraries(bench_chacha20 seatuna)

install(TARGETS bench_chacha20
	RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
