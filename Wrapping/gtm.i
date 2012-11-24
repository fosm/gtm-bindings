/*=========================================================================
*
*  Copyright OSEHRA
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*         http://www.apache.org/licenses/LICENSE-2.0.txt
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*=========================================================================*/
%module gtm

// Remove some warnings
#pragma SWIG nowarn=511

// Use exceptions
%include <exception.i>

// Support Strings
%include <std_string.i>

// Customize exception handling
%exception {
  try {
    $action
  } catch( std::exception &ex ) {
    char error_msg[1024];
    snprintf( error_msg, 1024, "Exception thrown in GTM $symname: %s", ex.what() );
    SWIG_exception( SWIG_RuntimeError, error_msg );
  } catch( ... ) {
    SWIG_exception( SWIG_UnknownError, "Unknown exception thrown in GTM $symname" );
  }
}


// This section is copied verbatim into the generated source code.
// Any include files, definitions, etc. need to go here.
%{
#define SWIG_FILE_WITH_INIT
#include "GTM.h"
%}

// Language Specific Sections
%include Python.i


// Classes to be wrapped
%include "GTM.h"

