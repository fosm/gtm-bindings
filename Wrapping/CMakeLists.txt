#
# python SWIG configuration
#
if ( WRAP_PYTHON )

  find_package ( SWIG 2 REQUIRED )
  include(${SWIG_USE_FILE})

  find_package ( PythonLibs 2.7 REQUIRED )
  find_package ( PythonInterp 2.7 REQUIRED )
  include_directories ( ${PYTHON_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/Wrapping )

  # Run swig
  set(CMAKE_SWIG_FLAGS ${CMAKE_SWIG_GLOBAL_FLAGS} "-c++" -features autodoc=1 -keyword)
  set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR})
  set(SWIG_MODULE_GTM_EXTRA_DEPS ${SWIG_EXTRA_DEPS}
    ${CMAKE_CURRENT_SOURCE_DIR}/Python.i )
  SWIG_add_module ( GTM python GTM.i GTMPython.cpp )
  SWIG_link_libraries ( GTM ${GTM_LIBRARIES} ${PYTHON_LIBRARIES})
  set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/GTMPython.cpp PROPERTIES COMPILE_FLAGS "-w")

endif()
