cmake_minimum_required( VERSION 3.5)

project( package C)

add_subdirectory( ../.. ${CMAKE_CURRENT_BINARY_DIR}/mulle-c11)

add_executable( ${PROJECT_NAME}.exe main.c)

#target_link_libraries( ${PROJECT_NAME}.exe PRIVATE mulle-c11)

