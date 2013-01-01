var http = require('http')
var gtm = require('./gtm');

var db = new gtm.Database();

db.set('^VisitorCounter',"0");

var server = http.createServer(function (req, res) {

  res.writeHead(200,{'content-type': 'text/plain'});


  var globalValue = db.get('^VisitorCounter');

  var visitorCounter = Number(globalValue) + 1;

  console.log('Visitor Counter',visitorCounter);

  db.execute('set ^VisitorCounter=^VisitorCounter+1');

  res.end("Hello Visitor # "+String(visitorCounter)+"\n");

});

server.listen(8124);

console.log('Server running on 8124');

