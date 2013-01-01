#=========================================================================
#
#  Copyright OSEHRA
#
#  Licensed under the Apache License, Version 2.0 (the "License");
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
#  Test the Set, Get and Query methods
#

db = GTM()

#
#   Exercise the string API
#

globalName = '^Capital("US")'
setValue = 'Washington'

db.set( globalName, setValue )

globalName = '^Capital("UK")'
setValue = 'London'

db.set( globalName, setValue )

getValue = db.query( globalName )

print "Query of ", globalName, " = ", getValue

expectedValue = '^Capital("US")';

db.kill('^Capital')

if getValue != expectedValue:
  print "Test FAILED !"
  print "Expected value = ", expectedValue
  print "Received value = ", getValue
  sys.exit(1)


#
#   Exercise the same pattern with direct strings
#

db.set( '^Capital("US")', 'Washington' )
db.set( '^Capital("UK")', 'London' )

getValue = db.query( '^Capital("UK")' )

print "Query of ", globalName, " = ", getValue

expectedValue = '^Capital("US")';

db.kill('^Capital')

if getValue != expectedValue:
  print "Test FAILED !"
  print "Expected value = ", expectedValue
  print "Received value = ", getValue
  sys.exit(1)

