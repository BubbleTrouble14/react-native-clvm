#pragma once

#include "JsiClvmObject.h" // Ensure this path is correct
#include "JsiClvmObjectFactory.h"

namespace RNClvm
{
  namespace jsi = facebook::jsi;

  class JsiClvmObjectPair : public JsiClvmObject<chia::CLVMObject_Pair>
  {
  public:
    using JsiClvmObject::JsiClvmObject; // Inherit constructors

    // Method to get the first element of the pair
    JSI_HOST_FUNCTION(getFirstNode)
    {
      auto pairObj = getTypedObject(); // This is already of type CLVMObject_Pair
      auto first = pairObj->GetFirstNode();
      return JsiClvmObjectFactory::createJsiClvmObject(runtime, first);
    }

    // Method to get the rest element of the pair
    JSI_HOST_FUNCTION(getRestNode)
    {
      auto pairObj = getTypedObject(); // This is already of type CLVMObject_Pair
      auto rest = pairObj->GetRestNode();
      return JsiClvmObjectFactory::createJsiClvmObject(runtime, rest);
    }

    // Method to get the rest element of the pair
    JSI_HOST_FUNCTION(setRestNode)
    {
      auto pairObj = getTypedObject();
      auto clvmObjPtr = JsiClvmObject::fromValue(runtime, arguments[0]);
      pairObj->SetRestNode(clvmObjPtr);

      return jsi::Value::undefined();
    }

    static jsi::Value toValue(jsi::Runtime &runtime, std::shared_ptr<chia::CLVMObject_Pair> clvmObjPtr)
    {
      auto wrapper = std::make_shared<JsiClvmObjectPair>(std::move(clvmObjPtr));
      return jsi::Object::createFromHostObject(runtime, wrapper);
    }

    JSI_EXPORT_FUNCTIONS(
        // JSI_EXPORT_FUNC(JsiClvmObjectPair, getFirstNode),
        // JSI_EXPORT_FUNC(JsiClvmObjectPair, getRestNode),
        JSI_EXPORT_FUNC(JsiClvmObjectPair, setRestNode), JSI_EXPORT_FUNC(JsiClvmObjectPair, getNodeType));
  };

} // namespace RNClvm
