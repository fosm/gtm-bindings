cmake_minimum_required(VERSION 2.8)

project(mjs)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH    ${PROJECT_BINARY_DIR}/lib)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake ${CMAKE_MODULE_PATH})

include(CTest)

find_package(NodeJS)
find_package(V8)
find_package(GTM)

include_directories(
  ${NODEJS_INCLUDE_DIR}
  ${V8_INCLUDE_DIR}
  ${GTM_DIST}
  )

link_directories(
  ${GTM_DIST}
  )

add_subdirectory(Source)
add_subdirectory(Testing)
