// load gtm module
var gtm = require('gtm');

// create gtm database connection
var db = new gtm.Database();

// interact with the database
db.set({'^Capital':'Washington'});

