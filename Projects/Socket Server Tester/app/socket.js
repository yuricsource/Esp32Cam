const path = require('path');
const defaults = module.exports.defaults = {
  port: '3333',
};

module.exports.create = function socketCreate(opt = defaults) {
  const {port} = opt;
  Object.assign(defaults, opt);

  const express = require('express');
  const app = express();
  const http = require('http').createServer(app);

  app.use((req, res, next) => {
    res.header('Access-Control-Allow-Origin', '*');
    res.header(
      'Access-Control-Allow-Methods',
      'PUT, GET, POST, DELETE, OPTIONS'
    );
    res.header(
      'Access-Control-Allow-Headers',
      'Origin, X-Requested-With, Content-Type, Accept'
    );
    next();
  });

  app.get('*', express.static(path.resolve(__dirname, '../frontend/dist')));

  addRoutes(app);
  addSocket(http);

  http.listen(port, function() {
    console.log(`Server listening on ${port}`);
  });
};

function addSocket(http) {
  const io = require('socket.io')(http);

  io.on('connection', function(socket) {
    console.log('Connected =>', socket);
    // TODO: add support for user registry
    io.emit('channel-log', {message: `connected ${new Date().toISOString()}`});

    // socket.on('chat message', function(msg) {
    //   io.emit('chat message', msg);
    // });
  });
}

function addRoutes(app) {
  app.get('/ping', function(req, res) {
    res.sendFile(path.resolve(__dirname, './socket-test.html'));
  });

  app.get('/api/ping', function(req, res) {
    res.status(200).send({message: 'pong'});
  });

  // TODO: add support for user registry
  // app.get('/', function(req, res) {
  //   res.sendFile(path.resolve(__dirname, '../frontend/dist/index.html'));
  // });
}
