// load gtm module
var gtm = require('./gtm');

// create gtm database connection
var db = new gtm.Database();

// modify the database
db.set('^Capital','Paris');

// query the database
var capital = db.get('^Capital');
console.log( capital );

// interact with the database
// db.set({'^Capital':'Washington'});

