
library(gtm)

db <- GTM()


cat("About :", db.About(), "\n")

cat("Version :", db.Version(), "\n")

db.Execute('write $ZVERSION,!')

db.Lock('^Capital')

db.Set('^Capital("US")','Washington')

