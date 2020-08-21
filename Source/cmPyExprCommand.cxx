#include "cmPyExprCommand.h"

#include "cmExecutionStatus.h"
#include "cmMakefile.h"
#include "cmMessenger.h"

bool cmPyExprCommand(const std::vector<std::string>& args,
                     cmExecutionStatus& status)
{
    auto &makeFile = status.GetMakefile();
    makeFile.DisplayStatus("Hello world py_expr", -1);
    return true;
}
