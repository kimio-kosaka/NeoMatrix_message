var five = require('johnny-five');

var host = '10.0.0.1';
var port = '5040';
var socket = require('socket.io-client')('http://'+host+':'+port);

var board = new five.Board();
var leftBtn, rightBtn;

board.on('ready', function() {
  leftBtn = new five.Button(2);
  rightBtn = new five.Button(3);
  leftBtn.on('up', function() {
    socket.emit('msg', {
      type: 'direction',
      data: 1
    });
  });
  rightBtn.on('up', function() {
    socket.emit('msg', {
      type: 'direction',
      data: 3
    });
  });
});