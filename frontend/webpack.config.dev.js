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
      template: "frontend/index.html"
    })
  ],
  output: {
    filename: "out.js",
    path: path.resolve(__dirname, "build"),
    publicPath: "/"
  },
  serve: {
    // this part is just for getting webpack-serve to properly serve the index.html file
    // in a real app, the index may likely be served from the actual server backend
    content: path.join(__dirname, "frontend/build"),
    add: (app, middleware, options) => {
      app.use(convert(history({})));
    }
  },
  devServer: {
    // webpack-serve might not actually use these, but I'm including them just-in-case
    contentBase: path.join(__dirname, "build"),
    publicPath: "http://localhost:8080/",
    proxy: {
      "/graphql": {
        target: "ws://localhost:9000",
        ws: true
      }
    },
    historyApiFallback: {
      index: "index.html"
    },
    hot: true,
    host: "0.0.0.0"
  },
  module: {
    rules: [
      // Set up Reason and OCaml files to use the loader
      { test: /\.(re|ml)$/, use: "bs-loader" },
      {
        test: /\.svg$/,
        loader: "svg-inline-loader?idPrefix&classPrefix"
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
              modules: true,
            }
          },
          {
            loader: "less-loader",
            options: {
              javascriptEnabled: true
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
