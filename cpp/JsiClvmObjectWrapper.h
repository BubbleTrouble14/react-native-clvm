#pragma once

#include <memory>
#include <string>
#include <utility>

#include "JsiClvmHostObjects.h"
#include "JsiHostObject.h"
#include "TypedArray.h"
#include <jsi/jsi.h>
#include "RNClvmLog.h"

namespace RNClvm
{
  namespace jsi = facebook::jsi;

  template <typename T>
  class JsiClvmObjectWrapper : public JsiClvmWrappingHostObject<chia::CLVMObjectPtr>
  {
  public:
    JsiClvmObjectWrapper(chia::CLVMObjectPtr clvmObjPtr)
        : JsiClvmWrappingHostObject<chia::CLVMObjectPtr>(std::move(clvmObjPtr)) {}

    // Get the underlying object, statically casted to the template type
    std::shared_ptr<T> getTypedObject() const
    {
      return std::static_pointer_cast<T>(getObject());
    }

    // Expose NodeType to JS
    JSI_HOST_FUNCTION(getNodeType)
    {
      auto typedObject = getTypedObject();
      auto nodeType = typedObject->GetNodeType();
      return jsi::String::createFromUtf8(runtime, chia::NodeTypeToString(nodeType));
    }

    JSI_EXPORT_FUNCTIONS(JSI_EXPORT_FUNC(JsiClvmObjectWrapper, getNodeType));

  protected:
    void releaseResources() override
    {
      this->setObject(nullptr);
    }
  };
}
