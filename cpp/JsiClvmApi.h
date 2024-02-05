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

#include "JsiProgram.h"
#include "JsiClvmObjectFactory.h"
// #include "JsiSExp.h"

namespace RNClvm
{

  namespace jsi = facebook::jsi;

  class JsiClvmApi : public RNJsi::JsiHostObject
  {
  public:
    static void installApi(jsi::Runtime &runtime);

    JsiClvmApi(jsi::Runtime &runtime) : JsiHostObject()
    {
      installReadonlyProperty("Program", std::make_shared<RNClvm::JsiProgram>());
      // installReadonlyProperty("SExp", std::make_shared<RNClvm::JsiSExp>());
    }

    // int calculate_number(std::string s)
    // {
    //   auto f = chia::Assemble(s);
    //   chia::Program prog(f);
    //   chia::CLVMObjectPtr r;
    //   std::tie(std::ignore, r) = prog.Run();
    //   // EXPECT_EQ(r->GetNodeType(), chia::NodeType::Atom_Int);
    //   return chia::ToInt(r).ToInt();
    // }

    JSI_HOST_FUNCTION(assemble)
    {
      auto str = arguments[0].asString(runtime).utf8(runtime);
      auto f = chia::Assemble(str);
      return JsiClvmObjectFactory::createJsiClvmObject(runtime, f);
      // return JsiSExp::toValue(runtime, f);
    }

    JSI_HOST_FUNCTION(toInt)
    {
      auto clvmObjPtr = JsiClvmObject<>::fromValue(runtime, arguments[0]); // You'll need to implement unwrapClvmObject.
      return jsi::Value(runtime, static_cast<double>(chia::ToInt(clvmObjPtr).ToInt()));
    }

    // JSI_HOST_FUNCTION(sExpFromStream)
    // {
    //   auto object = arguments[0].asObject(runtime);
    //   if (!isTypedArray(runtime, object))
    //   {
    //     throw jsi::JSError(runtime, "The 'fromBytes' argument must be an object, but it is not of type Uint8Array.");
    //   }

    //   auto typedArray = getTypedArray(runtime, object);

    //   auto bytesVector = typedArray.toVector(runtime);

    //   // Simulate the StreamReadFunc functionality using a lambda that captures the bytesVector by reference
    //   chia::StreamReadFunc streamReadFunc = [&bytesVector](int size) -> chia::Bytes
    //   {
    //     static size_t pos = 0; // Consider resetting pos appropriately in production code

    //     if (size + pos > bytesVector.size())
    //     {
    //       throw std::runtime_error("Attempt to read beyond the buffer size");
    //     }

    //     chia::Bytes result(bytesVector.begin() + pos, bytesVector.begin() + pos + size);
    //     pos += size;
    //     return result;
    //   };

    //   // Assuming you have a way to convert this lambda into a form that's usable by your C++ CLVM logic
    //   // For illustration, let's say you have a function similar to SExpFromStream that accepts this lambda
    //   auto result = chia::SExpFromStream(streamReadFunc);

    //   // Wrap the result in a JSI object and return it
    //   return JsiClvmObjectFactory::createJsiClvmObject(runtime, result);
    // }

    JSI_EXPORT_FUNCTIONS(JSI_EXPORT_FUNC(JsiClvmApi, assemble), JSI_EXPORT_FUNC(JsiClvmApi, toInt))
  };
} // namespace RNClvm
