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
#ifndef __NodeGTM_h
#define __NodeGTM_h

#define BUILDING_NODE_EXTENSION

#include <node.h>

#include <iostream>

extern "C" {
#include "gtmxc_types.h"
}

// maximum length of a GT.M message
const unsigned int maxMessageLength = 2048;
const unsigned int maxValueLength = 1048576;

// GT.M call wrapper - if an error in call or untrappable error in GT.M, print error on STDERR, clean up and exit
#define CALLGTM(functioncall) \
  this->status = functioncall ;		\
  if (0 != this->status ) {				\
    gtm_zstatus( this->message, maxMessageLength );			\
    std::cerr << this->message << std::endl;		\
    gtm_exit();					\
  }


//
//
//  Interface class between Node.js API and GTM API.
//
//
class NodeGTM : public node::ObjectWrap
{
public:
  static void Initialize( v8::Handle<v8::Object> target);

private:
  NodeGTM();
  virtual ~NodeGTM();

  static v8::Handle<v8::Value>  New(const v8::Arguments& args);
  static v8::Handle<v8::Value>  PlusOne(const v8::Arguments& args);
  static v8::Handle<v8::Value>  Get(const v8::Arguments& args);

  double counter_;

  //
  //   Member variables used to interact with GT.M API
  //

  gtm_status_t status;  // return of GT.M functions
  gtm_char_t   message[maxMessageLength];

  //
  // Internal API to interact with GT.M
  //
  void Get( const gtm_char_t * nameOfGlobal, gtm_char_t * valueOfGlobal );
};

#endif
