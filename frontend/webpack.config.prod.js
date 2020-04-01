// webpack.config.js
const path = require("path");
const BundleAnalyzerPlugin = require("webpack-bundle-analyzer")
  .BundleAnalyzerPlugin;
const ClosureCompilerPlugin = require("webpack-closure-compiler");

module.exports = {
  // Entry file can be a Reason or OCaml file
    entry: "./frontend/src/Index.re",
  mode: "production",
  plugins: [
    // new ClosureCompilerPlugin({
    //   compiler: {
    //     language_in: "ECMASCRIPT6",
    //     language_out: "ECMASCRIPT6",
    //     compilation_level: "ADVANCED"
    //   },
    //   concurrency: 3
    // })
  ],
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
