#pragma once

#include "JsiClvmObject.h" // Ensure this path is correct

namespace RNClvm
{
  namespace jsi = facebook::jsi;

  class JsiClvmObjectAtom : public JsiClvmObject<chia::CLVMObject_Atom>
  {
  public:
    using JsiClvmObject::JsiClvmObject; // Inherit constructors

    JSI_HOST_FUNCTION(asString)
    {
      // Here you can directly use getTypedObject() from the base class
      auto atomObj = getTypedObject(); // This is already the correct type
      return jsi::String::createFromUtf8(runtime, atomObj->AsString());
    }

    JSI_HOST_FUNCTION(asInt)
    {
      // Here you can directly use getTypedObject() from the base class
      auto atomObj = getTypedObject(); // This is already the correct type
      return jsi::Value(runtime, static_cast<double>(atomObj->AsInt().ToInt()));
    }

    // static jsi::Value toValue(jsi::Runtime &runtime, chia::CLVMObject_Atom clvmObjPtr)
    // {
    //   auto wrapper = std::make_shared<JsiClvmObjectAtom>(std::move(clvmObjPtr));
    //   return jsi::Object::createFromHostObject(runtime, wrapper);
    // }
    static jsi::Value toValue(jsi::Runtime &runtime, std::shared_ptr<chia::CLVMObject_Atom> clvmObjPtr)
    {
      auto wrapper = std::make_shared<JsiClvmObjectAtom>(std::move(clvmObjPtr));
      return jsi::Object::createFromHostObject(runtime, wrapper);
    }

    JSI_EXPORT_FUNCTIONS(JSI_EXPORT_FUNC(JsiClvmObjectAtom, asString));
  };

} // namespace RNClvm
