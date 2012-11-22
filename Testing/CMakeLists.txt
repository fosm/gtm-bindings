#
#  Tests for the C bindings to GT.M
#
set(TESTBIN ${EXECUTABLE_OUTPUT_PATH})

include_directories(${GTM_DIST})
link_directories(${GTM_DIST})

add_executable(test001 test001.c)
target_link_libraries(test001 gtmshr)

add_test(Test001 ${TESTBIN}/test001)
