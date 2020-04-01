// webpack.config.js
const path = require("path");

module.exports = {
  // Entry file can be a Reason or OCaml file
  entry: "./frontend/src/Index.re",
  mode: "development",
  output: {
    filename: "out.js",
    path: path.resolve(__dirname, "build")
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
