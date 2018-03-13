if( NOT __MULLE_C11_DEPENDENCIES_AND_LIBRARIES_TXT__)
   set( __MULLE_C11_DEPENDENCIES_AND_LIBRARIES_TXT__ ON)

   if( MULLE_TRACE_INCLUDE)
      message( STATUS "# Include \"${CMAKE_CURRENT_LIST_FILE}\"" )
   endif()

   #
   # Put your find_library() statements here to import other libraries
   #
   # Add OS specific dependencies to OS_SPECIFIC_LIBRARIES
   # Add all other dependencies (rest) to C_DEPENDENCIES_LIBRARIES


   #
   # The following includes include definitions generated
   # during `mulle-sde update`. Don't edit those files. They are
   # overwritten frequently.
   #
   # === MULLE-SDE START ===

   # `mulle-sde update` will generate these files

   include( _Dependencies)
   include( _Libraries)

   # === MULLE-SDE END ===
   #
endif()
