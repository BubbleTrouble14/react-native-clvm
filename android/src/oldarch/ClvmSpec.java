package com.clvm;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.Promise;

abstract class ClvmSpec extends ReactContextBaseJavaModule {
  ClvmSpec(ReactApplicationContext context) {
    super(context);
  }

  public abstract boolean install();
}
