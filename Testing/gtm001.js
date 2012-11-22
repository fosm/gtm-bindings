// load gtm module
var gtm = require('./gtm');

// create gtm database connection
var db = new gtm.Database();

// Print the GTM version
console.log(db.plusOne());
console.log(db.plusOne());
console.log(db.plusOne());

// interact with the database
// db.set({'^Capital':'Washington'});

