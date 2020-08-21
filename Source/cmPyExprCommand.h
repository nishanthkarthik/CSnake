#ifndef cmPyExprCommand_h
#define cmPyExprCommand_h

#include "cmConfigure.h"

#include <vector>
#include <string>

class cmExecutionStatus;

bool cmPyExprCommand(std::vector<std::string> const& args,
                     cmExecutionStatus &status);

#endif