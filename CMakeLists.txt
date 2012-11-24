cmake_minimum_required(VERSION 2.8)

project(mjs)

# MJS version number.
set(MJS_VERSION_MAJOR "1")
set(MJS_VERSION_MINOR "0")
set(MJS_VERSION_PATCH "0")

# Version string should not include patch level.  The major.minor is
# enough to distinguish available features of the toolkit.
set(MJS_VERSION_STRING "${MJS_VERSION_MAJOR}.${MJS_VERSION_MINOR}")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH    ${PROJECT_BINARY_DIR}/lib)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake ${CMAKE_MODULE_PATH})

find_package(NodeJS)
find_package(V8)
find_package(GTM)

include_directories(
  ${NODEJS_INCLUDE_DIR}
  ${V8_INCLUDE_DIR}
  ${GTM_DIST}
  ${PROJECT_SOURCE_DIR}/Source
  ${PROJECT_BINARY_DIR}/Source
  )

link_directories(
  ${GTM_DIST}
  )

configure_file(
  ${PROJECT_SOURCE_DIR}/Source/mjsConfigure.h.in
  ${PROJECT_BINARY_DIR}/Source/mjsConfigure.h
  )

# The fPIC flags is used to create position independent code.
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag( "-fPIC" CXX_HAS_fPIC )
if( CXX_HAS_fPIC )
  if(NOT "${CMAKE_CXX_FLAGS}" MATCHES "-fPIC")
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC" )
  endif()
endif( )


#
# Set up CPack support
#
set(CPACK_SOURCE_IGNORE_FILES "/\\\\.git")

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "m.js version ${MJS_VERSION_MAJOR}")
set(CPACK_PACKAGE_VENDOR "ISC")
set(CPACK_PACKAGE_VERSION_MAJOR "${MJS_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${MJS_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${MJS_VERSION_PATCH}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "MJS-${MJS_VERSION_MAJOR}.${MJS_VERSION_MINOR}")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

include(CPack)

#
# Set up for Testing
#
include(CTest)

option( WRAP_PYTHON "Wrap Python" OFF)

add_subdirectory(Source)
add_subdirectory(Testing)
add_subdirectory(Wrapping)

