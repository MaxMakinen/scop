#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "sfml-system" for configuration "Release"
set_property(TARGET sfml-system APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(sfml-system PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libsfml-system-s.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS sfml-system )
list(APPEND _IMPORT_CHECK_FILES_FOR_sfml-system "${_IMPORT_PREFIX}/lib/libsfml-system-s.a" )

# Import target "sfml-window" for configuration "Release"
set_property(TARGET sfml-window APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(sfml-window PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libsfml-window-s.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS sfml-window )
list(APPEND _IMPORT_CHECK_FILES_FOR_sfml-window "${_IMPORT_PREFIX}/lib/libsfml-window-s.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
