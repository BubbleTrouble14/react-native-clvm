#pragma once

#include "JsiClvmObjectAtom.h" // Include all specific JSI object headers
#include "JsiClvmObject.h"
// ... include other specific JSI objects

namespace RNClvm
{
  namespace jsi = facebook::jsi;

  class JsiClvmObjectFactory
  {
  public:
    static jsi::Value createJsiClvmObject(jsi::Runtime &runtime, chia::CLVMObjectPtr clvmObj)
    {
      switch (clvmObj->GetNodeType())
      {
      case chia::NodeType::Atom_Bytes:
      case chia::NodeType::Atom_Str:
      case chia::NodeType::Atom_Int:
      case chia::NodeType::Atom_G1Element:
        return JsiClvmObjectAtom::toValue(runtime, clvmObj);
      default:
        return JsiClvmObject::toValue(runtime, clvmObj);
      }
    }
  };

} // namespace RNClvm
