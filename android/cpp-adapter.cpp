#include <jni.h>

#include <ReactCommon/CallInvokerHolder.h>
#include <jsi/jsi.h>

#include "JsiClvmApi.h"

using namespace facebook; // NOLINT

extern "C" JNIEXPORT jboolean JNICALL Java_com_clvm_ClvmModule_nativeInstall(
    JNIEnv *env, jclass obj, jlong jsiRuntimeRef, jobject jsCallInvokerHolder)
{
  auto jsiRuntime{reinterpret_cast<jsi::Runtime *>(jsiRuntimeRef)};
  auto jsCallInvoker{jni::alias_ref<react::CallInvokerHolder::javaobject>{
      reinterpret_cast<react::CallInvokerHolder::javaobject>(
          jsCallInvokerHolder)} -> cthis()
                         ->getCallInvoker()};

  RNClvm::JsiClvmApi::installApi(*jsiRuntime);

  return true;
}
