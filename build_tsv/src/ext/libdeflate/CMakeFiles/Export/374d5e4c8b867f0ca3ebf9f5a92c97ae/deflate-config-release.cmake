#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "deflate::deflate" for configuration "Release"
set_property(TARGET deflate::deflate APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(deflate::deflate PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libdeflate.a"
  )

list(APPEND _cmake_import_check_targets deflate::deflate )
list(APPEND _cmake_import_check_files_for_deflate::deflate "${_IMPORT_PREFIX}/lib/libdeflate.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
