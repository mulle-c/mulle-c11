cmake_minimum_required( VERSION 3.0)

project( mulle-c11 C)


### mulle-sde environment

# add cmake module paths to search path
list( INSERT CMAKE_MODULE_PATH 0 "${PROJECT_SOURCE_DIR}/cmake/share")
list( INSERT CMAKE_MODULE_PATH 0 "${PROJECT_SOURCE_DIR}/cmake")

include( Environment)


### Files

include( PreFiles OPTIONAL)

#
# Include all non underscored .cmake files in ./cmake
#
file( GLOB LOCAL_CMAKE_INCLUDES
   "cmake/[A-Za-z0-9]*.cmake"
)

# message( STATUS "CMAKE_MODULE_PATH=\"${CMAKE_MODULE_PATH}\"")

foreach( FILE ${LOCAL_CMAKE_INCLUDES} )
#   message( STATUS "including \"${FILE}\"")
   include( "${FILE}")
endforeach()


include_directories( ${INCLUDE_DIRS})

include( PostFiles OPTIONAL)

### Install

include( PreInstall OPTIONAL)

install( FILES ${PUBLIC_HEADERS}  DESTINATION "include/mulle-c11")
install( FILES ${PRIVATE_HEADERS} DESTINATION "include/mulle-c11/private")

install( FILES ${CMAKE_INCLUDES}  DESTINATION "include/mulle-c11/cmake")

include( PostInstall OPTIONAL)
