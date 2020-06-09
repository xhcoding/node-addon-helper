const assert = require("assert");
const createSyncMethod = require("./binding")("create_sync_method");

describe(" create sync worker ", function() {
  it(" add method ", function() {
    assert.equal(createSyncMethod.add(20, 30), 50);
  });

  it(" concat method ", function() {
    assert.equal(createSyncMethod.concat("Hello ", "World "), "Hello World ");
  });


  it(" return void ", function() {
    assert.equal(createSyncMethod.returnVoid("Hello", 20), null);
  });

  it(" add throw ", function() {
    try {
      assert.equal(createSyncMethod.addThrow(20), null);
    } catch (err) {
      assert.equal(err.message, "add Throw");
    }
  });



});
