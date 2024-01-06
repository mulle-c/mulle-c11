cmake_minimum_required( VERSION 3.0)

project( mulle-c11 C)

set( PUBLIC_HEADERS "src/mulle-c11.h"
"src/mulle-c11-eval.h"
"src/mulle-c11-bool.h"
"src/mulle-c11-integer.h"
)

install( FILES ${PUBLIC_HEADERS} DESTINATION "include/mulle-c11")
