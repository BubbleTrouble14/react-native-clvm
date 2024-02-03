#import "Clvm.h"

#import <React/RCTBridge+Private.h>
#import <React/RCTBridge.h>
#import <React/RCTUtils.h>
#import <ReactCommon/RCTTurboModule.h>

@implementation Clvm

@synthesize bridge = _bridge;

RCT_EXPORT_MODULE()

- (void)invalidate {
  _bridge = nil;
}

- (void)setBridge:(RCTBridge *)bridge {
  _bridge = bridge;
}

+ (BOOL)requiresMainQueueSetup {
  return YES;
}

void installClvmApi(std::shared_ptr<facebook::react::CallInvoker> callInvoker,
                facebook::jsi::Runtime *runtime) {

  // Install the clvm API
  RNClvm::JsiClvmApi::installApi(*runtime);

  auto getArrayBufferForBlob = jsi::Function::createFromHostFunction(
    *runtime,
    jsi::PropNameID::forUtf8(*runtime, "getArrayBufferForBlob"),
    1, // function takes 1 argument
    [](jsi::Runtime& runtime, const jsi::Value& thisArg, const jsi::Value* args, size_t count) -> jsi::Value {
      // For demonstration, return a fixed string; in a real scenario, you'd likely convert args[0] if it's an ArrayBuffer or similar.
      return jsi::String::createFromUtf8(runtime, "Example String");
    }
  );
  runtime->global().setProperty(*runtime, "getArrayBufferForBlob", std::move(getArrayBufferForBlob));

}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(install) {
  RCTCxxBridge *cxxBridge = (RCTCxxBridge *)_bridge;
  if (cxxBridge.runtime != nullptr) {
    auto callInvoker = cxxBridge.jsCallInvoker;
    facebook::jsi::Runtime *jsRuntime =
        (facebook::jsi::Runtime *)cxxBridge.runtime;

    installClvmApi(callInvoker, jsRuntime);

    return @true;
  }
  return @false;
}

// Don't compile this code when we build for the old architecture.
#ifdef RCT_NEW_ARCH_ENABLED
- (std::shared_ptr<facebook::react::TurboModule>)getTurboModule:
    (const facebook::react::ObjCTurboModule::InitParams &)params {
  // Call installApi with c++ brigde or something similar.
  RCTCxxBridge *cxxBridge = (RCTCxxBridge *)_bridge;
  auto callInvoker = cxxBridge.jsCallInvoker;
  facebook::jsi::Runtime *jsRuntime =
      (facebook::jsi::Runtime *)cxxBridge.runtime;

  installClvmApi(callInvoker, jsRuntime);

  return std::make_shared<facebook::react::NativeClvmSpecJSI>(params);
}
#endif

@end
