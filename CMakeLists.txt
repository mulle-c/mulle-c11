cmake_minimum_required (VERSION 3.0)

project( mulle-c11 C)

set(HEADERS
src/mulle_c11.h
)

INSTALL(FILES ${HEADERS} DESTINATION "include/mulle_c11")
