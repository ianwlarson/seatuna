
#file(GLOB lib_srcs ./ *.c)

try_compile(CHACHA_LINUX_SSE ${CMAKE_CURRENT_BINARY_DIR}
	SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/seatuna_chacha20_featuretest.c
	${CMAKE_CURRENT_SOURCE_DIR}/seatuna_chacha20_linux_amd64_sse.s
	COMPILE_DEFINITIONS -I${CMAKE_SOURCE_DIR}/include)

if (CHACHA_LINUX_SSE AND NOT CHACHA20_DEFAULT)
	message(STATUS "Using linux sse assembly for chacha20.")
	set(SEATUNA_CHACHA_SOURCE seatuna_chacha20_linux_amd64_sse.s)
else()
	message(STATUS "Using default chacha20 source.")
	set(SEATUNA_CHACHA_SOURCE seatuna_chacha20.c)
endif()

set(lib_srcs
	${CMAKE_CURRENT_SOURCE_DIR}/seatuna.c
	${CMAKE_CURRENT_SOURCE_DIR}/seatuna_blake2.c
	${CMAKE_CURRENT_SOURCE_DIR}/${SEATUNA_CHACHA_SOURCE}
	PARENT_SCOPE)
