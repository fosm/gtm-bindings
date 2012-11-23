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


//
// Constructor
//
GTM::GTM()
{
  // Initialize GTM
  CALLGTM( gtm_init() );
}


//
// Destructor
//
GTM::~GTM()
{
  // Cleanup GT.M runtime
  CALLGTM( gtm_exit() );
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
  std::cout << "calling Get( " << globalName << " ) " << std::endl;

  gtm_string_t p_value;

  p_value.address = static_cast< xc_char_t *>( globalValue );
  p_value.length = maxValueLength ;

  CALLGTM( gtm_ci( "gtmget", globalName, &p_value, &errorMessage ));
}


//
//  Set the value of a Global from GT.M
//
void GTM::Set( const gtm_char_t * nameOfGlobal, const gtm_char_t * valueOfGlobal, gtm_char_t * errorMessage )
{
  std::cout << "calling Set( " << nameOfGlobal << " ) = " << valueOfGlobal << std::endl;

  gtm_string_t p_value;

  gtm_char_t * value = const_cast< gtm_char_t *>( valueOfGlobal );
  p_value.address = static_cast< xc_char_t * >( value );

  p_value.length = strlen( valueOfGlobal );

  CALLGTM( gtm_ci( "gtmset", nameOfGlobal, &p_value, &errorMessage ));
}


//
//  Kill a Global in GT.M
//
void GTM::Kill( const gtm_char_t * nameOfGlobal, gtm_char_t * errorMessage )
{
  std::cout << "calling Kill( " << nameOfGlobal << " ) " << std::endl;

  CALLGTM( gtm_ci( "gtmkill", nameOfGlobal, &errorMessage ));
}


//
//  Get the value of the next index in a Global from GT.M
//
void GTM::Order( const gtm_char_t * nameOfGlobal, gtm_char_t * valueOfIndex, gtm_char_t * errorMessage )
{
  std::cout << "calling Order( " << nameOfGlobal << " ) " << std::endl;

  gtm_string_t p_value;

  p_value.address = static_cast< xc_char_t *>( valueOfIndex );
  p_value.length = maxValueLength ;

  CALLGTM( gtm_ci( "gtmorder", nameOfGlobal, &p_value, &errorMessage ));
}


//
//  Get the value of the next index in a Global from GT.M
//
void GTM::Query( const gtm_char_t * nameOfGlobal, gtm_char_t * valueOfIndex, gtm_char_t * errorMessage )
{
  std::cout << "calling Query( " << nameOfGlobal << " ) " << std::endl;

  gtm_string_t p_value;

  p_value.address = static_cast< xc_char_t *>( valueOfIndex );
  p_value.length = maxValueLength ;

  CALLGTM( gtm_ci( "gtmquery", nameOfGlobal, &p_value, &errorMessage ));
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
