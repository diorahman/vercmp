var test = require('tap').test;
var vercmp = require ('./');

test('version comparison', function (t) {
  t.equal(vercmp('0.0.1', '0.0.1'), 0, "should be 0");
  t.equal(vercmp('0.0.2', '0.0.1'), 1, "should be 1");
  t.equal(vercmp('0.0.1', '0.0.2'), -1, "should be -1");
  t.end();
});

