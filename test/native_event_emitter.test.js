const assert = require("assert");
const nativeEventEmitter = require("../build/bin/Release/native_event_emitter.node");

const events = require("events");
const emitter = new events.EventEmitter();

notify = new nativeEventEmitter.NativeEventTransponder(
  emitter.emit.bind(emitter)
);

var receive_events = {};

describe(" native event emitter ", function() {
  before(function() {
    emitter.on("send_int32_t", event => {
      receive_events["send_int32_t"] = event;
    });

    emitter.on("send_double", event => {
      receive_events["send_double"] = event;
    });

    emitter.on("send_string", event => {
      receive_events["send_string"] = event;
    });

    emitter.on("send_vector_string", event => {
      receive_events["send_vector_string"] = event;
    });

    nativeEventEmitter.start();
  });

  it(" emitter inte32_t ", function() {
    assert.equal(receive_events["send_int32_t"], 100);
  });

  it(" emitter double ", function() {
    assert.equal(receive_events["send_double"], 100.1);
  });

  it(" emitter string ", function() {
    assert.equal(receive_events["send_string"], "Hello JS");
  });

  it(" emitter vector string ", function() {
    assert.deepStrictEqual(receive_events["send_vector_string"], [
      "Hello",
      "World"
    ]);
  });

  after(function() {
    notify.release();
  });
});
