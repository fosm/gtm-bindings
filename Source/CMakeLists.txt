#
#  Stand alone programs that use the C bindings to GT.M
#

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

add_library(cppgtm GTM.cpp)
target_link_libraries(cppgtm ${GTM_LIBRARY})

add_library(nodegtm SHARED NodeAddon.cpp NodeGTM.cpp)
target_link_libraries(nodegtm ${V8_LIBRARY} cppgtm)

add_custom_command(TARGET nodegtm
  POST_BUILD
  COMMAND ${CMAKE_COMMAND}
  ARGS -E copy "${LIBRARY_OUTPUT_PATH}/${CMAKE_SHARED_MODULE_PREFIX}nodegtm${CMAKE_SHARED_MODULE_SUFFIX}" "${LIBRARY_OUTPUT_PATH}/gtm.node"
  COMMENT "Copy the shared library into a file named 'gtm.node' as expected by Node.js"
  )

