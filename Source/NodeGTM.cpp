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

#define BUILDING_NODE_EXTENSION

#include <node.h>
#include <v8.h>

#include "NodeGTM.h"

using namespace v8;

Handle<Value> Method(const Arguments& args) {
  HandleScope scope;
  return scope.Close(String::New("world"));
}

void Initialize(Handle<Object> target) {
  target->Set(String::NewSymbol("hello"),
      FunctionTemplate::New(Method)->GetFunction());
}

NODE_MODULE(gtm, Initialize)
