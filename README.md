# ESP/JS TCP Connection

# Vue.js Template with Socket.IO

This is a simple application that uses the NET library to setup a TCP connection between an ESP32 and a Node.js server. It also includes a server status feature to show possible uses of the TCP connection.

## Prerequisites

- [Vue.js](https://vuejs.org/)
- [Socket.IO](https://socket.io/)


## Getting Started

1. Clone the repository.
2. Open `index.html` in your browser.

## Usage

1. The page displays a circle with an initial red color.
2. WebSocket connection status is updated in real-time.
3. If the connection is alive, the circle turns green; otherwise, it stays red.

## Dependencies

- [Vue.js](https://vuejs.org/)
- [Socket.IO](https://socket.io/)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.


# Arduino WebSocket Client

This Arduino sketch serves as a WebSocket client that connects to a server and exchanges messages using JSON over a TCP connection.

## Prerequisites

- [Arduino](https://www.arduino.cc/)
- [WiFi Library](https://www.arduino.cc/en/Reference/WiFi)
- [ArduinoJson Library](https://arduinojson.org/)
  
## Configuration

1. Update the `ssid` and `password` with your WiFi credentials.
2. Set the `serverIP` and `serverPort` according to your server configuration.

## Usage

1. Upload the sketch to your ESP32 device.
2. Monitor the Serial Console to check the connection status.

## WebSocket Communication

The client periodically sends a "connect" message to the server and listens for incoming messages. Upon receiving a "checkCon" message, it responds with an "isAlive" message.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
