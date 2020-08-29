#ifndef cmPyFFICommand_h
#define cmPyFFICommand_h

#include "cmConfigure.h"

#include <string>
#include <vector>

class cmExecutionStatus;

bool cmPyFFICommand(std::vector<std::string> const& args,
                    cmExecutionStatus& status);

#endif