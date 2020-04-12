// webpack.config.js
const path = require("path");
const HtmlWebpackPlugin = require("html-webpack-plugin");

module.exports = {
  // Entry file can be a Reason or OCaml file
  entry: "./frontend/src/Index.re",
  mode: "development",
  output: {
    filename: "out.js",
    path: path.resolve(__dirname, "build"),
    publicPath: "/"
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: "frontend/index.html"
    })
  ],
  module: {
    rules: [
      // Set up Reason and OCaml files to use the loader
      { test: /\.(re|ml)$/, use: "bs-loader" },
      {
        test: /\.svg$/,
        loader: "svg-inline-loader"
      },
      {
        test: /\.less$/,
        use: [
          {
            loader: "style-loader"
          },
          {
            loader: "css-loader",
            options: {
              sourceMap: true,
              modules: true
            }
          },
          {
            loader: "less-loader",
            options: {
              javascriptEnabled: true
            }
          },
          {
            loader: "postcss-loader",
            options: {
              syntax: "postcss-less",
              plugins: [require("postcss-reason-modules")]
            }
          }
        ]
      }
    ]
  },
  resolve: {
    // Add .re and .ml to the list of extensions webpack recognizes
    extensions: [".re", ".ml", ".js", ".svg"],
    alias: {
      react: "preact/compat",
      "react-dom": "preact/compat"
    }
  }
};
