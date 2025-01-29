cmake_minimum_required( VERSION 3.5)

project( mulle-c11 VERSION 4.6.1 LANGUAGES C)

set( PUBLIC_HEADERS "src/mulle-c11.h"
"src/mulle-c11-eval.h"
"src/mulle-c11-bool.h"
"src/mulle-c11-integer.h"
)

add_library( mulle-c11 INTERFACE)

# Create a custom target to copy headers to a temporary include directory
add_custom_target( mulle-c11-headers ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/include/mulle-c11"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PUBLIC_HEADERS} "${CMAKE_BINARY_DIR}/include/mulle-c11"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    SOURCES ${PUBLIC_HEADERS}
)

add_dependencies( mulle-c11 mulle-c11-headers)

target_include_directories(mulle-c11 INTERFACE
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install( FILES ${PUBLIC_HEADERS} DESTINATION "include/mulle-c11")
install( TARGETS mulle-c11 EXPORT mulle-c11-targets)
install( EXPORT mulle-c11-targets
         FILE mulle-c11-config.cmake
         NAMESPACE mulle-c11::
         DESTINATION lib/cmake/mulle-c11
)
