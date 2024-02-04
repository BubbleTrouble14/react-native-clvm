// JsiClvmObjectAtom.h
#pragma once

#include "JsiClvmObjectWrapper.h" // Ensure this path is correct

namespace RNClvm
{
  namespace jsi = facebook::jsi;

  class JsiClvmObject : public JsiClvmObjectWrapper<chia::CLVMObject>
  {
  public:
    // You're inheriting a constructor, but the base is a template, so you should directly call its constructor
    JsiClvmObject(chia::CLVMObjectPtr clvmObjPtr)
        : JsiClvmObjectWrapper<chia::CLVMObject>(std::move(clvmObjPtr)) {}

    static jsi::Value toValue(jsi::Runtime &runtime, chia::CLVMObjectPtr clvmObjPtr)
    {
      auto wrapper = std::make_shared<JsiClvmObject>(std::move(clvmObjPtr));
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
  };

} // namespace RNClvm
