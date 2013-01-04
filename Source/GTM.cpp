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

#include "GTM.h"
#include "GTMException.h"

#include "mjsConfigure.h"

#include <iostream>
#include <cstring>


#define  THROW_EXCEPTION_IF_ERROR( errorMessage ) \
  if( strlen( errorMessage ) != 0 ) \
    { \
    GTMException excp( errorMessage ); \
    throw(excp); \
    }


#define INITIALIZE_FUNCTION_DESCRIPTOR(functionname) \
  functionname##_cstr = new char[sizeof(#functionname)]; \
  strncpy(functionname##_cstr,#functionname,sizeof(#functionname)); \
  functionname##_str.address = functionname##_cstr;  \
  functionname##_str.length = sizeof(#functionname)-1; \
  functionname.rtn_name=functionname##_str;  \
  functionname.handle = NULL;


#define RELEASE_FUNCTION_DESCRIPTOR(functionname) \
  delete [] functionname##_cstr;


//
// Constructor
//
GTM::GTM()
{

  //
  // Since GT.M changes the terminal attributes, save the attributes of stderr, stdin and stdout
  // in order to restore them before exit
  //
  tcgetattr( 0, &stdin_sav );
  tcgetattr( 1, &stdout_sav );
  tcgetattr( 2, &stderr_sav );

  //
  // Clear error message buffer by putting null terminator in first byte
  //
  errorMessage[0] = '\0';

  //
  // Initialize GTM
  //
  CALLGTM( gtm_init() );

  //
  // Initialization - function descriptors for calling in to GT.M
  //
  INITIALIZE_FUNCTION_DESCRIPTOR(gtmget);
  INITIALIZE_FUNCTION_DESCRIPTOR(gtmkill);
  INITIALIZE_FUNCTION_DESCRIPTOR(gtmlock);
  INITIALIZE_FUNCTION_DESCRIPTOR(gtmorder);
  INITIALIZE_FUNCTION_DESCRIPTOR(gtmquery);
  INITIALIZE_FUNCTION_DESCRIPTOR(gtmset);
  INITIALIZE_FUNCTION_DESCRIPTOR(gtmxecute);

  //
  // Initialization - structure for return values
  //
  this->p_value.address = NULL;
  this->p_value.length = 0;
}


//
// Destructor
//
GTM::~GTM()
{
  // Cleanup GT.M runtime
  CALLGTM( gtm_exit() );

  //
  // Release resources of function descriptors for calling in to GT.M
  //
  RELEASE_FUNCTION_DESCRIPTOR(gtmget);
  RELEASE_FUNCTION_DESCRIPTOR(gtmkill);
  RELEASE_FUNCTION_DESCRIPTOR(gtmlock);
  RELEASE_FUNCTION_DESCRIPTOR(gtmorder);
  RELEASE_FUNCTION_DESCRIPTOR(gtmquery);
  RELEASE_FUNCTION_DESCRIPTOR(gtmset);
  RELEASE_FUNCTION_DESCRIPTOR(gtmxecute);

  // Restore terminal attributes
  tcsetattr( 2, 0, &stderr_sav );
  tcsetattr( 1, 0, &stdout_sav );
  tcsetattr( 0, 0, &stdin_sav );
}


//
// Return the Version of the Interface
//
const char * GTM::Version() const
{
  return MJS_VERSION_STRING;
}


//
// Return basic information about the Interface
//
const char * GTM::About() const
{
  return "\nDeveloped by multiple contributors\nDistributed under the Apache 2.0 License.\n";
}


//
//  Get the value of a Global from GT.M
//
void GTM::Get( const gtm_char_t * globalName, gtm_char_t * globalValue, gtm_char_t * errorMessage )
{
  this->p_value.address = static_cast< gtm_char_t *>( globalValue );
  this->p_value.length = maxValueLength ;

  CALLGTM( gtm_cip( &gtmget, globalName, &(this->p_value), &errorMessage ));

  // Add null terminator in string
  globalValue[p_value.length]='\0';
}


//
//  Set the value of a Global from GT.M
//
void GTM::Set( const gtm_char_t * nameOfGlobal, const gtm_char_t * valueOfGlobal, gtm_char_t * errorMessage )
{
  gtm_char_t * value = const_cast< gtm_char_t *>( valueOfGlobal );
  this->p_value.address = static_cast< gtm_char_t * >( value );
  this->p_value.length = strlen( valueOfGlobal );

  CALLGTM( gtm_cip( &(this->gtmset), nameOfGlobal, &(this->p_value), &errorMessage ));
}


//
//  Kill a Global in GT.M
//
void GTM::Kill( const gtm_char_t * nameOfGlobal, gtm_char_t * errorMessage )
{
  CALLGTM( gtm_cip( &(this->gtmkill), nameOfGlobal, &errorMessage ));
}


//
//  Get the value of the next index in a Global from GT.M
//
void GTM::Order( const gtm_char_t * nameOfGlobal, gtm_char_t * valueOfIndex, gtm_char_t * errorMessage )
{
  this->p_value.address = static_cast< gtm_char_t *>( valueOfIndex );
  this->p_value.length = maxValueLength ;

  CALLGTM( gtm_cip( &(this->gtmorder), nameOfGlobal, &(this->p_value), &errorMessage ));

  // Add null terminator in string
  valueOfIndex[this->p_value.length]='\0';
}


//
//  Get the value of the next index in a Global from GT.M
//
void GTM::Query( const gtm_char_t * nameOfGlobal, gtm_char_t * valueOfIndex, gtm_char_t * errorMessage )
{
  this->p_value.address = static_cast< gtm_char_t *>( valueOfIndex );
  this->p_value.length = maxValueLength ;

  CALLGTM( gtm_cip( &(this->gtmquery), nameOfGlobal, &(this->p_value), &errorMessage ));

  // Add null terminator in string
  valueOfIndex[this->p_value.length]='\0';
}


//
//   Execute M code passed in an input string to GT.M
//
void GTM::Execute( const gtm_char_t * textOfCode, gtm_char_t * errorMessage )
{
  CALLGTM( gtm_cip( &(this->gtmxecute), textOfCode, &errorMessage ));
}


//
//   Lock a global in GT.M
//
void GTM::Lock( const gtm_char_t * nameOfGlobal, gtm_char_t * errorMessage )
{
  CALLGTM( gtm_cip( &(this->gtmlock), nameOfGlobal, &errorMessage ));
}


//
//  Get the value of a Global from GT.M
//
void GTM::Get( const std::string & globalName, std::string & globalValue )
{
  this->Get( globalName.c_str(), this->valueOfGlobal, this->errorMessage );

  THROW_EXCEPTION_IF_ERROR( this->errorMessage );

  globalValue = this->valueOfGlobal;
}


//
//  Set the value of a Global from GT.M
//
void GTM::Set( const std::string & globalName, const std::string & globalValue )
{
  this->Set( globalName.c_str(), globalValue.c_str(), this->errorMessage );

  THROW_EXCEPTION_IF_ERROR( this->errorMessage );
}


//
//  Kill a Global in GT.M
//
void GTM::Kill( const std::string & globalName )
{
  this->Kill( globalName.c_str(), this->errorMessage );

  THROW_EXCEPTION_IF_ERROR( this->errorMessage );
}


//
//  Get the value of the next index in a Global from GT.M
//
void GTM::Order( const std::string & globalName, std::string & indexValue )
{
  this->Order( globalName.c_str(), this->valueOfIndex, this->errorMessage );

  THROW_EXCEPTION_IF_ERROR( this->errorMessage );

  indexValue = this->valueOfIndex;
}


//
//  Get the value of the next index in a Global from GT.M
//
void GTM::Query( const std::string & globalName, std::string & indexValue )
{
  this->Query( globalName.c_str(), this->valueOfIndex, this->errorMessage );

  THROW_EXCEPTION_IF_ERROR( this->errorMessage );

  indexValue = this->valueOfIndex;
}


//
//   Execute M code passed in an input string to GT.M
//
void GTM::Execute( const std::string & textOfCode )
{
  this->Execute( textOfCode.c_str(), this->errorMessage );

  THROW_EXCEPTION_IF_ERROR( this->errorMessage );
}


//
//   Lock a global in GT.M
//
void GTM::Lock( const std::string & nameOfGlobal )
{
  this->Lock( nameOfGlobal.c_str(), this->errorMessage );

  THROW_EXCEPTION_IF_ERROR( this->errorMessage );
}


//
//  Get the value of a Global from GT.M
//
std::string GTM::Get( const std::string & globalName )
{
  this->Get( globalName.c_str(), this->valueOfGlobal, this->errorMessage );

  THROW_EXCEPTION_IF_ERROR( this->errorMessage );

  return this->valueOfGlobal;
}


//
//  Get the value of the next index in a Global from GT.M
//
std::string GTM::Order( const std::string & globalName )
{
  this->Order( globalName.c_str(), this->valueOfIndex, this->errorMessage );

  THROW_EXCEPTION_IF_ERROR( this->errorMessage );

  return this->valueOfIndex;
}


//
//  Get the value of the next index in a Global from GT.M
//
std::string GTM::Query( const std::string & globalName )
{
  this->Query( globalName.c_str(), this->valueOfIndex, this->errorMessage );

  THROW_EXCEPTION_IF_ERROR( this->errorMessage );

  return this->valueOfIndex;
}

