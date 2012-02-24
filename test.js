var getpw = require("./build/Release/getpw");

console.log(getpw.getpwuid(process.getuid()));
