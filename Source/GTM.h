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
#ifndef __GTM_h
#define __GTM_h

#include <cstddef>
#include <string>

extern "C" {
#include "gtmxc_types.h"
#include <termios.h>
}

// maximum length of a GT.M message
#define maxMessageLength 2048
#define maxValueLength 1048576

// GT.M call wrapper - if an error in call or untrappable
// error in GT.M, print error on STDERR, clean up and exit
#define CALLGTM(functioncall) \
  this->functionStatus = functioncall ;		\
  if (0 != this->functionStatus ) {				\
    gtm_zstatus( this->statusMessage, maxMessageLength );			\
    std::cerr << this->statusMessage << std::endl;		\
    tcsetattr( 2, 0, &stderr_sav );		\
    tcsetattr( 1, 0, &stdout_sav );		\
    tcsetattr( 0, 0, &stdin_sav );		\
    gtm_exit();					\
  }


//
//
//  C++ Interface to GTM API.
//
//
class GTM
{
public:
  GTM();
  virtual ~GTM();

  // Reporting about itsefl
  const char * Version() const;
  const char * About() const;

  //
  // Methods to interact with GT.M
  //
  void Get( const gtm_char_t * nameOfGlobal, gtm_char_t * valueOfGlobal, gtm_char_t * errorMessage );
  void Set( const gtm_char_t * nameOfGlobal, const gtm_char_t * valueOfGlobal, gtm_char_t * errorMessage );
  void Kill( const gtm_char_t * nameOfGlobal, gtm_char_t * errorMessage );
  void Order( const gtm_char_t * nameOfGlobal, gtm_char_t * valueOfIndex, gtm_char_t * errorMessage );
  void Query( const gtm_char_t * nameOfGlobal, gtm_char_t * valueOfIndex, gtm_char_t * errorMessage );
  void Lock( const gtm_char_t * nameOfGlobal, gtm_char_t * errorMessage );
  void Execute( const gtm_char_t * textOfCode, gtm_char_t * errorMessage );

  //
  //  Methods using std::string for arguments and Exceptions for error management.
  //
  void Get( const std::string & nameOfGlobal, std::string & valueOfGlobal );
  void Set( const std::string & nameOfGlobal, const std::string & valueOfGlobal );
  void Kill( const std::string & nameOfGlobal );
  void Order( const std::string & nameOfGlobal, std::string & valueOfIndex );
  void Query( const std::string & nameOfGlobal, std::string & valueOfIndex );
  void Lock( const std::string & nameOfGlobal );
  void Execute( const std::string & textOfCode );

  //
  //  Methods that return values by copy.
  //
  std::string Get( const std::string & nameOfGlobal );
  std::string Order( const std::string & nameOfGlobal );
  std::string Query( const std::string & nameOfGlobal );

private:

  //
  //   Member variables used to interact with GT.M API
  //


  // return of GT.M functions
  gtm_status_t  functionStatus;

  //
  //   The use of these member variables assumes that
  //   this class is not used in a multi-threaded environment.
  //
  gtm_char_t   statusMessage[maxMessageLength];
  gtm_char_t   errorMessage[maxMessageLength];
  gtm_char_t   nameOfGlobal[maxValueLength];
  gtm_char_t   valueOfGlobal[maxValueLength];
  gtm_char_t   valueOfIndex[maxValueLength];

  //
  //  Function Descriptors
  //
  ci_name_descriptor gtmget;
  ci_name_descriptor gtminit;
  ci_name_descriptor gtmkill;
  ci_name_descriptor gtmlock;
  ci_name_descriptor gtmorder;
  ci_name_descriptor gtmquery;
  ci_name_descriptor gtmset;
  ci_name_descriptor gtmxecute;

  gtm_string_t gtmget_str;
  gtm_string_t gtminit_str;
  gtm_string_t gtmkill_str;
  gtm_string_t gtmlock_str;
  gtm_string_t gtmorder_str;
  gtm_string_t gtmquery_str;
  gtm_string_t gtmset_str;
  gtm_string_t gtmxecute_str;

  char * gtmget_cstr;
  char * gtminit_cstr;
  char * gtmkill_cstr;
  char * gtmlock_cstr;
  char * gtmorder_cstr;
  char * gtmquery_cstr;
  char * gtmset_cstr;
  char * gtmxecute_cstr;

  //
  //  Structure to return values
  //
  gtm_string_t p_value;

  //
  // Terminal Structures
  //
  struct termios stderr_sav;
  struct termios stdin_sav;
  struct termios stdout_sav;
};

#endif
