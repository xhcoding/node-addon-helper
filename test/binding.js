
const platform = require("os").platform();
const path = require("path");

function binding(name) {
  if (platform === "win32") {
    return require(path.resolve(__dirname, "../build/bin/Release", name));
  } else {
    return require(path.resolve(__dirname,  "../build/lib", name));
  }
}

module.exports = exports = binding;
