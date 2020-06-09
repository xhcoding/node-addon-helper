const assert = require("assert");
const typeConverter = require("./binding")("apply");

describe(" apply function ", function() {
  it(" apply Add ", function() {
    assert.equal(typeConverter.apply(18, 2), 20);
    assert.equal(typeConverter.apply(-10, -20), -30);
  });

});
