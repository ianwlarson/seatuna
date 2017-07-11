
cmake_minimum_required(VERSION 3.0.2)

project(seatuna C ASM)

set(INSTALL_LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib" CACHE PATH "Installation directory for libraries.")
set(INSTALL_INC_DIR "${CMAKE_INSTALL_PREFIX}/include" CACHE PATH "Installation directory for headers.")

set(SO_MAJOR 1)
set(SO_MINOR 0)
set(SO_PATCH 0)

set(FULLVERSION "${SO_MAJOR}.${SO_MINOR}.${SO_PATCH}")

find_package(cmocka REQUIRED)

enable_testing()

# TODO Remove -save-temps at some point.
add_compile_options(-std=gnu99 -save-temps -Wall -Wpedantic)

option(CHACHA20_DEFAULT "Use the default c chacha20 implementation.")

IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
	MESSAGE("Debug build.")
	add_compile_options(-g)
ELSE()
	MESSAGE("Release build.")
	add_compile_options(-O2)
ENDIF()

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(bench)
add_subdirectory(src)
add_subdirectory(test)

add_library(seatuna SHARED ${lib_srcs})

set_target_properties(seatuna
	PROPERTIES
	VERSION "${FULL_VERSION}"
	SOVERSION "${SO_MAJOR}"
)

install(TARGETS seatuna
	LIBRARY DESTINATION ${INSTALL_LIB_DIR}
	ARCHIVE DESTINATION ${INSTALL_LIB_DIR}
)

