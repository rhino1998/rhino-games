// webpack.config.js
const path = require("path");
const TerserJSPlugin = require("terser-webpack-plugin");
const BundleAnalyzerPlugin = require("webpack-bundle-analyzer")
  .BundleAnalyzerPlugin;
const ClosureCompilerPlugin = require("webpack-closure-compiler");
const HtmlWebpackPlugin = require("html-webpack-plugin");
const MiniCssExtractPlugin = require("mini-css-extract-plugin");
const OptimizeCSSAssetsPlugin = require("optimize-css-assets-webpack-plugin");
const PurifyCSSPlugin = require("purifycss-webpack");

const glob = require("glob");

module.exports = {
  // Entry file can be a Reason or OCaml file
  entry: "./frontend/src/Index.re",
  mode: "production",
  plugins: [
    new ClosureCompilerPlugin({
      compiler: {
        language_in: "ECMASCRIPT6",
        language_out: "ECMASCRIPT6",
        compilation_level: "ADVANCED",
        assume_function_wrapper: true,
        use_types_for_optimization: true
      },
      concurrency: 3
    }),
    new HtmlWebpackPlugin({
      template: "frontend/index.html",
      scriptLoading: "defer"
    }),
    new MiniCssExtractPlugin({
      filename: "[name].css",
      chunkFilename: "[id].css"
    }),
    new PurifyCSSPlugin({
      paths: glob.sync(`**/*.js`, {
        nodir: true
      })
    }),
    new BundleAnalyzerPlugin({ analyzerPort: 5000 })
  ],
  output: {
    path: path.join(__dirname, "build"),
    filename: "[name]-[chunkhash].bundle.js",
    chunkFilename: "[name]-[chunkhash].bundle.js",
    publicPath: "/"
  },
  optimization: {
    minimizer: [new TerserJSPlugin({}), new OptimizeCSSAssetsPlugin({})],
    usedExports: true,
    runtimeChunk: "single",
    splitChunks: {
      chunks: "all"
    }
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
            loader: MiniCssExtractPlugin.loader,
            options: {
              esModule: true
            }
          },
          {
            loader: "css-loader",
            options: {}
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
