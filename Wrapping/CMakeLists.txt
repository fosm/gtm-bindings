
# for wrapping to work correctly fPIC is needed on certain system.
macro(check_PIC_flag Language)
  string( TOUPPER ${Language} LANGUAGE )
  if ( UNIX AND NOT APPLE AND WRAP_${LANGUAGE} )
    if ( NOT ${CMAKE_CXX_FLAGS} MATCHES "-fPIC")
      message ( FATAL_ERROR "${Language} wrapping requires CMAKE_CXX_FLAGS (or equivalent) to include -fPIC and built with this flag." )
    endif()
  endif()
endmacro()


#
# Python SWIG configuration
#
if ( WRAP_PYTHON )

  check_PIC_flag ( Python )

  find_package ( SWIG 2 REQUIRED )
  # include(${SWIG_USE_FILE})
  include(UseSWIGLocal)

  find_package ( PythonLibs 2.7 REQUIRED )
  find_package ( PythonInterp 2.7 REQUIRED )
  include_directories ( ${PYTHON_INCLUDE_DIR} )

  # Run swig
  set(CMAKE_SWIG_FLAGS ${CMAKE_SWIG_GLOBAL_FLAGS} -features autodoc=1 -keyword)

  set(CMAKE_SWIG_OUTDIR ${LIBRARY_OUTPUT_PATH})
  set(SWIG_MODULE_GTM_EXTRA_DEPS ${SWIG_EXTRA_DEPS} ${CMAKE_CURRENT_SOURCE_DIR}/Python.i )
  SET_SOURCE_FILES_PROPERTIES(gtm.i PROPERTIES CPLUSPLUS ON)
  SET_SOURCE_FILES_PROPERTIES(gtm.i PROPERTIES CMAKE_SWIG_FLAGS "-includeall")
  SWIG_add_module ( gtm python gtm.i )
  SWIG_link_libraries ( gtm cppgtm ${PYTHON_LIBRARIES})

  # Installation
  set( GTM_PYTHON_MODULE_DIR "${PROJECT_BINARY_DIR}/Wrapping" )
  file(TO_NATIVE_PATH "${GTM_PYTHON_MODULE_DIR}" GTM_NATIVE_PYTHON_MODULE_DIR )
  get_target_property( GTM_BINARY_MODULE ${SWIG_MODULE_gtm_TARGET_NAME} LOCATION )
  file(TO_NATIVE_PATH "${GTM_BINARY_MODULE}" GTM_NATIVE_BINARY_MODULE )

  include( ConfigureFileBuildtime )
  configure_file_buildtime( "${CMAKE_CURRENT_SOURCE_DIR}/PythonPackage/setup.py.in"
    "${CMAKE_CURRENT_BINARY_DIR}/PythonPackage/setup.py" )

  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/PythonPackage/distribute_setup.py"
    "${CMAKE_CURRENT_BINARY_DIR}/PythonPackage/distribute_setup.py"
    COPYONLY )

endif()


#
# R SWIG configuration
#
if ( WRAP_R )

  check_PIC_flag ( R )

  find_package ( SWIG 2 REQUIRED )
  include(${SWIG_USE_FILE})

  find_package ( R REQUIRED )
  include_directories ( ${R_INCLUDE_DIR} )

  # Run swig
  set(CMAKE_SWIG_FLAGS ${CMAKE_SWIG_GLOBAL_FLAGS})

  set(CMAKE_SWIG_OUTDIR ${LIBRARY_OUTPUT_PATH})
  set(SWIG_MODULE_GTM_EXTRA_DEPS ${SWIG_EXTRA_DEPS} ${CMAKE_CURRENT_SOURCE_DIR}/R.i )
  SET_SOURCE_FILES_PROPERTIES(gtm.i PROPERTIES CPLUSPLUS ON)
  SET_SOURCE_FILES_PROPERTIES(gtm.i PROPERTIES CMAKE_SWIG_FLAGS "-includeall")
  SWIG_add_module ( gtm r gtm.i )

  if( R_LIBRARIES )
    SWIG_link_libraries ( gtm cppgtm ${R_LIBRARIES})
  endif()

  configure_file(
    ${PROJECT_SOURCE_DIR}/Wrapping/setupREnvironment.sh.in
    ${LIBRARY_OUTPUT_PATH}/setupREnvironment.sh
    )

endif()

add_subdirectory(Distribution)
