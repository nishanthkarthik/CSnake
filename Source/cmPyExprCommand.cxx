#include "cmPyExprCommand.h"

#include "cmExecutionStatus.h"
#include "cmMakefile.h"
#include "cmMessenger.h"

#include "PyExpr.h"

bool cmPyExprCommand(const std::vector<std::string>& args,
                     cmExecutionStatus& status)
{
  auto& makeFile = status.GetMakefile();
  makeFile.DisplayStatus("Hello world py_expr", -1);
  makeFile.DisplayStatus("Evaluating " + args.front(), -1);
  makeFile.DisplayStatus(CSnake::PyExpr(args.front())(), -1);
  return true;
}
