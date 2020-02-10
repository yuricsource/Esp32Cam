import express from "express";
import http from "http";
import io from "socket.io";

export default function socket() {
  const app = new express();
  const server = http.createServer(app);
  const socket = io(server);

  app.get("/", function(req, res) {
    console.log("#############", __dirname);
    res.sendFile(__dirname + "/socket-test.html");
  });

  socket.on("connection", function(socket) {
    console.log("a user connected");
    socket.broadcast.emit("hi");

    socket.on("chat message", function(msg) {
      io.emit("chat message", msg);
    });
  });

  server.listen(3000, function() {
    console.log("listening on *:3000");
  });
}
