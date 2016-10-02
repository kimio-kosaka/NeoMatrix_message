var express = require('express');
var app = express();
var port = 5030;
var ioport = 5040;
var host = 'localhost';
// var host = '10.0.0.1';
var io = require('socket.io').listen(ioport);

var bottle_socket_id;

/*
* express server setup
*/
app.set('view engine', 'html');
app.engine('html', require('hbs').__express);

app.get('/', function (req, res) {
  res.render('controller', {addr:host, port:ioport});
 });

app.use(express.static(__dirname + '/public'));
app.listen(port);

/*
* socket.io setup
*/

io.sockets.on('connection', function(socket){

  socket.on('disconnect', function(){
    // if bottle client is disconnected, notify all controllers
    if(socket.id === bottle_socket_id) {
      socket.broadcast.emit('bottle_disconnected');
      bottle_socket_id = undefined;
    }
  })

  socket.on('controller_ready', function () {
    // check if bottle client is online
    if(bottle_socket_id) {
      // only send message to one controller (do not broadcast)
      io.sockets.connected[socket.id].emit('bottle_connected');
    }
  });

  socket.on('bottle_connect', function () {
    // register socket ID for bottle client
    bottle_socket_id = socket.id;
    socket.broadcast.emit('bottle_connected');
  });

  socket.on('msg', function(data) {
    socket.broadcast.emit('msg', data);
  });

  socket.on('echo', function(data) {
    socket.broadcast.emit('echo', data);
  });

});
