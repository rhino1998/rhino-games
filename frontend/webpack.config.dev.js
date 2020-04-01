// webpack.config.js
const path = require("path");
var HtmlWebpackPlugin = require("html-webpack-plugin");
const history = require("connect-history-api-fallback");
const convert = require("koa-connect");

module.exports = {
  // Entry file can be a Reason or OCaml file
  entry: "./frontend/src/Index.re",
  mode: "development",
  plugins: [
    new HtmlWebpackPlugin({
      template: "index.html",
      inject: "body"
    })
  ],
  serve: {
    // this part is just for getting webpack-serve to properly serve the index.html file
    // in a real app, the index may likely be served from the actual server backend
    content: path.join(__dirname, "dist"),
    add: (app, middleware, options) => {
      app.use(convert(history({})));
    }
  },
  devServer: {
    // webpack-serve might not actually use these, but I'm including them just-in-case
    contentBase: path.join(__dirname, "dist"),
    publicPath: "http://localhost:8080/",
    hot: true,
    host: "0.0.0.0",
    errorOverlay: true
  },
  module: {
    rules: [
      // Set up Reason and OCaml files to use the loader
      { test: /\.(re|ml)$/, use: "bs-loader" }
    ]
  },
  resolve: {
    // Add .re and .ml to the list of extensions webpack recognizes
    extensions: [".re", ".ml", ".js"]
  }
};
