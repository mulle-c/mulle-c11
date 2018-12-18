cmake_minimum_required( VERSION 3.0)

project( mulle-c11 C)

set( PUBLIC_HEADERS "src/mulle-c11.h")

install( FILES ${PUBLIC_HEADERS} DESTINATION "include/mulle-c11")
