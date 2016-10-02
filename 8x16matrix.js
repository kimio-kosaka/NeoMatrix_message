/*
* LED Matrix Control
*/
var async = require('async');

/* LED Matrix Control Functions as below */
var Matrix = function (board, five) {
    this.board = board;
    this.five = five;
}

// CLEAR  "32" 0x20
Matrix.prototype.clear = function () {
  this.board.io.sendString('32');
};

// SET Brightness "36" 0x24
Matrix.prototype.setBrightness = function (brightness) {
  this.board.io.sendString('36' + ',' + brightness );
};

// SET Direction "37" 0x25
Matrix.prototype.setDirection = function(direction) {
  this.board.io.sendString('37' + ',' + direction );
}

// SET Delay  "38" 0x26
Matrix.prototype.setDelay = function(delay) {
  this.board.io.sendString('38' + ',' + delay);
}

// SET Massage "40" 0x28, "41" 0x29
Matrix.prototype.setMassage = function(buffer) {
  var board = this.board;
  if(buffer.length != 0) {
    buffer = buffer.slice(0,255);  //upper limit 140 chars
    buffer = buffer.replace(/\n/g,' ');
    var k = 24;
    async.series([
      function(next){
        console.log('--');
        console.log(buffer.slice(0,k));
        board.io.sendString('40,'+buffer.slice(0,k));
        next(null, '1');
      },
      function(next){
        for(var n = k; n < buffer.length; n = n+k){
            console.log("--");
            console.log(buffer.slice(n,n+k));
            board.io.sendString('41,' + buffer.slice(n, n + k));
        }
        next(null, '2');
      },
      function(next){
        board.io.sendString('42, ');
        next(null,'3');
      },
    ],
    function complete(err,result){
      //  console.log(JSON.stringify(result));
    }
    );
  }
};

module.exports = Matrix;
