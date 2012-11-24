
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
# python SWIG configuration
#
if ( WRAP_PYTHON )

  check_PIC_flag ( Python )

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
  SWIG_link_libraries ( GTM cppgtm ${PYTHON_LIBRARIES})

endif()
