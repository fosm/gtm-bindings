# load gtm module
from gtm import GTM

db = GTM()

print db.About()

print db.Version()

db.Set("^Capital","Washington")

value = db.Get("^Capital")

print value

db.Kill("^Capital")

db.Set('^Person(1,"name",)',"John Lennon");
db.Set('^Person(1,"address")',"Abby Road");

print db.Query('^Person(1)')

print db.Order('^Person(1,"address")')

# help(db)
