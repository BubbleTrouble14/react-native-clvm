#pragma once

#include "JsiClvmObjectAtom.h" // Include all specific JSI object headers
#include "JsiClvmObjectPair.h" // Include all specific JSI object headers
#include "JsiClvmObject.h"
#include <jsi/jsi.h>
// ... include other specific JSI objects

namespace RNClvm
{
  namespace jsi = facebook::jsi;

  class JsiClvmObjectFactory
  {
  public:
    static jsi::Value createJsiClvmObject(jsi::Runtime &runtime, chia::CLVMObjectPtr clvmObjPtr)
    {
      if (chia::IsAtom(clvmObjPtr))
      {
        auto atomPtr = std::static_pointer_cast<chia::CLVMObject_Atom>(clvmObjPtr);
        return JsiClvmObjectAtom::toValue(runtime, atomPtr);
      }
      else if (chia::IsPair(clvmObjPtr))
      {
        auto pairPtr = std::static_pointer_cast<chia::CLVMObject_Pair>(clvmObjPtr);
        return JsiClvmObjectPair::toValue(runtime, pairPtr);
      }
      else
      {
        return JsiClvmObject<>::toValue(runtime, clvmObjPtr);
      }
    }

    static chia::CLVMObjectPtr fromJsiValue(jsi::Runtime &runtime, const jsi::Value &value)
    {
      if (!value.isObject())
      {
        throw jsi::JSError(runtime, "Expected an object.");
      }
      auto object = value.asObject(runtime);

      // Check if it's a generic CLVM object host object
      if (object.isHostObject<JsiClvmObject<>>(runtime))
      {
        auto hostObject = object.asHostObject<JsiClvmObject<>>(runtime);
        return hostObject->getObject();
      }
      else if (object.isHostObject<JsiClvmObjectAtom>(runtime))
      {
        auto hostObject = object.asHostObject<JsiClvmObjectAtom>(runtime);
        return hostObject->getObject();
      }
      else if (object.isHostObject<JsiClvmObjectPair>(runtime))
      {
        auto hostObject = object.asHostObject<JsiClvmObjectPair>(runtime);
        return hostObject->getObject();
      }
      else
      {
        throw jsi::JSError(runtime, "Object is not a recognized CLVM host object.");
      }
    }
  };

} // namespace RNClvm
