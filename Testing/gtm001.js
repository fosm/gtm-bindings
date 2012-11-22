// load gtm module
var gtm = require('./gtm');

// create gtm database connection
var db = new gtm.Database();

// query the database
console.log(db.get('^Capital'));

// interact with the database
// db.set({'^Capital':'Washington'});

