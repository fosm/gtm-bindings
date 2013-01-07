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

var db = new gtm.Database();

console.log( db.about() );

console.log( db.version() );

db.set("^FibonacciA", "1");
db.set("^FibonacciB", "1");

getValue = "Initially empty";

for ( i=0; i<10; i++ ) {
  db.execute("set ^FibonacciValue=^FibonacciA+^FibonacciB");
  db.execute("set ^FibonacciB=^FibonacciA");
  db.execute("set ^FibonacciA=^FibonacciValue");
  getValue = db.get("^FibonacciValue");
  console.log( "Fibonacci value = " + getValue );
}
db.kill("^FibonacciA");
db.kill("^FibonacciB");
db.kill("^FibonacciValue");

