const assert = require("assert");
const typeConverter = require("../build/bin/Release/fetch_info_item.node");

describe(" fetch info item ", function() {
  it(" fetch info[1] is int32_t ", function() {
    assert.equal(typeConverter.fetchInfoItem(-10, -20), -20);
    assert.equal(typeConverter.fetchInfoItem(-10, 5000), 5000);

  });

});
