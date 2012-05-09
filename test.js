var getpw = require("./build/Release/getpw"), assert = require("assert");

var pw = getpw.getpwuid(process.getuid());
["pw_name", "pw_uid"].forEach(function (k) {
  assert.ok(k in pw, 'expected key "' + k + '" not found in result');
});
console.log("getpwuid: %s", JSON.stringify(getpw.getpwuid(process.getuid()), null, "  "));

