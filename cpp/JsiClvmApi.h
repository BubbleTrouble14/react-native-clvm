#pragma once

#include <memory>

#include <jsi/jsi.h>

#include "JsiHostObject.h"
#include "TypedArray.h"
#include "RNClvmLog.h"
#include "TypedArray.h"
#include "JsiPromises.h"

#include "assemble.h"
#include "int.h"
#include "operator_lookup.h"
#include "sexp_prog.h"
#include "types.h"
#include "clvm_utils.h"
#include "bech32.h"

#include "JsiProgram.h"
#include "JsiSExp.h"

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
      // RNClvmLogger::logToJavascriptConsole(runtime, str);
      // RNClvmLogger::logToJavascriptConsole(runtime, "(\"this\" \"is the\" \"environement\")");
      auto f = chia::Assemble(str);
      return JsiSExp::toValue(runtime, f);
      // return JsiSExp::toValue(runtime, f);
    }

    JSI_HOST_FUNCTION(toInt)
    {
      auto clvmObjPtr = JsiSExp::fromValue(runtime, arguments[0]); // You'll need to implement unwrapClvmObject.
      return jsi::Value(runtime, static_cast<double>(chia::ToInt(clvmObjPtr).ToInt()));
    }

    JSI_HOST_FUNCTION(sexpFromStream)
    {

      auto object = arguments[0].asObject(runtime);
      auto typedArray = getTypedArray(runtime, object);
      auto bytesVector = typedArray.toVector(runtime);

      return RNJsi::JsiPromises::createPromiseAsJSIValue(
          runtime,
          [bytesVector = std::move(bytesVector)](
              jsi::Runtime &runtime,
              std::shared_ptr<RNJsi::JsiPromises::Promise> promise) -> void
          {
            // Offload the stream reading operation to a separate thread, if necessary
            // For demonstration, assuming synchronous execution for now
            try
            {
              // Instantiate StreamReader with the bytes from TypedArray
              chia::StreamReader reader(bytesVector);

              // Lambda function that wraps the StreamReader's call operator
              auto readFunc = [&reader](int size) -> chia::Bytes
              {
                return reader(size);
              };

              // Parse the s-expression from the stream using the StreamReader through the lambda
              auto sexp = chia::SExpFromStream(readFunc);

              promise->resolve(JsiSExp::toValue(runtime, sexp));
            }
            catch (const std::exception &e)
            {
              promise->reject(e.what());
            }
          });
    }

    JSI_EXPORT_FUNCTIONS(JSI_EXPORT_FUNC(JsiClvmApi, assemble), JSI_EXPORT_FUNC(JsiClvmApi, toInt))
  };
} // namespace RNClvm
