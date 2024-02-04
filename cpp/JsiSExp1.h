#pragma once

#include <memory>
#include <string>
#include <utility>

#include "JsiClvmHostObjects.h"
#include "JsiHostObject.h"
#include "TypedArray.h"
#include <jsi/jsi.h>
#include "RNClvmLog.h"

#include "JsiSExp.h"

#include "sexp_prog.h"
#include "types.h"

namespace RNClvm
{
  namespace jsi = facebook::jsi;

  class JsiSExp1 : public JsiClvmWrappingHostObject<chia::CLVMObjectPtr>
  {
  public:
    JsiSExp1(chia::CLVMObjectPtr clvmObjPtr)
        : JsiClvmWrappingHostObject<chia::CLVMObjectPtr>(std::move(clvmObjPtr)) {}

    JSI_HOST_FUNCTION(getNodeType)
    {
      return jsi::String::createFromUtf8(runtime, chia::NodeTypeToString(getObject()->GetNodeType()));
    }

    static jsi::Value toValue(jsi::Runtime &runtime, chia::CLVMObjectPtr clvmObjPtr)
    {
      auto wrapper = std::make_shared<JsiSExp1>(std::move(clvmObjPtr));
      return jsi::Object::createFromHostObject(runtime, wrapper);
    }

    JSI_HOST_FUNCTION(getFirst)
    {
      auto obj = getObject();
      if (chia::IsPair(obj))
      {
        auto first = chia::First(obj);
        return toValue(runtime, first);
      }
      throw jsi::JSError(runtime, "Object is not a pair");
    }

    JSI_EXPORT_FUNCTIONS(JSI_EXPORT_FUNC(JsiSExp1, getNodeType))

  protected:
    void releaseResources() override
    {
      // Clear internally allocated objects
      this->setObject(nullptr);
    }
  };

} // namespace RNClvm
