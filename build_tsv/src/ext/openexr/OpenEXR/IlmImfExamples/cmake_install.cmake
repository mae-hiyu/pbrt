# Install script for directory: /Users/hiyu/Tools/pbrt/src/ext/openexr/OpenEXR/IlmImfExamples

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Library/Developer/CommandLineTools/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/OpenEXR/examples" TYPE FILE FILES
    "/Users/hiyu/Tools/pbrt/src/ext/openexr/OpenEXR/IlmImfExamples/main.cpp"
    "/Users/hiyu/Tools/pbrt/src/ext/openexr/OpenEXR/IlmImfExamples/drawImage.cpp"
    "/Users/hiyu/Tools/pbrt/src/ext/openexr/OpenEXR/IlmImfExamples/rgbaInterfaceExamples.cpp"
    "/Users/hiyu/Tools/pbrt/src/ext/openexr/OpenEXR/IlmImfExamples/rgbaInterfaceTiledExamples.cpp"
    "/Users/hiyu/Tools/pbrt/src/ext/openexr/OpenEXR/IlmImfExamples/generalInterfaceExamples.cpp"
    "/Users/hiyu/Tools/pbrt/src/ext/openexr/OpenEXR/IlmImfExamples/lowLevelIoExamples.cpp"
    "/Users/hiyu/Tools/pbrt/src/ext/openexr/OpenEXR/IlmImfExamples/previewImageExamples.cpp"
    "/Users/hiyu/Tools/pbrt/src/ext/openexr/OpenEXR/IlmImfExamples/generalInterfaceTiledExamples.cpp"
    "/Users/hiyu/Tools/pbrt/src/ext/openexr/OpenEXR/IlmImfExamples/generalInterfaceTiledExamples.h"
    "/Users/hiyu/Tools/pbrt/src/ext/openexr/OpenEXR/IlmImfExamples/drawImage.h"
    "/Users/hiyu/Tools/pbrt/src/ext/openexr/OpenEXR/IlmImfExamples/rgbaInterfaceExamples.h"
    "/Users/hiyu/Tools/pbrt/src/ext/openexr/OpenEXR/IlmImfExamples/generalInterfaceExamples.h"
    "/Users/hiyu/Tools/pbrt/src/ext/openexr/OpenEXR/IlmImfExamples/rgbaInterfaceTiledExamples.h"
    "/Users/hiyu/Tools/pbrt/src/ext/openexr/OpenEXR/IlmImfExamples/lowLevelIoExamples.h"
    "/Users/hiyu/Tools/pbrt/src/ext/openexr/OpenEXR/IlmImfExamples/previewImageExamples.h"
    "/Users/hiyu/Tools/pbrt/src/ext/openexr/OpenEXR/IlmImfExamples/namespaceAlias.h"
    )
endif()

