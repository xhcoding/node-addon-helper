const assert = require("assert");
const typeConverter = require("../build/bin/Release/apply.node");

describe(" apply function ", function() {
  it(" apply Add ", function() {
    assert.equal(typeConverter.apply(18, 2), 20);
    assert.equal(typeConverter.apply(-10, -20), -30);
  });

});
