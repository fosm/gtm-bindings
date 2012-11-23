/* This program is a driver to demonstrate a C main() program that calls in to GT.M.
   No claim of copyright is made with respect to this code.

   The expected result of running this program is as follows (the platform and GT.M version will vary)
     $ GTMCI=gtm_access.ci ./gtm_access
     Washington, DC
     England
     United States
     ^Capital("United States")
     GT.M V5.4-002B Linux x86_64
     gtmget2 failure: [,M7,Z150372994,]
     $

   Note that the last line is indeed an expected failure.

   This program is only a demonstration.  Please ensure that you have a correctly
   configured GT.M installation, correctly configured environment variables,
   with appropriate directories and files.

   DO NOT USE THIS CODE AS-IS IN A PRODUCTION ENVIRONMENT.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "gtmxc_types.h"

/* GT.M limits - you can use smaller numbers if your application is guaranteed to use smaller values
   but remember that this is a low-level programming interface that does not check for overflows
*/
#define maxcode 8192   /* maximum length of a line of code for the compiler / variable name */
#define maxmsg 2048    /* maximum length of a GT.M message */
#define maxname 32     /* one more than the maximum length of a GT.M name */
#define maxstr 1048576 /* maximum length of a value that GT.M can return */

/* GT.M call wrapper - if an error in call or untrappable error in GT.M, print error on STDERR, clean up and exit
 */
#define CALLGTM(xyz) status = xyz ;		\
  if (0 != status ) {				\
    gtm_zstatus( msg, maxmsg );			\
    fprintf(stderr, "Failure of %s with error: %s\n", #xyz, msg );	\
    gtm_exit();					\
    tcsetattr( 2, 0, &stderr_sav );		\
    tcsetattr( 1, 0, &stdout_sav );		\
    tcsetattr( 0, 0, &stdin_sav );		\
    return status ;				\
  }

#ifndef NULL
# define NULL ((void *) 0)

#endif

int main() {

  ci_name_descriptor gtmget, gtminit, gtmkill, gtmlock, gtmorder, gtmquery, gtmset, gtmxecute;
  gtm_char_t err[maxmsg], msg[maxmsg], value[maxstr];
  gtm_status_t status;
  gtm_string_t p_value, gtmget_str, gtminit_str, gtmkill_str, gtmlock_str, gtmorder_str, gtmquery_str, gtmset_str, gtmxecute_str;
  int i;
  struct termios stderr_sav, stdin_sav, stdout_sav;

  /* Initialization - string constants */
  gtm_char_t washington[] = "Washington, DC";
  gtm_char_t london[] = "London";

  /* Initialization - function descriptors for calling in to GT.M */
  gtmget_str.address = "gtmget"; gtmget_str.length = sizeof("gtmget")-1; gtmget.rtn_name=gtmget_str; gtmget.handle = NULL;
  gtminit_str.address = "gtminit"; gtminit_str.length = sizeof("gtminit")-1; gtminit.rtn_name=gtminit_str; gtminit.handle = NULL;
  gtmkill_str.address = "gtmkill"; gtmkill_str.length = sizeof("gtmkill")-1; gtmkill.rtn_name=gtmkill_str; gtmkill.handle = NULL;
  gtmlock_str.address = "gtmlock"; gtmlock_str.length = sizeof("gtmlock")-1; gtmlock.rtn_name=gtmlock_str; gtmlock.handle = NULL;
  gtmorder_str.address = "gtmorder"; gtmorder_str.length = sizeof("gtmorder")-1; gtmorder.rtn_name=gtmorder_str; gtmorder.handle = NULL;
  gtmquery_str.address = "gtmquery"; gtmquery_str.length = sizeof("gtmquery")-1; gtmquery.rtn_name=gtmquery_str; gtmquery.handle = NULL;
  gtmset_str.address = "gtmset"; gtmset_str.length = sizeof("gtmset")-1; gtmset.rtn_name=gtmset_str; gtmset.handle = NULL;
  gtmxecute_str.address = "gtmxecute"; gtmxecute_str.length = sizeof("gtmxecute")-1; gtmxecute.rtn_name=gtmxecute_str; gtmxecute.handle = NULL;

  /* Initialization - structure for return values */
  p_value.address = (gtm_char_t *) &value;
  p_value.length = 0;

  /* Ensure required environment variables are set.

     PLEASE NOTE - This is only a demonstration program.  You will almost certainly want
     other environment variables to be defined in a production environment.
  */
  if ((NULL == getenv( "gtm_dist" )) | (NULL == getenv( "gtmgbldir" )) | (NULL == getenv( "gtmroutines" )) | (NULL == getenv( "GTMCI" ))) return 1;

  /* Since GT.M changes the terminal attributes, save the attributes of stderr, stdin and stdout
     in order to restore them before exit
  */
  tcgetattr( 0, &stdin_sav );
  tcgetattr( 1, &stdout_sav );
  tcgetattr( 2, &stderr_sav );

  /* Initialize GT.M runtime */
  err[0] = '\0'; /* Clear error message buffer by putting null terminator in first byte */
  CALLGTM( gtm_init() );

  /* Initialize the GT.M access routines */
  p_value.address = ( gtm_char_t *) &value ; p_value.length = maxstr ;
  CALLGTM( gtm_cip( &gtminit, &err ));
  if (0 != strlen( err )) fprintf( stdout, "gtminit error: [%s]\n", err);

  /* Set a node - note that value can be an arbitrary blob, not just a null terminated string */
  p_value.address = (gtm_char_t *) &washington; p_value.length = strlen(washington);
  CALLGTM( gtm_cip( &gtmset, "^Capital(\"United States\")", &p_value, &err));
  if (0 != strlen( err )) fprintf( stdout, "gtmset1 failure: [%s]\n", err);

  /* Set another node */
  p_value.address = ( gtm_char_t *) &london ; p_value.length = strlen(london);
  CALLGTM( gtm_cip( &gtmset, "^Capital(\"England\")", &p_value, &err));
  if (0 != strlen( err )) fprintf( stdout, "gtmset2 failure: [%s]\n", err);

  /* Get the node first set & print it */
  p_value.address = ( gtm_char_t *) &value ; p_value.length = maxstr ;
  CALLGTM( gtm_cip( &gtmget, "^Capital(\"United States\")", &p_value, &err));
  if (0 != strlen( err )) fprintf( stdout, "gtmget1 failure: [%s]\n", err);
  else {
    for (i = 0 ; i < (int) p_value.length ; i++ ) fprintf( stdout, "%c", *(p_value.address+i));
    fprintf( stdout, "\n" );
  };

  /* Ordering through subscripts - first subscript */
  p_value.length = maxstr ; /* p.value.address already points to &value */
  CALLGTM( gtm_cip( &gtmorder, "^Capital(\"\")", &p_value, &err ));
  if (0 != strlen( err )) fprintf( stdout, "gtmorder failure: [%s]\n", err);
  else {
    for (i = 0 ; i < (int) p_value.length ; i++ ) fprintf( stdout, "%c", *(p_value.address+i));
    fprintf( stdout, "\n" );
  };

  /* Ordering through subscripts - next subscript */
  p_value.length = maxstr ; /* p.value.address already points to &value */
  CALLGTM( gtm_cip( &gtmorder, "^Capital(\"England\")", &p_value, &err ));
  if (0 != strlen( err )) fprintf( stdout, "gtmorder failure: [%s]\n", err);
  else {
    for (i = 0 ; i < (int) p_value.length ; i++ ) fprintf( stdout, "%c", *(p_value.address+i));
    fprintf( stdout, "\n" );
  };

  /* Ordering through nodes - next node */
  p_value.length = maxstr ; /* p.value.address already points to &value */
  CALLGTM( gtm_cip( &gtmquery, "^Capital(\"England\")", &p_value, &err ));
  if (0 != strlen( err )) fprintf( stdout, "gtmquery failure: [%s]\n", err);
  else {
    for (i = 0 ; i < (int) p_value.length ; i++ ) fprintf( stdout, "%c", *(p_value.address+i));
    fprintf( stdout, "\n" );
  };

  /* Get an M lock */
  CALLGTM( gtm_cip( &gtmlock, "+^CIDemo($Job)", &err ));
  if (0 != strlen( err )) fprintf( stdout, "gtmlock failure: [%s]\n", err);

  /* Xecute a string */
  CALLGTM( gtm_cip( &gtmxecute, "write $zversion,!", &err ));
  if (0 != strlen( err )) fprintf( stdout, "gtmxecute failure: [%s]\n", err);

  /* Kill a (sub)tree */
  CALLGTM( gtm_cip( &gtmkill, "^Capital", &err ));
  if (0 != strlen( err )) fprintf( stdout, "gtmkill failure: [%s]\n", err);

  /* Error trapped within GT.M - value does not exist */
  p_value.length = maxstr ; /* p.value.address already points to &value */
  CALLGTM( gtm_cip( &gtmget, "^Capital(\"United States\")", &p_value, &err ));
  if (0 != strlen( err )) fprintf( stdout, "gtmget2 failure: [%s]\n", err);
  else {
    for (i = 0 ; i < (int) p_value.length ; i++ ) fprintf( stdout, "%c", *(p_value.address+i));
    fprintf( stdout, "\n" );
  };

  /* Cleanup GT.M runtime */
  CALLGTM( gtm_exit( ));

  /* Restore terminal attributes */
  tcsetattr( 2, 0, &stderr_sav );
  tcsetattr( 1, 0, &stdout_sav );
  tcsetattr( 0, 0, &stdin_sav );

  return 0;

}
