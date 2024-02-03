#pragma once

#include <memory>

#include <jsi/jsi.h>

#include "JsiHostObject.h"
#include "TypedArray.h"

#include "assemble.h"
#include "int.h"
#include "operator_lookup.h"
#include "sexp_prog.h"
#include "types.h"
#include "clvm_utils.h"

#include "bech32.h"

#include "RNClvmLog.h"

namespace RNClvm
{

  namespace jsi = facebook::jsi;

  class JsiClvmApi : public RNJsi::JsiHostObject
  {
  public:
    static void installApi(jsi::Runtime &runtime);

    JsiClvmApi(jsi::Runtime &runtime) : JsiHostObject()
    {
    }

    int calculate_number(std::string s)
    {
      auto f = chia::Assemble(s);
      chia::Program prog(f);
      chia::CLVMObjectPtr r;
      std::tie(std::ignore, r) = prog.Run();
      // EXPECT_EQ(r->GetNodeType(), chia::NodeType::Atom_Int);
      return chia::ToInt(r).ToInt();
    }

    JSI_HOST_FUNCTION(calculateNumber)
    {
      if (count != 1)
      {
        throw jsi::JSError(runtime, "calculateNumber(..) expects one argument (string)!");
      }

      if (!arguments[0].isString())
      {
        throw jsi::JSError(runtime, "Expected string argument!");
      }

      // Get the string argument
      std::string s = arguments[0].asString(runtime).utf8(runtime);

      // Call the calculate_number function and get the result
      int result = calculate_number(s);

      // Return the result as a JSI Value
      return jsi::Value(result);
    };

    JSI_EXPORT_FUNCTIONS(JSI_EXPORT_FUNC(JsiClvmApi, calculateNumber))
  };
} // namespace RNClvm
