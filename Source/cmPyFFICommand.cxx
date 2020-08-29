#include "cmPyFFICommand.h"

#include "cmExecutionStatus.h"
#include "cmMakefile.h"
#include "cmMessenger.h"

#include "Py.h"

namespace {
constexpr auto INPUTS = "INPUTS";
constexpr auto MODULE = "MODULE";
constexpr auto FN = "FN";
constexpr auto OUTPUT = "OUTPUT";
}

bool cmPyFFICommand(const std::vector<std::string>& args,
                    cmExecutionStatus& status)
{
  auto& makeFile = status.GetMakefile();
  makeFile.DisplayStatus("Evaluating py_ffi", -1);
  if (args.empty()) {
    status.SetError("called with incorrect number of arguments");
    return false;
  }

  makeFile.DisplayStatus("Reading FFI args", -1);
  auto context =
    CSnake::CMakeArgParser::parse(args, { MODULE, FN, OUTPUT }, { INPUTS });

  makeFile.DisplayStatus("Evaluating FFI", -1);
  auto result = CSnake::Py()(context[INPUTS], context[MODULE].front(),
                             context[FN].front());

  makeFile.DisplayStatus("FFI Call Done", -1);
  makeFile.AddDefinition(context[OUTPUT].front(), result);
  return true;
}
