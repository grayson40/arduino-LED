var http = require('http');
var fs = require('fs');
var index = fs.readFileSync('home.html');

var SerialPort = require("serialport");

// var port = new SerialPort("COM3", {
//     baudRate: 9600,
// });

var app = http.createServer(function (req, res) {
    res.writeHead(200, { 'Content-Type': 'text/html' });
    res.end(index);
});

// Read from html and send to arduino
const io = require('socket.io').listen(process.env.port || 5000);

io.on('connection', function (socket) {
    console.log('client connected');

    // listen for incoming data msg on this newly connected socket
    socket.on('data', function (data) {
        console.log(`data received is '${data}'`)
        // port.write(data);
    });

});

app.listen(3000);