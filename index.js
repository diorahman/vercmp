var o = require ('./build/Release/vercmp');

module.exports = function (a, b) {
  return o.vercmp (a, b);
}
