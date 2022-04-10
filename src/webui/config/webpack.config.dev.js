"use strict";

const webpack = require("webpack");
const { merge } = require("webpack-merge");
const baseConfig = require("./webpack.config.base");

const HOST = "localhost";
const PORT = 9000;

module.exports = merge(baseConfig, {
    mode: "development",
    devtool: "eval-cheap-module-source-map",

    devServer: {
        hot: true,
        compress: true,
        host: HOST,
        port: PORT,
        open: true,
        headers: {
            "Access-Control-Allow-Origin": "*",
            "Access-Control-Allow-Methods": "GET, POST, PUT, DELETE, PATCH, OPTIONS",
            "Access-Control-Allow-Headers":
                "X-Requested-With, content-type, Authorization",
        },
    },

    module: {
        rules: [
            {
                test: /\.css$/,
                use: ["vue-style-loader", "css-loader"],
            },
            {
                test: /\.styl(us)?$/,
                use: ["vue-style-loader", "css-loader", "stylus-loader"],
            },
        ],
    },

    plugins: [new webpack.HotModuleReplacementPlugin()],
});