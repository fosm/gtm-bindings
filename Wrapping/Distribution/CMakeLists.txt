#
# Packaging
#

#
# A general packaging target, not built by default, to build packages for each
# language.  This should depend on all language specific targets.
#
add_custom_target( dist cmake -E echo "Finished generating wrapped packages for distribution..." )



if( WRAP_PYTHON )

  add_custom_target( prepare.Python
    ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/lib/gtm.py ${PROJECT_BINARY_DIR}/Wrapping/PythonPackage
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/Wrapping/PythonPackage
    COMMENT "Copying gtm.py to packaging directory" )

  add_custom_target( build.Python
    ${PYTHON_EXECUTABLE} ./setup.py build
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/Wrapping/PythonPackage
    COMMENT "Building Python egg for distribution" )

  add_custom_target( dist.Python
    ${PYTHON_EXECUTABLE} ./setup.py bdist_egg
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/Wrapping/PythonPackage
    COMMENT "Creating Python egg for distribution" )

  add_dependencies( build.Python prepare.Python )
  add_dependencies( dist.Python build.Python )

  add_dependencies( dist dist.Python )

endif()


if ( WRAP_NODEJS )

  file(GLOB NODEJS_TESTS "${PROJECT_SOURCE_DIR}/Testing/*.js")

  set(SOURCE_MODULE_PACKAGE_DIR "${PROJECT_SOURCE_DIR}/Wrapping/NodePackage")
  set(BINARY_MODULE_PACKAGE_DIR "${PROJECT_BINARY_DIR}/Wrapping/NodePackage/node_modules/gtm")

  file(MAKE_DIRECTORY "${BINARY_MODULE_PACKAGE_DIR}")
  file(MAKE_DIRECTORY "${BINARY_MODULE_PACKAGE_DIR}/tests")
  file(MAKE_DIRECTORY "${BINARY_MODULE_PACKAGE_DIR}/lib")
  file(MAKE_DIRECTORY "${BINARY_MODULE_PACKAGE_DIR}/resources")

  configure_file(
    "${SOURCE_MODULE_PACKAGE_DIR}/package.json.in"
    "${BINARY_MODULE_PACKAGE_DIR}/package.json"
    )

  configure_file(
    "${SOURCE_MODULE_PACKAGE_DIR}/index.js.in"
    "${BINARY_MODULE_PACKAGE_DIR}/index.js"
    )

  configure_file(
    "${SOURCE_MODULE_PACKAGE_DIR}/README"
    "${BINARY_MODULE_PACKAGE_DIR}/README"
    COPYONLY
    )

  configure_file(
    ${PROJECT_SOURCE_DIR}/Source/gtm_access.ci
    ${BINARY_MODULE_PACKAGE_DIR}/resources/gtm_access.ci
    COPYONLY
    )

  configure_file(
    ${PROJECT_SOURCE_DIR}/Source/_gtmaccess.m
    ${BINARY_MODULE_PACKAGE_DIR}/resources/_gtmaccess.m
    COPYONLY
    )

  configure_file(
    ${PROJECT_SOURCE_DIR}/LICENSE
    ${BINARY_MODULE_PACKAGE_DIR}/LICENSE
    COPYONLY
    )

  file(COPY ${NODEJS_TESTS} DESTINATION "${BINARY_MODULE_PACKAGE_DIR}/tests")

  add_custom_target( dist.Nodejs
    COMMAND ${CMAKE_COMMAND}
      -E copy "${LIBRARY_OUTPUT_PATH}/${CMAKE_SHARED_MODULE_PREFIX}nodegtm${CMAKE_SHARED_MODULE_SUFFIX}"
              "${BINARY_MODULE_PACKAGE_DIR}/lib/fisgtm.node"
    COMMENT "Copying gtm shared library into a file named 'fisgtm.node' for packaging node.js module."
    )

  add_dependencies( dist.Nodejs nodegtm)

  add_dependencies( dist dist.Nodejs )

endif()


