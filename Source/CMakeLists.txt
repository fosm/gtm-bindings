#
#  Stand alone programs that use the C bindings to GT.M
#

include_directories(${GTM_DIST})
link_directories(${GTM_DIST})

configure_file(
  ${PROJECT_SOURCE_DIR}/Source/gtm_access.ci
  ${EXECUTABLE_OUTPUT_PATH}/gtm_access.ci
  )

configure_file(
  ${PROJECT_SOURCE_DIR}/Source/_gtmaccess.m
  ${GTM_ROUTINES}/_gtmaccess.m
  )

configure_file(
  ${PROJECT_SOURCE_DIR}/Source/setupEnvironment.sh.in
  ${EXECUTABLE_OUTPUT_PATH}/setupEnvironment.sh
  )

add_library(gtm SHARED gtm_node.cpp)
target_link_libraries(gtm ${V8_LIBRARY})

