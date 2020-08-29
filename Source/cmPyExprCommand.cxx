#include "cmPyExprCommand.h"

#include "cmExecutionStatus.h"
#include "cmMakefile.h"
#include "cmMessenger.h"

#include "PyExpr.h"

namespace {
constexpr auto EXPRESSION = "EXPRESSION";
constexpr auto OUTPUT = "OUTPUT";
constexpr auto INPUTS = "INPUTS";
constexpr auto MODULES = "MODULES";
}

bool cmPyExprCommand(const std::vector<std::string>& args,
                     cmExecutionStatus& status)
{
  auto& makeFile = status.GetMakefile();
  makeFile.DisplayStatus("Evaluating py_expr", -1);
  if (args.empty()) {
    status.SetError("called with incorrect number of arguments");
    return false;
  }

  if (args.size() == 1) {
    status.GetMakefile().IssueMessage(MessageType::WARNING,
                                      "Evaluating " + args.front() +
                                        " without side effects");
    makeFile.DisplayStatus(CSnake::PyExpr()(args.front()), -1);
  } else {
    auto context = CSnake::PyExprParser::parse(args, { OUTPUT, EXPRESSION },
                                               { MODULES, INPUTS });

    auto scope = std::map<std::string, std::string>{};
    for (const auto& item : context[INPUTS]) {
      scope.emplace(item, status.GetMakefile().GetRequiredDefinition(item));
    }

    const auto evaluated =
      CSnake::PyExpr()(context[MODULES], scope, context[EXPRESSION].front());

    status.GetMakefile().AddDefinition(context[OUTPUT].front(), evaluated);

    makeFile.DisplayStatus("Multi argument mode", -1);
    makeFile.DisplayStatus(evaluated, -1);
  }
  return true;
}
