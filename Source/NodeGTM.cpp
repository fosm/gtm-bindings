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
#include "GTM.h"

#include <cstring>

#define THROW_EXCEPTION(message) \
v8::ThrowException(v8::Exception::TypeError(v8::String::New(message))); \
    return scope.Close(v8::Undefined());

#define FUNCTION_PROTOTYPE(nodeName,cppName) \
  tpl->PrototypeTemplate()->Set(v8::String::NewSymbol(nodeName), \
      v8::FunctionTemplate::New(cppName)->GetFunction());


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
  FUNCTION_PROTOTYPE("get",Get);
  FUNCTION_PROTOTYPE("set",Set);
  FUNCTION_PROTOTYPE("kill",Kill);
  FUNCTION_PROTOTYPE("order",Order);
  FUNCTION_PROTOTYPE("query",Query);
  FUNCTION_PROTOTYPE("version",Version);
  FUNCTION_PROTOTYPE("about",About);
  FUNCTION_PROTOTYPE("execute",Execute);

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

  obj->Wrap(args.This());

  return args.This();
}


//
// Constructor
//
NodeGTM::NodeGTM()
{
  this->gtmConnection = new GTM();
}


//
// Destructor
//
NodeGTM::~NodeGTM()
{
  if( this->gtmConnection )
    {
    GTM * gtm = static_cast< GTM * >( this->gtmConnection );
    delete gtm;
    this->gtmConnection = NULL;
    }
}


//
//  Get the Version of the Interface
//
v8::Handle<v8::Value> NodeGTM::Version(const v8::Arguments& args)
{
  v8::HandleScope scope;

  //
  // Now we delegate the task to the GT.M interface
  //
  NodeGTM * obj = ObjectWrap::Unwrap<NodeGTM >( args.This() );

  GTM * gtm = static_cast< GTM * >( obj->gtmConnection );

  const char * version = gtm->Version();

  return scope.Close(v8::String::New( version ));
}


//
//  Get the Basic Information about the Interface
//
v8::Handle<v8::Value> NodeGTM::About(const v8::Arguments& args)
{
  v8::HandleScope scope;

  //
  // Now we delegate the task to the GT.M interface
  //
  NodeGTM * obj = ObjectWrap::Unwrap<NodeGTM >( args.This() );

  GTM * gtm = static_cast< GTM * >( obj->gtmConnection );

  const char * about = gtm->About();

  return scope.Close(v8::String::New( about ));
}


//
//  Get the value of a Global from GT.M
//
v8::Handle<v8::Value> NodeGTM::Get(const v8::Arguments& args)
{
  v8::HandleScope scope;

  gtm_char_t valueOfGlobal[maxValueLength];
  gtm_char_t nameOfGlobal[maxValueLength];
  gtm_char_t errorMessage[maxMessageLength];

  if( args[0]->IsString() )
    {
    v8::Local<v8::String> name = args[0]->ToString();
    name->WriteAscii( nameOfGlobal );
    }
  else
    {
    THROW_EXCEPTION("Argument was not a String");
    }

  //
  // Now we delegate the task to the GT.M interface
  //
  NodeGTM * obj = ObjectWrap::Unwrap<NodeGTM >( args.This() );

  GTM * gtm = static_cast< GTM * >( obj->gtmConnection );

  gtm->Get( nameOfGlobal, valueOfGlobal, errorMessage );

  if ( strlen( errorMessage ) != 0 )
    {
    THROW_EXCEPTION( errorMessage );
    }

  return scope.Close(v8::String::New( valueOfGlobal ));
}


//
//  Set the value of a Global from GT.M
//
v8::Handle<v8::Value> NodeGTM::Set(const v8::Arguments& args)
{
  v8::HandleScope scope;

  gtm_char_t valueOfGlobal[maxValueLength];
  gtm_char_t nameOfGlobal[maxValueLength];
  gtm_char_t errorMessage[maxValueLength];


  if( args.Length() < 2 )
    {
    THROW_EXCEPTION("Wrong number of arguments. Expected two");
    }


  if( args[0]->IsString() )
    {
    v8::Local<v8::String> name = args[0]->ToString();
    name->WriteAscii( nameOfGlobal );
    }
  else
    {
    THROW_EXCEPTION("First argument was not a String");
    }


  if( args[1]->IsString() )
    {
    v8::Local<v8::String> name = args[1]->ToString();
    name->WriteAscii( valueOfGlobal );
    }
  else
    {
    THROW_EXCEPTION("Second argument was not a String");
    }

  //
  // Now we delegate the task to the GT.M interface
  //
  NodeGTM * obj = ObjectWrap::Unwrap<NodeGTM >( args.This() );

  GTM * gtm = static_cast< GTM * >( obj->gtmConnection );

  gtm->Set( nameOfGlobal, valueOfGlobal, errorMessage );

  if ( strlen( errorMessage ) != 0 )
    {
    THROW_EXCEPTION( errorMessage );
    }

  //
  // TODO: Discuss with community if this return is a good idea...
  //
  return scope.Close( args[1]->ToString() );
}


//
//  Kill (delete) a Global through GT.M
//
v8::Handle<v8::Value> NodeGTM::Kill(const v8::Arguments& args)
{
  v8::HandleScope scope;

  gtm_char_t nameOfGlobal[maxValueLength];
  gtm_char_t errorMessage[maxValueLength];


  if( args.Length() != 1 )
    {
    THROW_EXCEPTION("Wrong number of arguments. Expected one");
    }


  if( args[0]->IsString() )
    {
    v8::Local<v8::String> name = args[0]->ToString();
    name->WriteAscii( nameOfGlobal );
    }
  else
    {
    THROW_EXCEPTION("First argument was not a String");
    }


  //
  // Now we delegate the task to the GT.M interface
  //
  NodeGTM * obj = ObjectWrap::Unwrap<NodeGTM >( args.This() );

  GTM * gtm = static_cast< GTM * >( obj->gtmConnection );

  gtm->Kill( nameOfGlobal, errorMessage );

  if ( strlen( errorMessage ) != 0 )
    {
    THROW_EXCEPTION( errorMessage );
    }

  //
  // TODO: Discuss with community if this return is a good idea...
  //
  return scope.Close( args[0]->ToString() );
}


//
//  Get the value of the next index in a Global from GT.M
//
v8::Handle<v8::Value> NodeGTM::Order(const v8::Arguments& args)
{
  v8::HandleScope scope;

  gtm_char_t valueOfIndex[maxValueLength];
  gtm_char_t nameOfGlobal[maxValueLength];
  gtm_char_t errorMessage[maxMessageLength];


  if( args[0]->IsString() )
    {
    v8::Local<v8::String> name = args[0]->ToString();
    name->WriteAscii( nameOfGlobal );
    }
  else
    {
    THROW_EXCEPTION("Argument was not a String");
    }


  //
  // Now we delegate the task to the GT.M interface
  //
  NodeGTM * obj = ObjectWrap::Unwrap<NodeGTM >( args.This() );

  GTM * gtm = static_cast< GTM * >( obj->gtmConnection );

  gtm->Order( nameOfGlobal, valueOfIndex, errorMessage );

  if ( strlen( errorMessage ) != 0 )
    {
    THROW_EXCEPTION( errorMessage );
    }

  return scope.Close(v8::String::New( valueOfIndex ));
}


//
//  Get the value of the next index in a Global from GT.M
//
v8::Handle<v8::Value> NodeGTM::Query(const v8::Arguments& args)
{
  v8::HandleScope scope;

  gtm_char_t valueOfIndex[maxValueLength];
  gtm_char_t nameOfGlobal[maxValueLength];
  gtm_char_t errorMessage[maxMessageLength];


  if( args[0]->IsString() )
    {
    v8::Local<v8::String> name = args[0]->ToString();
    name->WriteAscii( nameOfGlobal );
    }
  else
    {
    THROW_EXCEPTION("Argument was not a String");
    }


  //
  // Now we delegate the task to the GT.M interface
  //
  NodeGTM * obj = ObjectWrap::Unwrap<NodeGTM >( args.This() );

  GTM * gtm = static_cast< GTM * >( obj->gtmConnection );

  gtm->Query( nameOfGlobal, valueOfIndex, errorMessage );

  if ( strlen( errorMessage ) != 0 )
    {
    THROW_EXCEPTION( errorMessage );
    }

  return scope.Close(v8::String::New( valueOfIndex ));
}


//
//  Execute code passed in an input string to GT.M
//
v8::Handle<v8::Value> NodeGTM::Execute(const v8::Arguments& args)
{
  v8::HandleScope scope;

  gtm_char_t textOfCode[maxValueLength];
  gtm_char_t errorMessage[maxMessageLength];


  if( args[0]->IsString() )
    {
    v8::Local<v8::String> name = args[0]->ToString();
    name->WriteAscii( textOfCode );
    }
  else
    {
    THROW_EXCEPTION("Argument was not a String");
    }


  //
  // Now we delegate the task to the GT.M interface
  //
  NodeGTM * obj = ObjectWrap::Unwrap<NodeGTM >( args.This() );

  GTM * gtm = static_cast< GTM * >( obj->gtmConnection );

  gtm->Execute( textOfCode, errorMessage );

  if ( strlen( errorMessage ) != 0 )
    {
    THROW_EXCEPTION( errorMessage );
    }

  return scope.Close(v8::String::New( errorMessage ));
}

