// load gtm module
var gtm = require('gtm');

// create gtm database connection
var db = new gtm.Database();

console.log("\n");
console.log('Node.js Version: ' + process.version);

console.log('Version: ' + db.version());

console.log('About: ' + db.about());

// Set a global
db.set('^Person',"John Lennon");

// Get the global
var name = db.get('^Person');

console.log('^Person '+name);

// Kill the global
db.kill('^Person');

db.execute('write $ZVERSION,!');

