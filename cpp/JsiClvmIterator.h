#pragma once

#include <memory>

#include <jsi/jsi.h>

#include "JsiHostObject.h"
#include "TypedArray.h"
#include "RNClvmLog.h"

#include "assemble.h"
#include "int.h"
#include "operator_lookup.h"
#include "sexp_prog.h"
#include "types.h"
#include "clvm_utils.h"
#include "bech32.h"

#include "JsiClvmObject.h"

namespace RNClvm
{
  namespace jsi = facebook::jsi;

  class JsiClvmIterator : public RNJsi::JsiHostObject
  {
  private:
    chia::ArgsIter iter;

  public:
    explicit JsiClvmIterator(chia::CLVMObjectPtr list) : iter(list) {}

    // Mimics ArgsIter::NextInt
    JSI_HOST_FUNCTION(nextInt)
    {
      if (!iter.IsEof())
      {
        int num_bytes;
        auto val = iter.NextInt(&num_bytes);
        auto resultObj = jsi::Object(runtime);
        resultObj.setProperty(runtime, "value", jsi::Value(static_cast<double>(val.ToInt())));
        resultObj.setProperty(runtime, "numBytes", jsi::Value(static_cast<double>(num_bytes)));
        return resultObj;
      }
      else
      {
        return jsi::Value::undefined(); // End of iteration
      }
    }

    // Mimics ArgsIter::NextStr
    JSI_HOST_FUNCTION(nextStr)
    {
      if (!iter.IsEof())
      {
        auto str = iter.NextStr();
        return jsi::String::createFromUtf8(runtime, str);
      }
      else
      {
        return jsi::Value::undefined(); // End of iteration
      }
    }

    // Mimics ArgsIter::Next
    JSI_HOST_FUNCTION(nextBytes)
    {
      if (!iter.IsEof())
      {
        auto bytes = iter.Next();
        auto newTypedArray = TypedArray<TypedArrayKind::Uint8Array>(runtime, bytes.size());
        auto newBuffer = newTypedArray.getBuffer(runtime);
        std::memcpy(newBuffer.data(runtime), bytes.data(), bytes.size());
        return newTypedArray;
      }
      else
      {
        return jsi::Value::undefined(); // End of iteration
      }
    }

    // Mimics ArgsIter::IsEof
    JSI_HOST_FUNCTION(hasNext)
    {
      return jsi::Value(!iter.IsEof());
    }

    // Mimics ArgsIter::NextCLVMObj, but exposed as 'next' to JS
    JSI_HOST_FUNCTION(next)
    {
      if (!iter.IsEof())
      {
        auto obj = iter.NextCLVMObj();
        return JsiClvmObject::toValue(runtime, obj);
      }
      else
      {
        return jsi::Value::undefined(); // End of iteration
      }
    }

    JSI_EXPORT_FUNCTIONS(
        JSI_EXPORT_FUNC(JsiClvmIterator, next),
        JSI_EXPORT_FUNC(JsiClvmIterator, hasNext),
        JSI_EXPORT_FUNC(JsiClvmIterator, nextInt),
        JSI_EXPORT_FUNC(JsiClvmIterator, nextStr),
        JSI_EXPORT_FUNC(JsiClvmIterator, nextBytes));
  };

} // namespace RNClvm
