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
  static v8::Handle<v8::Value>  Get(const v8::Arguments& args);
  static v8::Handle<v8::Value>  Set(const v8::Arguments& args);
  static v8::Handle<v8::Value>  Kill(const v8::Arguments& args);
  static v8::Handle<v8::Value>  Order(const v8::Arguments& args);
  static v8::Handle<v8::Value>  Query(const v8::Arguments& args);

  void * gtmConnection;
};

#endif
