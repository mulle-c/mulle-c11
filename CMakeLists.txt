cmake_minimum_required (VERSION 3.0)

project( mulle-c11 C)

set(HEADERS
src/mulle_c11.h
)

set( PUBLIC_HEADERS
${HEADERS}
CMakeDependencies.txt
)

INSTALL(FILES ${PUBLIC_HEADERS} DESTINATION "include/mulle_c11")
