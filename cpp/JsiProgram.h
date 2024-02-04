#pragma once

#include <memory>
#include <string>
#include <utility>

#include "JsiClvmHostObjects.h"
#include "JsiHostObject.h"
#include "TypedArray.h"
#include <jsi/jsi.h>
#include "RNClvmLog.h"

#include "JsiSExp.h"
#include "JsiSExp1.h"

#include "sexp_prog.h"
#include "types.h"

namespace RNClvm
{

  namespace jsi = facebook::jsi;

  class JsiProgram : public JsiClvmWrappingSharedPtrHostObject<chia::Program, JsiProgram>
  {
  public:
    // For static methods we set a nullptr
    JsiProgram() : JsiClvmWrappingSharedPtrHostObject<chia::Program, JsiProgram>(nullptr) {}

    JsiProgram(std::shared_ptr<chia::Program> program)
        : JsiClvmWrappingSharedPtrHostObject<chia::Program, JsiProgram>(std::move(program)) {}

    // ----------fromBytes----------//
    JSI_HOST_FUNCTION(fromBytes)
    {
      auto object = arguments[0].asObject(runtime);
      if (!isTypedArray(runtime, object))
      {
        throw jsi::JSError(runtime, "The 'fromBytes' argument must be an object, but it is not of type Uint8Array.");
      }

      auto typedArray = getTypedArray(runtime, object);

      auto prog = chia::Program::ImportFromBytes(typedArray.toVector(runtime));

      return JsiProgram::toValue(runtime, prog);
    };

    // ----------getTreeHash----------//
    JSI_HOST_FUNCTION(getTreeHash)
    {
      auto newTypedArray = TypedArray<TypedArrayKind::Uint8Array>(runtime, 32);
      auto newBuffer = newTypedArray.getBuffer(runtime);

      std::memcpy(newBuffer.data(runtime), getObject()->GetTreeHash().data(), 32);

      return newTypedArray;
    };

    // ----------getTreeHash----------//
    JSI_HOST_FUNCTION(getSExp)
    {
      return JsiSExp1::toValue(runtime, getObject()->GetSExp());
    };

    JSI_EXPORT_FUNCTIONS(JSI_EXPORT_FUNC(JsiProgram, fromBytes), JSI_EXPORT_FUNC(JsiProgram, getTreeHash), JSI_EXPORT_FUNC(JsiProgram, getSExp))
  };

} // namespace RNClvm
