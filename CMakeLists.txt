
cmake_minimum_required(VERSION 3.0.2)

project(seatuna C)

find_package(cmocka REQUIRED)

enable_testing()

add_compile_options(-std=c99)

IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
	MESSAGE("Debug build.")
	add_compile_options(-Wall -Wpedantic)
ELSE()
	MESSAGE("Release build.")
	add_compile_options(-Os)
ENDIF()

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/platform/linux)

add_subdirectory(src)
add_subdirectory(test)

add_library(seatuna SHARED ${lib_srcs})

install(TARGETS seatuna
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/lib
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
        ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib)

