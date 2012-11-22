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

#include "NodeGTM.h"

//
// Constructor
//
NodeGTM::NodeGTM()
{
  // Initialize GTM
  CALLGTM( gtm_init() );
}


//
// Destructor
//
NodeGTM::~NodeGTM()
{
  // Cleanup GT.M runtime
  CALLGTM( gtm_exit() );
}


using namespace v8;

Handle<Value> Database(const Arguments& args) {
  HandleScope scope;

  Local<Object> obj = Object::New();


  obj->Set(String::NewSymbol("Version"), String::New("V6.0"));

  return scope.Close(obj);
}

void Initialize(Handle<Object> target) {

  target->Set(String::NewSymbol("Database"),
      FunctionTemplate::New(Database)->GetFunction());
}

NODE_MODULE(gtm, Initialize)
