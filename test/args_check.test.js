const assert = require("assert");
const argsCheck = require("../build/bin/Release/args_check.node");

describe(" check args length ", function() {
  it(" expect 4, actual 0", function() {
    try {
      argsCheck.checkInfoLength();
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Wrong number of arguments! expect: 4, actual: 0"
      );
    }
  });

  it(" expect 4, actual 5", function() {
    try {
      argsCheck.checkInfoLength(1, 2, 3, 4, 5);
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Wrong number of arguments! expect: 4, actual: 5"
      );
    }
  });

  it(" expect 4, actual 4", function() {
    assert.equal(argsCheck.checkInfoLength(1, 2, 3, 4), null);
  });
});

describe(" check args is Boolean ", function() {
  it(" expect Boolean, actual Undefined", function() {
    try {
      argsCheck.checkInfoTypeBoolean(undefined);
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: Boolean, actual: Undefined"
      );
    }
  });

  it(" expect Boolean, actual Null", function() {
    try {
      argsCheck.checkInfoTypeBoolean(null);
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: Boolean, actual: Null"
      );
    }
  });

    it(" expect Boolean, actual Number", function() {
    try {
      argsCheck.checkInfoTypeBoolean(1);
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: Boolean, actual: Number"
      );
    }
    });

  it(" expect Boolean, actual String", function() {
    try {
      argsCheck.checkInfoTypeBoolean("");
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: Boolean, actual: String"
      );
    }
  });

  it(" expect Boolean, actual Array", function() {
    try {
      argsCheck.checkInfoTypeBoolean([]);
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: Boolean, actual: Array"
      );
    }
  });

  it(" expect Boolean, actual ArrayBuffer", function() {
    try {
      argsCheck.checkInfoTypeBoolean(new ArrayBuffer(8));
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: Boolean, actual: ArrayBuffer"
      );
    }
  });

  it(" expect Boolean, actual TypedArray", function() {
    try {
      argsCheck.checkInfoTypeBoolean(new Int8Array(8));
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: Boolean, actual: TypedArray"
      );
    }
  });

  it(" expect Boolean, actual Object", function() {
    try {
      argsCheck.checkInfoTypeBoolean({});
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: Boolean, actual: Object"
      );
    }
  });

  it(" expect Boolean, actual Function", function() {
    try {
      argsCheck.checkInfoTypeBoolean(()=>{});
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: Boolean, actual: Function"
      );
    }
  });

  it(" expect Boolean, actual Boolean", function() {
    assert.equal(argsCheck.checkInfoTypeBoolean(true), null);
  });



});

describe(" check args is Number ", function() {
  it(" expect Number, actual Undefined", function() {
    try {
      argsCheck.checkInfoTypeNumber(undefined);
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: Number, actual: Undefined"
      );
    }
  });

  it(" expect Number, actual Null", function() {
    try {
      argsCheck.checkInfoTypeNumber(null);
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: Number, actual: Null"
      );
    }
  });

    it(" expect Number, actual Boolean", function() {
    try {
      argsCheck.checkInfoTypeNumber(true);
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: Number, actual: Boolean"
      );
    }
    });

  it(" expect Number, actual String", function() {
    try {
      argsCheck.checkInfoTypeNumber("");
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: Number, actual: String"
      );
    }
  });

  it(" expect Number, actual Array", function() {
    try {
      argsCheck.checkInfoTypeNumber([]);
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: Number, actual: Array"
      );
    }
  });

  it(" expect Number, actual ArrayBuffer", function() {
    try {
      argsCheck.checkInfoTypeNumber(new ArrayBuffer(8));
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: Number, actual: ArrayBuffer"
      );
    }
  });

  it(" expect Number, actual TypedArray", function() {
    try {
      argsCheck.checkInfoTypeNumber(new Int8Array(8));
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: Number, actual: TypedArray"
      );
    }
  });

  it(" expect Number, actual Object", function() {
    try {
      argsCheck.checkInfoTypeNumber({});
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: Number, actual: Object"
      );
    }
  });

  it(" expect Number, actual Function", function() {
    try {
      argsCheck.checkInfoTypeNumber(()=>{});
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: Number, actual: Function"
      );
    }
  });

  it(" expect Number, actual Number", function() {
    assert.equal(argsCheck.checkInfoTypeNumber(10), null);
  });


});


describe(" check args is String ", function() {
  it(" expect String, actual Undefined", function() {
    try {
      argsCheck.checkInfoTypeString(undefined);
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: String, actual: Undefined"
      );
    }
  });

  it(" expect String, actual Null", function() {
    try {
      argsCheck.checkInfoTypeString(null);
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: String, actual: Null"
      );
    }
  });

    it(" expect String, actual Boolean", function() {
    try {
      argsCheck.checkInfoTypeString(true);
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: String, actual: Boolean"
      );
    }
    });

  it(" expect String, actual Number", function() {
    try {
      argsCheck.checkInfoTypeString(10);
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: String, actual: Number"
      );
    }
  });

  it(" expect String, actual Array", function() {
    try {
      argsCheck.checkInfoTypeString([]);
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: String, actual: Array"
      );
    }
  });

  it(" expect String, actual ArrayBuffer", function() {
    try {
      argsCheck.checkInfoTypeString(new ArrayBuffer(8));
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: String, actual: ArrayBuffer"
      );
    }
  });

  it(" expect String, actual TypedArray", function() {
    try {
      argsCheck.checkInfoTypeString(new Int8Array(8));
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: String, actual: TypedArray"
      );
    }
  });

  it(" expect String, actual Object", function() {
    try {
      argsCheck.checkInfoTypeString({});
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: String, actual: Object"
      );
    }
  });

  it(" expect String, actual Function", function() {
    try {
      argsCheck.checkInfoTypeString(()=>{});
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: String, actual: Function"
      );
    }
  });

  it(" expect String, actual String", function() {
    assert.equal(argsCheck.checkInfoTypeString("Hello"), null);
  });


});


describe(" check args will to std::vector<uint8_t> ", function() {
  it(" expect Array|ArrayBuffer|Buffer|TypedArray, actual Undefined", function() {
    try {
      argsCheck.checkInfoTypeVectorUint8_t(undefined);
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: Array|ArrayBuffer|Buffer|TypedArray, actual: Undefined"
      );
    }
  });

  it(" expect ArrayBuffer|Buffer|TypedArray, actual Array", function() {
    assert.equal(argsCheck.checkInfoTypeVectorUint8_t([1, 2, 3]), null);
  });


  it(" expect ArrayBuffer|Buffer|TypedArray, actual ArrayBuffer", function() {
    assert.equal(argsCheck.checkInfoTypeVectorUint8_t(new ArrayBuffer(8)), null);
  });


  it(" expect ArrayBuffer|Buffer|TypedArray, actual TypedArray", function() {
    assert.equal(argsCheck.checkInfoTypeVectorUint8_t(new Int8Array(8)), null);
  });


  it(" expect ArrayBuffer|Buffer|TypedArray, actual Buffer", function() {
    assert.equal(argsCheck.checkInfoTypeVectorUint8_t(Buffer.alloc(10)), null);
  });


});


describe(" check args will to std::vector<std::string> ", function() {
  it(" expect Array, actual Undefined", function() {
    try {
      argsCheck.checkInfoTypeVectorString(undefined);
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: Array, actual: Undefined"
      );
    }
  });

  it(" expect Array, actual ArrayBuffer", function() {
    try {
      argsCheck.checkInfoTypeVectorString(new ArrayBuffer(8));
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: Array, actual: ArrayBuffer"
      );
    }
  });


  it(" expect Array, actual TypedArray", function() {
    try {
      argsCheck.checkInfoTypeVectorString(new Int8Array(8));
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: Array, actual: TypedArray"
      );
    }
  });


  it(" expect Array, actual Buffer", function() {
    try {
      argsCheck.checkInfoTypeVectorString(Buffer.alloc(8));
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: Array, actual: TypedArray"
      );
    }
  });


});

describe(" check args will to std::pair<const char*, size_t> ", function() {
  it(" expect ArrayBuffer|Buffer|TypedArray, actual Undefined", function() {
    try {
      argsCheck.checkInfoTypeCharPointer(undefined);
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: ArrayBuffer|Buffer|TypedArray, actual: Undefined"
      );
    }
  });

  it(" expect ArrayBuffer|Buffer|TypedArray, actual ArrayBuffer", function() {
    assert.equal(argsCheck.checkInfoTypeCharPointer(new ArrayBuffer(8)), null);
  });


  it(" expect ArrayBuffer|Buffer|TypedArray, actual TypedArray", function() {
    assert.equal(argsCheck.checkInfoTypeCharPointer(new Int8Array(8)), null);
  });


  it(" expect ArrayBuffer|Buffer|TypedArray, actual Buffer", function() {
    assert.equal(argsCheck.checkInfoTypeCharPointer(Buffer.alloc(10)), null);
  });
});

describe(" check args will to function ", function() {
  it(" expect Function, actual Undefined", function() {
    try {
      argsCheck.checkInfoTypeFunction(undefined);
    } catch (err) {
      assert.ok(err instanceof TypeError);
      assert.equal(
        err.message,
        "Type of arg 0 is not matched! expect: Function, actual: Undefined"
      );
    }
  });

  it(" expect Function, actual Function", function() {
    assert.equal(argsCheck.checkInfoTypeFunction(() => {}), null);
  });

});
