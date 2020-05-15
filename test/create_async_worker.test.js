const assert = require("assert");
const createAsyncWorker = require("../build/bin/Release/create_async_worker.node");


describe(" create async worker ", function() {
  it(" create add worker", function(done) {
    createAsyncWorker.addAsync(20, 30, (result) => {
      assert.equal(result, 50);
      done();
    });
  });

  it(" create concat worker", function(done) {
    createAsyncWorker.concatAsync("Hello ", "World ", (result) => {
      assert.equal(result, "Hello World ");
      done();
    });
  });


  it(" create no return worker", function(done) {
    createAsyncWorker.returnVoid("Hello", 30, (result) => {
      assert.equal(result, "returnVoid");
      done();
    });
  });




});
