var getpw = require("./build/Release/getpwuid");

console.log(getpw.getpwuid(process.getuid()));
