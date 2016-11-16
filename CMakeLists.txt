# Copyright 2016 Ian W. Larson
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

project("SeaTuna" C)
cmake_minimum_required(VERSION 3.0)

enable_testing()

add_compile_options(-std=c99)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/platform/linux)

add_library(Unity STATIC ext/src/unity.c)
target_include_directories(Unity PUBLIC ${PROJECT_SOURCE_DIR}/ext/src)

add_subdirectory(src)
add_subdirectory(test)

add_library(seatuna SHARED ${lib_srcs})
add_executable(seatuna_tests ${test_srcs} ${lib_srcs})

target_link_libraries(seatuna_tests PUBLIC Unity)

install(TARGETS seatuna seatuna_tests
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/lib
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
        ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib)

install(TARGETS seatuna_tests RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)

message(STATUS "${PROJECT_SOURCE_DIR}")
