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

  class JsiClvmObject : public JsiClvmWrappingHostObject<chia::CLVMObjectPtr>
  {
  public:
    JsiClvmObject(chia::CLVMObjectPtr object)
        : JsiClvmWrappingHostObject<chia::CLVMObjectPtr>(std::move(object)) {}

    // Factory method to create a JSI object from a CLVMObjectPtr
    static jsi::Value toValue(jsi::Runtime &runtime, chia::CLVMObjectPtr clvmObjPtr)
    {
      auto wrapper = std::make_shared<JsiClvmObject>(std::move(clvmObjPtr));
      return jsi::Object::createFromHostObject(runtime, wrapper);
    }

    // Method to convert a JSI value back to a CLVMObjectPtr
    static chia::CLVMObjectPtr fromValue(jsi::Runtime &runtime, const jsi::Value &value)
    {
      auto object = value.asObject(runtime);
      if (!object.isHostObject<JsiClvmObject>(runtime))
      {
        throw jsi::JSError(runtime, "Expected a host object of the correct type.");
      }
      auto hostObject = object.asHostObject<JsiClvmObject>(runtime);
      return hostObject->getObject();
    }

    // Expose the type of the underlying CLVM object
    JSI_HOST_FUNCTION(getNodeType)
    {
      auto object = this->getObject();
      return jsi::String::createFromUtf8(runtime, chia::NodeTypeToString(object->GetNodeType()));
    }

    // Expose whether the underlying CLVM object is considered "false"
    JSI_HOST_FUNCTION(isFalse)
    {
      auto object = this->getObject();
      return jsi::Value(object->IsFalse());
    }

    // Expose whether the underlying CLVM object is considered "false"
    JSI_HOST_FUNCTION(equals)
    {
      auto object = this->getObject();
      auto other = JsiClvmObject::fromValue(runtime, arguments[0]);
      return jsi::Value(object->EqualsTo(other));
    }

    JSI_EXPORT_FUNCTIONS(
        JSI_EXPORT_FUNC(JsiClvmObject, getNodeType),
        JSI_EXPORT_FUNC(JsiClvmObject, isFalse),
        JSI_EXPORT_FUNC(JsiClvmObject, equals)
    );

  protected:
    void releaseResources() override
    {
      // Clear internally allocated objects
      this->setObject(nullptr);
    }
  };
}
