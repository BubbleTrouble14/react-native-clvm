#include "JsiClvmApi.h"

#include <jsi/jsi.h>

#include <memory>
#include <string>
#include <vector>

#include "RuntimeAwareCache.h"

namespace RNClvm
{

  namespace jsi = facebook::jsi;

  void JsiClvmApi::installApi(jsi::Runtime &runtime)
  {
    RNJsi::BaseRuntimeAwareCache::setMainJsRuntime(&runtime);

    auto clvmApi = std::make_shared<JsiClvmApi>(runtime);
    runtime.global().setProperty(runtime, "ClvmApi", jsi::Object::createFromHostObject(runtime, std::move(clvmApi)));

    // Not sure if i need to use both as I now use the BaseRuntimeAwareCache
    auto propNameIdCache = std::make_shared<InvalidateCacheOnDestroy>(runtime);
    runtime.global().setProperty(runtime, "clvmPropNameIdCache", jsi::Object::createFromHostObject(runtime, propNameIdCache));
  }

} // namespace RNClvm
