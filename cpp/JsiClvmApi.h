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

    JSI_HOST_FUNCTION(assemble)
    {
      auto str = arguments[0].asString(runtime).utf8(runtime);
      auto f = chia::Assemble(str);
      return JsiSExp::toValue(runtime, f);
    }

    JSI_EXPORT_FUNCTIONS(JSI_EXPORT_FUNC(JsiClvmApi, assemble))
  };
} // namespace RNClvm
