
#file(GLOB lib_srcs ./ *.c)

set(lib_srcs
	${CMAKE_CURRENT_SOURCE_DIR}/seatuna.c
	${CMAKE_CURRENT_SOURCE_DIR}/seatuna_blake2.c
	${CMAKE_CURRENT_SOURCE_DIR}/seatuna_chacha20.c
	PARENT_SCOPE)
