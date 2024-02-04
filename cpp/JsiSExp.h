#pragma once

#include <memory>
#include <string>
#include <utility>

#include "JsiClvmHostObjects.h"
#include "JsiHostObject.h"
#include "TypedArray.h"
#include <jsi/jsi.h>
#include "RNClvmLog.h"

#include "sexp_prog.h"
#include "types.h"

namespace RNClvm
{

  namespace jsi = facebook::jsi;

  class JsiSExp : public JsiCLVMObjectWrapper
  {
  public:
    JsiSExp(chia::CLVMObjectPtr object)
        : JsiCLVMObjectWrapper(std::move(object)) {}

    // Inspect the type of CLVM object
    JSI_HOST_FUNCTION(getNodeType)
    {
      // return jsi::String::createFromUtf8(runtime, chia::NodeTypeToString(getObject()->GetNodeType()));
      return jsi::String::createFromUtf8(runtime, "sdfsdf");
    }

    EXPORT_JSI_API_TYPENAME(JsiSExp, SExp)

    JSI_EXPORT_FUNCTIONS(JSI_EXPORT_FUNC(JsiSExp, getNodeType))
  };

} // namespace RNClvm
