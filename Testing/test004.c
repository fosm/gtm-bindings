/* This program is a driver to demonstrate a C main() program that calls in to GT.M.
   No claim of copyright is made with respect to this code.

   On x86 GNU/Linux (64-bit Ubuntu 10.10), this program was compiled and run with:
     gcc -c gtm_access.c -I$gtm_dist
     gcc gtm_access.o -o gtm_access -L $gtm_dist -Wl,-rpath=$gtm_dist -lgtmshr
     ./gtm_access ; stty sane

   This program is only a demonstration.  Please ensure that you have a correctly
   configured GT.M installation, correctly configured environment variables,
   with appropriate directories and files.

   Please do not use this code as-is in a production environment.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gtmxc_types.h"

// GT.M limits - you can use smaller numbers if your application doesn't need such large strings
#define maxcode 8192 // maximum length of a line of code for the compiler / variable name
#define maxmsg 2048 // maximum length of a GT.M message
#define maxstr 1048576 // maximum length of a value

// GT.M call wrapper - if an error in call or untrappable error in GT.M, print error on STDERR, clean up and exit
#define CALLGTM(xyz) status = xyz ;		\
  if (0 != status ) {				\
    gtm_zstatus( msg, maxmsg );			\
    fprintf( stderr, "%s\n", msg );		\
    gtm_exit();					\
    return status ;				\
  }

int main() {

  int i;
  gtm_char_t err[maxmsg], msg[maxmsg], value[maxstr];
  gtm_status_t status;
  gtm_string_t p_value;

  // Initialization
  p_value.address = (xc_char_t *) &value;
  p_value.length = 0;
    
  // Set environment variables - not needed if these are already defined in the environment
  //
  // PLEASE NOTE - This is only a demonstration program.  You will almost certainly want
  // other environment variables to be defined in a production environment.
  //
  if (NULL == getenv( "gtm_dist" )) putenv( "gtm_dist=/usr/lib/fis-gtm/V5.4-001_x86_64" );
  if (NULL == getenv( "gtmgbldir" )) putenv("gtmgbldir=/home/kbhaskar/.fis-gtm/V5.4-001_x86_64/g/gtm.gld");
  if (NULL == getenv( "gtmroutines" )) \
    putenv("gtmroutines=/home/kbhaskar/.fis-gtm/V5.4-001_x86_64/o(/home/kbhaskar/.fis-gtm/V5.4-001_x86_64/r /home/kbhaskar/.fis-gtm/r) /usr/lib/fis-gtm/V5.4-001_x86_64");
  if (NULL == getenv( "GTMCI" )) putenv("GTMCI=/home/kbhaskar/demo/gtm_access.ci");
 
  // Initialize GT.M runtime
  CALLGTM( gtm_init() );

  // Initialize the GT.M access routines
  p_value.address = ( xc_char_t *) &value ; p_value.length = maxstr ;
  CALLGTM( gtm_ci( "gtminit", &err ));
  if (0 != strlen( err )) fprintf( stdout, "%s\n", err);

  // Set a node - note that value can be an arbitrary blob, not just a null terminated string
  gtm_char_t washington[] = "Washington, DC";
  p_value.address = (xc_char_t *) &washington; p_value.length = strlen( "Washington, DC" );
  CALLGTM( gtm_ci( "gtmset", "^Capital(\"United States\")", &p_value, &err ));
  if (0 != strlen( err )) fprintf( stdout, "%s\n", err);

  // Set another node
  gtm_char_t london[] = "London";
  p_value.address = ( xc_char_t *) &london ; p_value.length = strlen( "London" );
  CALLGTM( gtm_ci( "gtmset", "^Capital(\"England\")", &p_value, &err ));
  if (0 != strlen( err )) fprintf( stdout, "%s\n", err);

  // Get the node first set & print it
  p_value.address = ( xc_char_t *) &value ; p_value.length = maxstr ;
  CALLGTM( gtm_ci( "gtmget", "^Capital(\"United States\")", &p_value, &err ));
  if (0 != strlen( err )) fprintf( stdout, "%s\n", err);
  else {
    for (i = 0 ; i < (int) p_value.length ; i++ ) fprintf( stdout, "%c", *(p_value.address+i));
    fprintf( stdout, "\n" );
  };

  // Ordering through nodes - next subscript
  p_value.length = maxstr ; // p.value.address already points to &value
  CALLGTM( gtm_ci( "gtmorder", "^Capital(\"England\")", &p_value, &err ));
  if (0 != strlen( err )) fprintf( stdout, "%s\n", err);
  else {
    for (i = 0 ; i < (int) p_value.length ; i++ ) fprintf( stdout, "%c", *(p_value.address+i));
    fprintf( stdout, "\n" );
  };

  // Ordering through nodes - next node
  p_value.length = maxstr ; // p.value.address already points to &value
  CALLGTM( gtm_ci( "gtmquery", "^Capital(\"England\")", &p_value, &err ));
  if (0 != strlen( err )) fprintf( stdout, "%s\n", err);
  else {
    for (i = 0 ; i < (int) p_value.length ; i++ ) fprintf( stdout, "%c", *(p_value.address+i));
    fprintf( stdout, "\n" );
  };

  // Get an M lock
  CALLGTM( gtm_ci( "gtmlock", "+^CIDemo($Job)", &err ));
  if (0 != strlen( err )) fprintf( stdout, "%s\n", err);

  // Xecute a string
  CALLGTM( gtm_ci( "gtmxecute", "write $zversion,! zsystem \"lke show\"", &err ));
  if (0 != strlen( err )) fprintf( stdout, "%s\n", err);

  // Kill a (sub)tree
  CALLGTM( gtm_ci( "gtmkill", "^Capital", &err ));
  if (0 != strlen( err )) fprintf( stdout, "%s\n", err);

  // Error trappable within GT.M - value does not exist
  p_value.length = maxstr ; // p.value.address already points to &value
  CALLGTM( gtm_ci( "gtmget", "^Capital(\"United States\")", &p_value, &err ));
  if (0 != strlen( err )) fprintf( stdout, "%s\n", err);
  else {
    for (i = 0 ; i < (int) p_value.length ; i++ ) fprintf( stdout, "%c", *(p_value.address+i));
    fprintf( stdout, "\n" );
  };

  // Cleanup GT.M runtime
  CALLGTM( gtm_exit( ));

  return 0;

}
