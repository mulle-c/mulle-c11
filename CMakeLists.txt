cmake_minimum_required( VERSION 3.0)

project( mulle-c11 C)


### mulle-sde environment

# add cmake module paths to search path
list( INSERT CMAKE_MODULE_PATH 0 "${PROJECT_SOURCE_DIR}/cmake/share")
list( INSERT CMAKE_MODULE_PATH 0 "${PROJECT_SOURCE_DIR}/cmake")

include( Environment)


### Files

include( PreFiles OPTIONAL)

set( MULLE_C11_LIBRARY ON)

#
# Include all non underscored .cmake files in ./cmake
#
file( GLOB LOCAL_CMAKE_INCLUDES
   "cmake/[A-Za-z0-9]*.cmake"
)

foreach( FILE ${LOCAL_CMAKE_INCLUDES} )
   include( "${FILE}")
endforeach()


include_directories( ${INCLUDE_DIRS})

include( PostFiles OPTIONAL)

### Library

include( PreLibrary OPTIONAL)

add_library( "mulle-c11"
${SOURCES}
${PUBLIC_HEADERS}
${PRIVATE_HEADERS}
${CMAKE_EDITABLE_FILES}
)

if( BUILD_SHARED_LIBS)
   target_link_libraries( mulle-c11
${DEPENDENCIES_LIBRARIES}
${OS_SPECIFIC_LIBRARIES}
)
endif()

include( PostLibrary OPTIONAL)

### Install

include( PreInstall OPTIONAL)

install( TARGETS "mulle-c11" DESTINATION "lib")
install( FILES ${PUBLIC_HEADERS}  DESTINATION "include/mulle-c11")
install( FILES ${PRIVATE_HEADERS} DESTINATION "include/mulle-c11/private")

install( FILES ${CMAKE_INCLUDES}  DESTINATION "include/mulle-c11/cmake")

include( PostInstall OPTIONAL)
