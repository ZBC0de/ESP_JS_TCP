let portNum                                  = 8152;
let fs                                       = require('fs');
let express                                  = require('express')
let socketIO                                   = require('socket.io');

let app                                      = express();
let io;
let server;
const net = require('net');
const os = require('os');
const portStatus = require("tcp-port-status");
let ip = "null";

// Create a TCP server
const esp32IP = '10.1.1.75'; // Replace with your ESP32's IP
const esp32Port = 3000; // Use the server port on your ESP32
const tcpServer = net.createServer((socket) => {

    console.log('Client connected');

    // Event handler for receiving data from clients
    socket.on('data', (data) => {
        data = JSON.parse(data);
        ip = data.ip
        io.emit('html', JSON.stringify({type: 'isConn', data: true}));
    });

    // Event handler for client disconnection
    socket.on('end', () => {
        console.log('Client disconnected');
    });

    socket.on('error', (err) => {
        console.log(err)
    });

    setInterval(() => {
        portStatus(ip, 3000)
            .then(status => {
                if(status === 'open') {
                    io.emit('html', JSON.stringify({type: 'isConn', data: true}));
                }
            })
            .catch(error => {
                if (error === 'timeout') {
                    io.emit('html', JSON.stringify({type: 'isConn', data: false}));
                    tcpServer.close();
                } else {
                    io.emit('html', JSON.stringify({type: 'isConn', data: true}));
                }
            });
    },2500)


});

// Set the server to listen on a specific port
const PORT = 3000; // You can change this to any port you prefer
tcpServer.listen(PORT, () => {
    console.log(`Server listening on port ${PORT}`);
});

server = app.listen(portNum, function () {

    console.log(`Starting on port ${portNum}`)

    app.use(express.static('public'))

    io = socketIO(server);

    io.on('connection', (socketIO) => {

        socketIO.on('js', function (data) {
            try{
                let msg = JSON.parse(data);

                switch (msg.type) {
                    case'':

                        break;
                    default:
                        break;
                }

            }catch (e) {
                console.log(e.message);

            }
        })

    })
})




function getServerIP() {
    const ifaces = os.networkInterfaces();

// Get server IP address
    Object.keys(ifaces).forEach((ifname) => {
        ifaces[ifname].forEach((iface) => {
            if ('IPv4' === iface.family && !iface.internal) {
                console.log(`Server IP address: ${iface.address}`);
            }
        });
    });
}






