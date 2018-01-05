var getpw = require("./build/Release/getpw"), assert = require("assert");

var pw = getpw.getpwuid(process.getuid());
["pw_name", "pw_uid"].forEach(function (k) {
  assert.ok(k in pw, 'expected key "' + k + '" not found in result');
});
console.log("getpwuid: %s", JSON.stringify(getpw.getpwuid(process.getuid()), null, "  "));

var gr = getpw.getgrgid(process.getgid());
["gr_name", "gr_gid"].forEach(function (k) {
  assert.ok(k in gr, 'expected key "' + k + '" not found in result');
});
console.log("getgrgid: %s", JSON.stringify(getpw.getgrgid(process.getgid()), null, "  "));

