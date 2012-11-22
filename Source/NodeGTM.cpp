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

#include <cstring>

//
//  Static function to initialize object.
//
void NodeGTM::Initialize( v8::Handle<v8::Object> target)
{
 // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(New);

  tpl->SetClassName(v8::String::NewSymbol("Database"));

  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototypes
  tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("plusOne"),
      v8::FunctionTemplate::New(PlusOne)->GetFunction());

  tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("get"),
      v8::FunctionTemplate::New(Get)->GetFunction());

  v8::Persistent<v8::Function> constructor =
      v8::Persistent<v8::Function>::New( tpl->GetFunction() );

  target->Set(v8::String::NewSymbol("Database"), constructor);
}

//
//  Static Method to create a New object
//
v8::Handle<v8::Value> NodeGTM::New(const v8::Arguments& args)
{
  v8::HandleScope scope;

  NodeGTM * obj = new NodeGTM();

  obj->counter_ = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();

  obj->Wrap(args.This());

  return args.This();
}


//
// Constructor
//
NodeGTM::NodeGTM()
{
  // Initialize GTM
  CALLGTM( gtm_init() );

  this->counter_ = 0.0;
}


//
// Destructor
//
NodeGTM::~NodeGTM()
{
  // Cleanup GT.M runtime
  CALLGTM( gtm_exit() );
}

//
//  Simple method to add +1
//
v8::Handle<v8::Value> NodeGTM::PlusOne(const v8::Arguments& args)
{
  v8::HandleScope scope;

  NodeGTM * obj = ObjectWrap::Unwrap<NodeGTM >( args.This() );

  obj->counter_ += 1;

  return scope.Close(v8::Number::New(obj->counter_));
}


//
//  Get the value of a Global from GT.M
//
v8::Handle<v8::Value> NodeGTM::Get(const v8::Arguments& args)
{
  v8::HandleScope scope;

  NodeGTM * obj = ObjectWrap::Unwrap<NodeGTM >( args.This() );

  gtm_char_t valueOfGlobal[maxValueLength];
  gtm_char_t nameOfGlobal[maxValueLength];

  if( args[0]->IsString() )
    {
    v8::Local<v8::String> name = args[0]->ToString();
    name->WriteAscii( nameOfGlobal );
    std::cout << "Global name " << nameOfGlobal << std::endl;
    }
  else
    {
    std::cerr << "Argument was not a String" << std::endl;
    }

  obj->Get( nameOfGlobal );

  return scope.Close(v8::String::New(valueOfGlobal));
}


//
//  Get the value of a Global from GT.M
//
void NodeGTM::Get( gtm_char_t * nameOfGlobal )
{
  gtm_char_t errorMessage[maxMessageLength];
  gtm_char_t valueOfGlobal[maxValueLength];


  gtm_string_t p_value;

  p_value.address = ( xc_char_t *) &valueOfGlobal;
  p_value.length = maxValueLength ;


  gtm_string_t p_name;

  p_name.address = ( xc_char_t *) &nameOfGlobal;
  p_name.length = maxValueLength ;


  CALLGTM( gtm_ci( "gtmget", p_name, &p_value, &errorMessage ));

  if ( strlen( errorMessage ) != 0 )
    {
    std::cerr << errorMessage << std::endl;
    }
  else
    {
    for (int i = 0 ; i < (int) p_value.length ; i++ )
      {
      std::cout << *(p_value.address+i);
      }
    std::cout << std::endl;
    }
}


