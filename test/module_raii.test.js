const assert = require("assert");
const module_raii = require("../build/bin/Debug/module_raii.node");


describe (" module raii ", function() {
  this.timeout(11000);
  it( "init and deinit ", function (done) {
    assert.equal(module_raii.getNumber(), 1);
    module_raii._module_raii = null;

    var interval = setInterval(() => {
      if (module_raii.getNumber() === 0) {
        clearInterval(interval);
        done();
      }
    });

  });
});
