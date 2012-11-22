/*=========================================================================
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

/*
 *   This programs exercises the passage of a string from M.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "gtmxc_types.h"

// GT.M limits
#define maxcode 8192     // maximum length of a line of code for the compiler / variable name
#define maxmsg  2048     // maximum length of a GT.M message
#define maxstr  1048576  // maximum length of a value

// GT.M call wrapper - if an error in call or untrappable error in GT.M, print error on STDERR, clean up and exit
#define CALLGTM(xyz) status = xyz ;		\
  if (0 != status ) {				\
    gtm_zstatus( msg, maxmsg );			\
    fprintf( stderr, "%s\n", msg );		\
    gtm_exit();					\
    return status ;				\
  }


int main()
{

  gtm_char_t err[maxmsg];
  gtm_char_t msg[maxmsg];
  gtm_char_t value[maxstr];
  gtm_char_t var[maxcode];
  gtm_char_t dststr[100];

  gtm_int_t inputnumber=5;
  gtm_int_t outputnumber=0;

  gtm_status_t status;
  gtm_string_t p_value;

  int failed=0;

  // Initialization
  p_value.address = (xc_char_t *) &value;
  p_value.length = 0;


  // Initialize GT.M runtime
  CALLGTM( gtm_init() );


  // Get the string from M routine
  CALLGTM( gtm_ci("getstring", dststr) )

  printf("\nstring returned: %s\n", dststr);

  if( strcmp(dststr,"Make it so!") != 0 )
    {
    failed = 1;
    }


  // Get the string from M routine
  CALLGTM( gtm_ci("getsquare", &inputnumber, &outputnumber) )

  printf("\nreturned value: %d\n", outputnumber);

  if( strcmp(dststr,"Make it so!") != 0 )
    {
    failed = 1;
    }


  // Cleanup GT.M runtime
  CALLGTM( gtm_exit() );

  if( failed == 0 )
    {
    printf("Test PASSED !\n");
    }
  else
    {
    printf("Test FAILED !\n");
    }

  return failed;
}
