#pragma once

#include <string>

namespace CSnake {
class PyScope
{
public:
  PyScope();
  ~PyScope();
  PyScope(PyScope&&) = delete;
  PyScope& operator=(PyScope&&) = delete;
};

class PyExpr
{
public:
  PyExpr(std::string expr);
  std::string operator()();

private:
  PyScope m_scope;
  std::string m_str;
};
}