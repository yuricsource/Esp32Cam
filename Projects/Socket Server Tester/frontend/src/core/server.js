const express = window.require("express");
const { resolve } = window.require("path");
let _port = process.argv[2] || 3000;
let _folder = process.argv[3] || "./";

const run = ({ port, folder, onStart }) => {
  const app = express();
  const io = window.require('socket.io')(app);

  io.on('connection', function(socket){
    console.log('a user connected', socket);
  });

  _port = port || _port;
  _folder = folder || _folder;

  // console.log('webserver ', _folder, _port);

  app.use((req, res, next) => {
    // console.log('webserver ', req);
    res.header("Access-Control-Allow-Origin", "*");
    res.header(
      "Access-Control-Allow-Methods",
      "PUT, GET, POST, DELETE, OPTIONS"
    );
    res.header(
      "Access-Control-Allow-Headers",
      "Origin, X-Requested-With, Content-Type, Accept"
    );
    next();
  });

  // app.get('/', express.static(resolve(_folder, 'public')));
  // console.log('webserver ', resolve(_folder));
  app.get("*", express.static(resolve(_folder)));
  // app.get('/static', express.static(resolve(_folder, 'static')));

  // process.on('uncaughtException', (err)=>
  //   console.error('uncaughtException ', err)
  // );

  // process.on('unhandledRejection', (reason)=>
  //   console.error('unhandledRejection ', reason)
  // );

  const server = app.listen(_port, () => {
    // console.log(`app listening on port ${_port}!`);
    // TODO: change this solution
    if (onStart) {
      onStart();
    }
  });
  app.server = server;
  app.close = cb => {
    server.close(cb);
    // return new Promise((resolve)=> {
    //   server.close(()=> resolve());
    // });
  };

  return app;
};

module.exports = run;
