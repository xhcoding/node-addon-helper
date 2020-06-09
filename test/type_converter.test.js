const assert = require("assert");
const typeConverter = require("./binding")("type_converter");

describe(" type converter ", function() {
  it(" convert to bool ", function() {
    assert.equal(typeConverter.convertBool(true), true);
    assert.equal(typeConverter.convertBool(false), false);
  });

  it(" convert to int8_t ", function() {
    assert.equal(typeConverter.convertInt8_t(0), 0);
    assert.equal(typeConverter.convertInt8_t(-128), -128);
    assert.equal(typeConverter.convertInt8_t(-129), 127);
    assert.equal(typeConverter.convertInt8_t(127), 127);
    assert.equal(typeConverter.convertInt8_t(128), -128);
  });

  it(" convert to uint8_t ", function() {
    assert.equal(typeConverter.convertUint8_t(0), 0);
    assert.equal(typeConverter.convertUint8_t(255), 255);
    assert.equal(typeConverter.convertUint8_t(-1), 255);
    assert.equal(typeConverter.convertUint8_t(256), 0);
  });

  it(" convert to int16_t ", function() {
    assert.equal(typeConverter.convertInt16_t(0), 0);
    assert.equal(typeConverter.convertInt16_t(-32768), -32768);
    assert.equal(typeConverter.convertInt16_t(-32769), 32767);
    assert.equal(typeConverter.convertInt16_t(32767), 32767);
    assert.equal(typeConverter.convertInt16_t(32768), -32768);
  });

  it(" convert to uint16_t ", function() {
    assert.equal(typeConverter.convertUint16_t(0), 0);
    assert.equal(typeConverter.convertUint16_t(65535), 65535);
    assert.equal(typeConverter.convertUint16_t(-1), 65535);
    assert.equal(typeConverter.convertUint16_t(65536), 0);
  });

  it(" convert to int32_t ", function() {
    assert.equal(typeConverter.convertInt32_t(0), 0);
    assert.equal(typeConverter.convertInt32_t(-2147483648), -2147483648);
    assert.equal(typeConverter.convertInt32_t(-2147483649), 2147483647);
    assert.equal(typeConverter.convertInt32_t(2147483647), 2147483647);
    assert.equal(typeConverter.convertInt32_t(2147483648), -2147483648);
  });

  it(" convert to uint32_t ", function() {
    assert.equal(typeConverter.convertUint32_t(0), 0);
    assert.equal(typeConverter.convertUint32_t(4294967295), 4294967295);
    assert.equal(typeConverter.convertUint32_t(-1), 4294967295);
    assert.equal(typeConverter.convertUint32_t(4294967296), 0);
  });

  it(" convert to int64_t ", function() {
    assert.equal(typeConverter.convertInt64_t(0), 0);
    assert.equal(
      typeConverter.convertInt64_t(-9223372036854775808),
      -9223372036854775808
    );
    assert.equal(
      typeConverter.convertInt64_t(9223372036854775807),
      9223372036854775807
    );
  });

  it(" convert to float ", function() {
    assert.equal(typeConverter.convertFloat(0.0), 0.0);
    assert.equal(typeConverter.convertFloat(-1.11001), -1.110010027885437);
    assert.equal(typeConverter.convertFloat(1.00011), 1.0001100301742554);
  });

  it(" convert to double ", function() {
    assert.equal(typeConverter.convertDouble(0.0), 0.0);
    assert.equal(typeConverter.convertDouble(-1.11001), -1.110010027885437);
    assert.equal(typeConverter.convertDouble(1.00011), 1.0001100301742554);
  });

  it(" convert to std::string ", function() {
    assert.equal(typeConverter.convertString("hello, world"), "hello, world");
    assert.equal(typeConverter.convertString(""), "");
  });

  it(" convert to std::vector<int8_t> ", function() {
    const expect = [0, -128, 127, 127, -128];
    const arr = [0, -128, -129, 127, 128];
    assert.deepStrictEqual(typeConverter.convertVectorInt8_t(arr), expect);

    const v1 = Int8Array.from(arr);
    assert.deepStrictEqual(typeConverter.convertVectorInt8_t(v1), expect);
    assert.deepStrictEqual(
      typeConverter.convertVectorInt8_t(v1.buffer),
      expect
    );

    const buf = Buffer.from(arr);
    assert.deepStrictEqual(typeConverter.convertVectorInt8_t(buf), expect);
  });

  it(" convert to std::vector<uint8_t> ", function() {
    const expect = [0, 255, 255, 0];
    const arr = [0, 255, -1, 256];
    assert.deepStrictEqual(typeConverter.convertVectorUint8_t(arr), expect);

    const v1 = Uint8Array.from(arr);
    assert.deepStrictEqual(typeConverter.convertVectorUint8_t(v1), expect);
    assert.deepStrictEqual(
      typeConverter.convertVectorUint8_t(v1.buffer),
      expect
    );

    const buf = Buffer.from(arr);
    assert.deepStrictEqual(typeConverter.convertVectorUint8_t(buf), expect);
  });

  it(" convert to std::vector<int16_t> ", function() {
    const expect = [0, -32768, 32767, 32767, -32768];
    const arr = [0, -32768, -32769, 32767, 32768];
    assert.deepStrictEqual(typeConverter.convertVectorInt16_t(arr), expect);

    const v1 = Int16Array.from(arr);
    assert.deepStrictEqual(typeConverter.convertVectorInt16_t(v1), expect);
    assert.deepStrictEqual(
      typeConverter.convertVectorInt16_t(v1.buffer),
      expect
    );
    const buf = Buffer.from(v1.buffer)
    assert.deepStrictEqual(typeConverter.convertVectorInt16_t(buf), expect);
  });

  it(" convert to std::vector<uint16_t> ", function() {
    const expect = [0, 65535, 65535, 0];
    const arr = [0, 65535, -1, 65536];
    assert.deepStrictEqual(typeConverter.convertVectorUint16_t(arr), expect);

    const v1 = Uint16Array.from(arr);
    assert.deepStrictEqual(typeConverter.convertVectorUint16_t(v1), expect);
    assert.deepStrictEqual(
      typeConverter.convertVectorUint16_t(v1.buffer),
      expect
    );

    const buf = Buffer.from(v1.buffer);
    assert.deepStrictEqual(typeConverter.convertVectorUint16_t(buf), expect);
  });

  it(" convert to std::vector<int32_t> ", function() {
    const expect = [0, -2147483648, 2147483647, 2147483647, -2147483648];
    const arr = [0, -2147483648, -2147483649, 2147483647, 2147483648];
    assert.deepStrictEqual(typeConverter.convertVectorInt32_t(arr), expect);

    const v1 = Int32Array.from(arr);
    assert.deepStrictEqual(typeConverter.convertVectorInt32_t(v1), expect);
    assert.deepStrictEqual(
      typeConverter.convertVectorInt32_t(v1.buffer),
      expect
    );

    const buf = Buffer.from(v1.buffer);
    assert.deepStrictEqual(typeConverter.convertVectorInt32_t(buf), expect);
  });

  it(" convert to std::vector<uint32_t> ", function() {
    const expect = [0, 4294967295, 4294967295, 0];
    const arr = [0, 4294967295, -1, 4294967296];
    assert.deepStrictEqual(typeConverter.convertVectorUint32_t(arr), expect);

    const v1 = Uint32Array.from(arr);
    assert.deepStrictEqual(typeConverter.convertVectorUint32_t(v1), expect);
    assert.deepStrictEqual(
      typeConverter.convertVectorUint32_t(v1.buffer),
      expect
    );

    const buf = Buffer.from(v1.buffer);
    assert.deepStrictEqual(typeConverter.convertVectorUint32_t(buf), expect);
  });


  it(" convert to std::vector<float> ", function() {
    const expect = [0,  -1.110010027885437, 1.0001100301742554];
    const arr = [0, -1.11001, 1.00011];
    assert.deepStrictEqual(typeConverter.convertVectorFloat(arr), expect);

    const v1 = Float32Array.from(arr);
    assert.deepStrictEqual(typeConverter.convertVectorFloat(v1), expect);
    assert.deepStrictEqual(
      typeConverter.convertVectorFloat(v1.buffer),
      expect
    );

    const buf = Buffer.from(v1.buffer);
    assert.deepStrictEqual(typeConverter.convertVectorFloat(buf), expect);
  });


  it(" convert to std::vector<double> ", function() {
    const expect = [0,  -1.110010027885437, 1.0001100301742554];
    const arr = [0, -1.11001, 1.00011];
    assert.deepStrictEqual(typeConverter.convertVectorDouble(arr), expect);

    const v1 = Float64Array.from(arr);
    assert.deepStrictEqual(typeConverter.convertVectorDouble(v1), arr);
    assert.deepStrictEqual(
      typeConverter.convertVectorDouble(v1.buffer),
      arr
    );

    const buf = Buffer.from(v1.buffer);
    assert.deepStrictEqual(typeConverter.convertVectorDouble(buf), arr);
  });


  it(" convert to std::vector<std::string> ", function() {
    const expect = ["", "hello", "world"];
    const arr = ["", "hello", "world"];
    assert.deepStrictEqual(typeConverter.convertVectorString(arr), expect);
  });

  it(" convert to const char * ", function() {
    const expect = [0, 4294967295, 4294967295, 0];
    const arr = [0, 4294967295, -1, 4294967296];

    const v1 = Uint32Array.from(arr);
    const buf = Buffer.from(v1.buffer);

    assert.deepStrictEqual(typeConverter.convertCharPointer(v1), buf);
    assert.deepStrictEqual(
      typeConverter.convertCharPointer(v1.buffer),
      buf
    );

    assert.deepStrictEqual(typeConverter.convertCharPointer(buf), buf);
  });


});
