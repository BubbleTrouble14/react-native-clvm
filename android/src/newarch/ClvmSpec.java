package com.clvm;

import com.facebook.react.bridge.ReactApplicationContext;

abstract class ClvmSpec extends NativeClvmSpec {
  ClvmSpec(ReactApplicationContext context) {
    super(context);
  }
}
