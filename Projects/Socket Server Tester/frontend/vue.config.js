const config = {
  // publicPath: process.env.NODE_ENV === "production" ? "./" : "/",
  publicPath: "./",
  devServer: {
    port: 3993,
    hot: true,
    inline: true,
    disableHostCheck: true,
    writeToDisk: true
  }
};

module.exports = config;
