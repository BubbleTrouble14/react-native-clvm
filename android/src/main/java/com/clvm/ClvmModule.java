package com.clvm;

import android.util.Log;

import androidx.annotation.NonNull;

import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.module.annotations.ReactModule;
import com.facebook.react.turbomodule.core.CallInvokerHolderImpl;
import com.facebook.react.turbomodule.core.interfaces.CallInvokerHolder;

import java.lang.ref.WeakReference;

@ReactModule(name = ClvmModule.NAME)
public class ClvmModule extends ClvmSpec {
  public static final String NAME = "Clvm";
  private final WeakReference<ReactApplicationContext> weakReactContext;

  ClvmModule(ReactApplicationContext context) {
    super(context);
    this.weakReactContext = new WeakReference<>(context);
  }

  @Override
  @NonNull
  public String getName() {
    return NAME;
  }

  static {
    System.loadLibrary("rnclvm");
  }

  public static native boolean nativeInstall(long jsiRuntimeRef, CallInvokerHolder jsCallInvokerHolder);

  @ReactMethod(isBlockingSynchronousMethod = true)
  public boolean install() {
    try {
      ReactApplicationContext context = weakReactContext.get();
      if (context == null) {
        Log.e(NAME, "React Application Context was null!");
        return false;
      }

      long jsiRuntimeRef = context.getJavaScriptContextHolder().get();
      CallInvokerHolder jsCallInvokerHolder = context.getCatalystInstance().getJSCallInvokerHolder();
      return nativeInstall(jsiRuntimeRef, jsCallInvokerHolder);
    } catch (Exception exception) {
      Log.e(NAME, "Failed to initialize react-native-clvm!", exception);
      return false;
    }
  }
}
