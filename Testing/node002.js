// load http module
var http = require('http');
var fs = require('fs');

// create http server
var server = http.createServer( function (req, res) {

  // open and read in node001.js
  fs.readFile('node001.js', 'utf8', function(err, data) {

    res.writeHead(200, {'Content-Type': 'text/plain'});

    if (err)
      res.write('Could not find or open file for reading\n');
    else
      // if no error, write JS file to client
      res.write(data);

    res.end();
  });
});

server.listen(8124, function() { console.log('bound to port 8124');});

console.log('Server running on 8124/');
