// load gtm module
var gtm = require('./gtm');

// create gtm database connection
var db = new gtm.Database();

// load readline module
var readline = require('readline');

// create a new interface
var interface = readline.createInterface(process.stdin, process.stdout, null);

// welcome the visitor
interface.question(" Welcome to the GT.M prompt via Node.js ", function(answer) {
  interface.setPrompt("> ");
  interface.prompt();
});

// function to close interface
function closeInterface() {
  console.log('Leaving interface...');
  process.exit();
}

// listen for HALT
interface.on('line', function(cmd) {
  if (cmd.trim() == 'HALT') {
    closeInterface();
    return;
  } else {
    db.execute(cmd);
  }
  interface.setPrompt("> ");
  interface.prompt();
});

interface.on('close', function() {
   closeInterface();
});

