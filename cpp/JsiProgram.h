#pragma once

#include <memory>
#include <string>
#include <utility>

#include "JsiClvmHostObjects.h"
#include "JsiHostObject.h"
#include "TypedArray.h"
#include <jsi/jsi.h>
#include "RNClvmLog.h"

// #include "JsiSExp.h"
// #include "JsiSExp1.h"
#include "JsiClvmObjectFactory.h"

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

    // ----------fromAssemble----------//
    JSI_HOST_FUNCTION(fromAssemble)
    {
      // Get the string from the first argument
      auto str = arguments[0].asString(runtime).utf8(runtime);

      // Import the program using the provided assembly code string
      auto prog = chia::Program::ImportFromAssemble(str);

      // Wrap the program in a JSI object and return it
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
      return JsiClvmObjectFactory::createJsiClvmObject(runtime, getObject()->GetSExp());
      // return JsiSExp::toValue(runtime, getObject()->GetSExp());
    };

    // ----------getTreeHash----------//
    JSI_HOST_FUNCTION(run)
    {
      auto clvmObjPtr = JsiClvmObject::fromValue(runtime, arguments[0]); // You'll need to implement unwrapClvmObject.

      auto [cost, result] = getObject()->Run(clvmObjPtr);

      // Create a JS object to hold both the cost and the result.
      auto resultObj = jsi::Object(runtime);

      // Wrap the cost.
      resultObj.setProperty(runtime, "cost", static_cast<double>(cost)); // JSI uses double for numbers.

      auto clvmObj = JsiClvmObjectFactory::createJsiClvmObject(runtime, result);
      resultObj.setProperty(runtime, "value", clvmObj);

      return resultObj;
    }

    JSI_EXPORT_FUNCTIONS(JSI_EXPORT_FUNC(JsiProgram, fromBytes), JSI_EXPORT_FUNC(JsiProgram, getTreeHash), JSI_EXPORT_FUNC(JsiProgram, getSExp), JSI_EXPORT_FUNC(JsiProgram, run), JSI_EXPORT_FUNC(JsiProgram, fromAssemble))
  };

} // namespace RNClvm
