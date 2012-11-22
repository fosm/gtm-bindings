find_path(GTM_DIST NAMES libgtmshr.so
PATHS
 "/usr/lib/fis-gtm/V5.5-000_x86_64"
 "/usr/lib/fis-gtm/V6.0-000_x86_64"
 )

find_path(GTM_ROUTINES PATHS $ENV{gtmroutines})

