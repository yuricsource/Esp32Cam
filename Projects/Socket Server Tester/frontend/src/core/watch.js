const { createReadStream } = window.require("fs");
const stack = (window.stack = []);
const stackMax = 50;
module.exports = file => {
  const readStream = createReadStream(file);
  // Handle any errors while reading
  readStream.on("error", () => {
    // handle error
    // console.log('###### data error', err);
    // File could not be read
    // return cb(err);
  });

  // Listen for data
  readStream.on("data", chunk => {
    // console.log('###### data', chunk.toString());
    stack.push(chunk.toString());
    if (stack.length > stackMax) {
      stack.shift();
    }
  });

  // Listen for data
  readStream.on("end", chunk => {
    // console.log("###### data end", chunk);
    // console.log('###### data end', chunk.toString());
    // chunks.push(chunk);
  });

  // File is done being read
  readStream.on("close", chunk => {
    // console.log("###### data close", chunk);
    // console.log('###### data close', chunk.toString());
    //     // Create a buffer of the image from the stream
    //     return cb(null, Buffer.concat(chunks));
  });
  // watch(file, {encoding: 'buffer'}, (eventType, filename) => {
  //   if (filename) {
  //     console.log('############################################################## ', eventType);
  //     console.log('############################################################## ', filename.toString());
  //     // Prints: <Buffer ...>
  //   }
  // });
};
