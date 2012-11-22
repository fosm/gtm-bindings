#
#  Tests for the C bindings to GT.M
#
set(TESTBIN ${EXECUTABLE_OUTPUT_PATH})

include_directories(${GTM_DIST})
link_directories(${GTM_DIST})

configure_file(
  ${PROJECT_SOURCE_DIR}/Testing/test002.ci
  ${EXECUTABLE_OUTPUT_PATH}/test002.ci
  )

configure_file(
  ${PROJECT_SOURCE_DIR}/Testing/test002.m
  ${GTM_ROUTINES}/test002.m
  )

add_executable(test001 test001.c)
target_link_libraries(test001 gtmshr)
add_test(Test001 ${TESTBIN}/test001)

add_executable(test002 test002.c)
target_link_libraries(test002 gtmshr)
add_test(Test002 ${TESTBIN}/test002)

add_executable(test003 test003.c)
target_link_libraries(test003 gtmshr)
add_test(Test003 ${TESTBIN}/test003)

add_executable(test004 test004.c)
target_link_libraries(test004 gtmshr)
add_test(Test004 ${TESTBIN}/test004)
