# load gtm module
from gtm import GTM

db = GTM()

print db.about()

print db.version()

db.set("^Capital","Washington")

value = db.get("^Capital")

print value

db.kill("^Capital")

db.set('^Person(1,"name")',"John Lennon");
db.set('^Person(1,"address")',"Abby Road");
db.set('^Person(1,"phone")',"555-1234");

print db.query('^Person(1)')

print db.order('^Person(1,"address")')

db.execute('write $ZVERSION,!')

# help(db)
