// load gtm module
var gtm = require('./gtm');

// create gtm database connection
var db = new gtm.Database();

// Set a global
db.set('^Fibonacci(1)','1');
db.set('^Fibonacci(2)','1');
db.set('^Fibonacci(3)','2');
db.set('^Fibonacci(4)','3');
db.set('^Fibonacci(5)','5');
db.set('^Fibonacci(6)','8');

// Get the index that follows 4, it should be 5.
var nextindex = db.order('^Fibonacci(4)');
console.log('next index ='+nextindex);

// Set a global
db.set('^Apoptosis','Life is short');

// Kill the global
db.kill('^Apoptosis');

// modify the database
db.set('^Capital','Paris');

// query the database
var capital = db.get('^Capital');
console.log( capital );

// interact with the database
// db.set({'^Capital':'Washington'});

