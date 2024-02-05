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

  template <typename T = chia::CLVMObject>
  class JsiClvmObject : public JsiClvmWrappingHostObject<chia::CLVMObjectPtr>
  {
  public:
    JsiClvmObject(chia::CLVMObjectPtr clvmObjPtr)
        : JsiClvmWrappingHostObject<chia::CLVMObjectPtr>(std::move(clvmObjPtr)) {}

    static jsi::Value toValue(jsi::Runtime &runtime, std::shared_ptr<T> clvmObjPtr)
    {
      auto wrapper = std::make_shared<JsiClvmObject>(clvmObjPtr);
      return jsi::Object::createFromHostObject(runtime, wrapper);
    }

    static chia::CLVMObjectPtr fromValue(jsi::Runtime &runtime, const jsi::Value &value)
    {
      auto object = value.asObject(runtime);
      if (!object.isHostObject<JsiClvmObject>(runtime))
      {
        throw jsi::JSError(runtime, "Expected a host object of the correct type.");
      }
      auto hostObject = object.asHostObject<JsiClvmObject>(runtime);
      auto clvmObjPtr = hostObject->getObject();
      if (!clvmObjPtr)
      {
        throw jsi::JSError(runtime, "Object is null.");
      }
      return clvmObjPtr;
    }

    // Get the underlying object, statically casted to the template type
    std::shared_ptr<T> getTypedObject() const
    {
      return std::static_pointer_cast<T>(getObject());
    }

    JSI_HOST_FUNCTION(getNodeType)
    {
      auto object = this->getObject();
      return jsi::String::createFromUtf8(runtime, chia::NodeTypeToString(object->GetNodeType()));
    }

    JSI_HOST_FUNCTION(isFalse)
    {
      auto typedObject = getTypedObject();
      return jsi::Value(typedObject->IsFalse());
    }

    JSI_HOST_FUNCTION(equals)
    {
      auto typedObject = getTypedObject();
      return jsi::Value(typedObject->Eq());
    }

    JSI_EXPORT_FUNCTIONS(JSI_EXPORT_FUNC(JsiClvmObject, getNodeType), JSI_EXPORT_FUNC(JsiClvmObject, isFalse), JSI_EXPORT_FUNC(JsiClvmObject, equals));

  protected:
    void releaseResources() override
    {
      this->setObject(nullptr);
    }
  };
}
