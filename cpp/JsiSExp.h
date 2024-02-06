#pragma once

#include <memory>
#include <string>
#include <utility>

#include "JsiClvmHostObjects.h"
#include "JsiHostObject.h"
#include "TypedArray.h"
#include <jsi/jsi.h>
#include "RNClvmLog.h"
#include "JsiClvmIterator.h"
namespace RNClvm
{
  namespace jsi = facebook::jsi;

  class JsiSExp : public JsiClvmWrappingHostObject<chia::CLVMObjectPtr>
  {
  public:
    JsiSExp(chia::CLVMObjectPtr object)
        : JsiClvmWrappingHostObject<chia::CLVMObjectPtr>(std::move(object)) {}

    // Factory method to create a JSI object from a CLVMObjectPtr
    static jsi::Value toValue(jsi::Runtime &runtime, chia::CLVMObjectPtr clvmObjPtr)
    {
      auto wrapper = std::make_shared<JsiSExp>(std::move(clvmObjPtr));
      return jsi::Object::createFromHostObject(runtime, wrapper);
    }

    // Method to convert a JSI value back to a CLVMObjectPtr
    static chia::CLVMObjectPtr fromValue(jsi::Runtime &runtime, const jsi::Value &value)
    {
      auto object = value.asObject(runtime);
      if (!object.isHostObject<JsiSExp>(runtime))
      {
        throw jsi::JSError(runtime, "Expected a host object of the correct type.");
      }
      auto hostObject = object.asHostObject<JsiSExp>(runtime);
      return hostObject->getObject();
    }

    JSI_HOST_FUNCTION(getNodeType)
    {
      auto object = this->getObject();
      return jsi::String::createFromUtf8(runtime, chia::NodeTypeToString(object->GetNodeType()));
    }

    JSI_HOST_FUNCTION(isFalse)
    {
      auto object = this->getObject();
      return jsi::Value(object->IsFalse());
    }

    JSI_HOST_FUNCTION(equals)
    {
      auto object = this->getObject();
      auto other = JsiSExp::fromValue(runtime, arguments[0]);
      return jsi::Value(object->EqualsTo(other));
    }

    JSI_HOST_FUNCTION(isAtom)
    {
      auto object = this->getObject();
      return jsi::Value(chia::IsAtom(object));
    }

    JSI_HOST_FUNCTION(isPair)
    {
      auto object = this->getObject();
      return jsi::Value(chia::IsPair(object));
    }

    JSI_HOST_FUNCTION(isNull)
    {
      auto object = this->getObject();
      return jsi::Value(chia::IsNull(object));
    }

    JSI_HOST_FUNCTION(toBytes)
    {
      auto object = this->getObject();
      auto bytes = chia::ToBytes(object);
      auto newTypedArray = TypedArray<TypedArrayKind::Uint8Array>(runtime, bytes.size());
      auto newBuffer = newTypedArray.getBuffer(runtime);
      std::memcpy(newBuffer.data(runtime), bytes.data(), bytes.size());
      return newTypedArray;
    }

    JSI_HOST_FUNCTION(toInt)
    {
      auto object = this->getObject();
      return jsi::Value(runtime, static_cast<double>(chia::ToInt(object).ToInt()));
    }

    JSI_HOST_FUNCTION(toString)
    {
      auto object = this->getObject();
      return jsi::String::createFromUtf8(runtime, chia::ToString(object));
    }

    JSI_HOST_FUNCTION(first)
    {
      auto object = this->getObject();
      return toValue(runtime, chia::First(object));
    }

    JSI_HOST_FUNCTION(rest)
    {
      auto object = this->getObject();
      return toValue(runtime, chia::Rest(object));
    }

    JSI_HOST_FUNCTION(toPair)
    {
      auto object = this->getObject();

      auto [first, rest] = chia::Pair(object);
      auto resultObj = jsi::Object(runtime);
      resultObj.setProperty(runtime, "first", toValue(runtime, first));
      resultObj.setProperty(runtime, "rest", toValue(runtime, rest));

      return resultObj;
    }

    JSI_HOST_FUNCTION(toIter)
    {
      auto object = getObject();
      auto iterator = std::make_shared<JsiClvmIterator>(object);
      return jsi::Object::createFromHostObject(runtime, iterator);
    }

    JSI_EXPORT_FUNCTIONS(
        JSI_EXPORT_FUNC(JsiSExp, getNodeType),
        JSI_EXPORT_FUNC(JsiSExp, isFalse),
        JSI_EXPORT_FUNC(JsiSExp, equals),
        JSI_EXPORT_FUNC(JsiSExp, isAtom),
        JSI_EXPORT_FUNC(JsiSExp, isPair),
        JSI_EXPORT_FUNC(JsiSExp, isNull),
        JSI_EXPORT_FUNC(JsiSExp, toBytes),
        JSI_EXPORT_FUNC(JsiSExp, toInt),
        JSI_EXPORT_FUNC(JsiSExp, toString),
        JSI_EXPORT_FUNC(JsiSExp, first),
        JSI_EXPORT_FUNC(JsiSExp, rest),
        JSI_EXPORT_FUNC(JsiSExp, toPair),
        JSI_EXPORT_FUNC(JsiSExp, toIter));

  protected:
    void releaseResources() override
    {
      // Clear internally allocated objects
      this->setObject(nullptr);
    }
  };
}
