#
# python SWIG configuration
#
if ( WRAP_PYTHON )

  find_package ( SWIG 2 REQUIRED )
  include(${SWIG_USE_FILE})

  find_package ( PythonLibs 2.7 REQUIRED )
  find_package ( PythonInterp 2.7 REQUIRED )
  include_directories ( ${PYTHON_INCLUDE_DIR} )

  # Run swig
  set(CMAKE_SWIG_FLAGS ${CMAKE_SWIG_GLOBAL_FLAGS} -features autodoc=1 -keyword)

  set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR})
  set(SWIG_MODULE_GTM_EXTRA_DEPS ${SWIG_EXTRA_DEPS} ${CMAKE_CURRENT_SOURCE_DIR}/Python.i )
  SET_SOURCE_FILES_PROPERTIES(GTM.i PROPERTIES CPLUSPLUS ON)
  SET_SOURCE_FILES_PROPERTIES(GTM.i PROPERTIES CMAKE_SWIG_FLAGS "-includeall")
  SWIG_add_module ( GTM python GTM.i )
  SWIG_link_libraries ( GTM ${GTM_LIBRARIES} ${PYTHON_LIBRARIES})

endif()
