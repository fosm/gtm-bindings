# load gtm module
from gtm import GTM

db = GTM()

print db.about()

print db.version()

db.set("^FibonacciA", "1")
db.set("^FibonacciB", "1")

getValue = "Initially empty"

for i in xrange(1,10):
  db.execute("set ^FibonacciValue=^FibonacciA+^FibonacciB")
  db.execute("set ^FibonacciB=^FibonacciA")
  db.execute("set ^FibonacciA=^FibonacciValue")
  getValue = db.get("^FibonacciValue")
  print "Fibonacci value = ", getValue

db.kill("^FibonacciA")
db.kill("^FibonacciB")
db.kill("^FibonacciValue")

