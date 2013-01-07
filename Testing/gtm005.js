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
//  Test the Set, Get and Order methods
//

var db = new gtm.Database();

//
//   Exercise the string API
//

var globalName = '^Capital("US")';
var setValue = 'Washington';

db.set( globalName, setValue );

globalName = '^Capital("UK")';
setValue = 'London';

db.set( globalName, setValue );

var getValue = db.order( globalName );

console.log( "Order of "+ globalName+" = "+getValue);

var expectedValue = "US";

db.kill('^Capital');

if ( getValue != expectedValue ) {
  console.log( "Test FAILED !" );
  console.log( "Expected value = " + expectedValue );
  console.log( "Received value = " + getValue );
//  sys.exit(1);
}


//
//   Exercise the same pattern with direct strings
//

db.set( '^Capital("US")', 'Washington' );
db.set( '^Capital("UK")', 'London' );

getValue = db.order( '^Capital("UK")' );

console.log( "Order of " + globalName + " = " + getValue );

expectedValue = "US";

db.kill('^Capital');

if ( getValue != expectedValue ) {
  console.log( "Test FAILED !" );
  console.log( "Expected value = " + expectedValue );
  console.log( "Received value = " + getValue );
  // sys.exit(1);
}
