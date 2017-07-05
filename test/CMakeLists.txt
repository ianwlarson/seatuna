
file(GLOB srcs ./ *.c)

set(test_srcs ${srcs} PARENT_SCOPE)

add_subdirectory(sha_tests)
