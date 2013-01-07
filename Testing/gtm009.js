//=========================================================================
//
//  Copyright OSEHRA
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//         http://www.apache.org/licenses/LICENSE-2.0.txt
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
//=========================================================================*/


// load gtm module
var gtm = require('gtm');

//
// Test the Lock method
//

var db = new gtm.Database();

var globalName = "^ValueCounter";
var setValue = "0";
var getValue = "Initially empty";

db.lock( globalName );

db.set( globalName, setValue );

for ( i=0; i<10; i++ ) {
  db.execute("set ^ValueCounter=^ValueCounter+1");
  getValue = db.get( globalName );
  console.log( "counter = " + getValue );
  }
console.log( "Final Counter Value = " + getValue );

db.kill( "^ValueCounter" );

