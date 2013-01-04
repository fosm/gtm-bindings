#
# Packaging
#

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

endif()

# A general packaging target, not built by default, to build packages for each
# language.  This should depend on all language specific targets.
add_custom_target( dist cmake -E echo "Finished generating wrapped packages for distribution..." )
add_dependencies( dist dist.Python )

