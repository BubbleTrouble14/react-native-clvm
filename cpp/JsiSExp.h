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
#include "JsiClvmObject.h"

#include "sexp_prog.h"
#include "types.h"

namespace RNClvm
{

  namespace jsi = facebook::jsi;

  class JsiSExp : public JsiClvmWrappingSharedPtrHostObject<chia::SExp, JsiSExp>
  {
  public:
    // For static methods we set a nullptr
    JsiSExp() : JsiClvmWrappingSharedPtrHostObject<chia::SExp, JsiSExp>(nullptr) {}

    JsiSExp(std::shared_ptr<chia::SExp> sExp)
        : JsiClvmWrappingSharedPtrHostObject<chia::SExp, JsiSExp>(std::move(sExp)) {}

    // ----------fromBytes----------//
    JSI_HOST_FUNCTION(fromBytes)
    {
      auto object = arguments[0].asObject(runtime);
      if (!isTypedArray(runtime, object))
      {
        throw jsi::JSError(runtime, "The 'fromBytes' argument must be an object, but it is not of type Uint8Array.");
      }

      auto typedArray = getTypedArray(runtime, object);

      auto prog = chia::SExp::ImportFromBytes(typedArray.toVector(runtime));

      return JsiSExp::toValue(runtime, prog);
    };

    // ----------fromAssemble----------//
    JSI_HOST_FUNCTION(fromAssemble)
    {
      // Get the string from the first argument
      auto str = arguments[0].asString(runtime).utf8(runtime);

      // Import the sExp using the provided assembly code string
      auto prog = chia::SExp::ImportFromAssemble(str);

      // Wrap the sExp in a JSI object and return it
      return JsiSExp::toValue(runtime, prog);
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

    // ----------run----------//
    JSI_HOST_FUNCTION(run)
    {
      auto clvmObjPtr = JsiClvmObjectFactory::fromJsiValue(runtime, arguments[0]);
      // auto clvmObjPtr = JsiClvmObject<>::fromValue(runtime, arguments[0]); // You'll need to implement unwrapClvmObject.

      auto [cost, result] = getObject()->Run(clvmObjPtr);

      // Create a JS object to hold both the cost and the result.
      auto resultObj = jsi::Object(runtime);

      // Wrap the cost.
      resultObj.setProperty(runtime, "cost", static_cast<double>(cost)); // JSI uses double for numbers.

      auto clvmObj = JsiClvmObjectFactory::createJsiClvmObject(runtime, result);
      resultObj.setProperty(runtime, "value", clvmObj);

      return resultObj;
    }

    JSI_EXPORT_FUNCTIONS(JSI_EXPORT_FUNC(JsiSExp, fromBytes), JSI_EXPORT_FUNC(JsiSExp, getTreeHash), JSI_EXPORT_FUNC(JsiSExp, getSExp), JSI_EXPORT_FUNC(JsiSExp, run), JSI_EXPORT_FUNC(JsiSExp, fromAssemble))
  };

} // namespace RNClvm
