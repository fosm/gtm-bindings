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

configure_file(
  ${PROJECT_SOURCE_DIR}/Testing/runNode.sh.in
  ${LIBRARY_OUTPUT_PATH}/runNode.sh
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

add_executable(test005 test005.c)
target_link_libraries(test005 gtmshr)
add_test(Test005 ${TESTBIN}/test005)

add_executable(node001 node001.cpp)
target_link_libraries(node001 gtmshr)
add_test(Node001 ${TESTBIN}/node001)

add_executable(gtm001 gtm001.cpp)
target_link_libraries(gtm001 cppgtm)
add_test(GTM001 ${TESTBIN}/gtm001)

add_executable(gtm002 gtm002.cpp)
target_link_libraries(gtm002 cppgtm)
add_test(GTM002 ${TESTBIN}/gtm002)

add_executable(gtm003 gtm003.cpp)
target_link_libraries(gtm003 cppgtm)
add_test(GTM003 ${TESTBIN}/gtm003)

add_executable(gtm004 gtm004.cpp)
target_link_libraries(gtm004 cppgtm)
add_test(GTM004 ${TESTBIN}/gtm004)

add_executable(gtm005 gtm005.cpp)
target_link_libraries(gtm005 cppgtm)
add_test(GTM005 ${TESTBIN}/gtm005)

add_executable(gtm006 gtm006.cpp)
target_link_libraries(gtm006 cppgtm)
add_test(GTM006 ${TESTBIN}/gtm006)

add_executable(gtm007 gtm007.cpp)
target_link_libraries(gtm007 cppgtm)
add_test(GTM007 ${TESTBIN}/gtm007)

add_executable(gtm008 gtm008.cpp)
target_link_libraries(gtm008 cppgtm)
add_test(GTM008 ${TESTBIN}/gtm008)

add_executable(gtm009 gtm009.cpp)
target_link_libraries(gtm009 cppgtm)
add_test(GTM009 ${TESTBIN}/gtm009)

add_executable(gtm010 gtm010.cpp)
target_link_libraries(gtm010 cppgtm)
add_test(GTM010 ${TESTBIN}/gtm010)

if(WRAP_PYTHON)
  set(PYTHONTESTLAUNCHER ${LIBRARY_OUTPUT_PATH}/runPythonTest.sh)
  add_test(PYGTM001 ${PYTHONTESTLAUNCHER} gtm001)
  add_test(PYGTM002 ${PYTHONTESTLAUNCHER} gtm002)
  add_test(PYGTM003 ${PYTHONTESTLAUNCHER} gtm003)
  add_test(PYGTM004 ${PYTHONTESTLAUNCHER} gtm004)
  add_test(PYGTM005 ${PYTHONTESTLAUNCHER} gtm005)
  add_test(PYGTM006 ${PYTHONTESTLAUNCHER} gtm006)
  add_test(PYGTM007 ${PYTHONTESTLAUNCHER} gtm007)
  add_test(PYGTM008 ${PYTHONTESTLAUNCHER} gtm008)
  add_test(PYGTM009 ${PYTHONTESTLAUNCHER} gtm009)
  add_test(PYGTM010 ${PYTHONTESTLAUNCHER} gtm010)
endif()
