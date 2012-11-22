cmake_minimum_required(VERSION 2.8)

project(mjs)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH    ${PROJECT_BINARY_DIR}/lib)

find_path(GTM_DIST NAMES libgtmshr.so
PATHS
 "/usr/lib/fis-gtm/V5.5-000_x86_64"
 "/usr/lib/fis-gtm/V6.0-000_x86_64"
 )

find_path(GTM_ROUTINES PATHS $ENV{gtmroutines})

include(CTest)

add_subdirectory(Source)
add_subdirectory(Testing)
