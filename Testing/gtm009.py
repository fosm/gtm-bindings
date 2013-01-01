#=========================================================================
#
#  Copyright OSEHRA
#
#  Licensed under the Apache License, Version 2.0 (the "License")
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#         http://www.apache.org/licenses/LICENSE-2.0.txt
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
#=========================================================================*/


# load gtm module
from gtm import GTM

#
#  Test the Lock method
#

db = GTM()

globalName = "^ValueCounter"
setValue = "0"
getValue = "Initially empty"

db.lock( globalName )

db.set( globalName, setValue )

for i in xrange(0,9):
  db.execute("set ^ValueCounter=^ValueCounter+1")
  getValue = db.get( globalName )
  print "counter = ", getValue

print "Final Counter Value = ", getValue

db.kill( "^ValueCounter" )

