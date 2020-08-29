#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

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
  std::string operator()(const std::string& expr);

  std::string operator()(const std::vector<std::string>& modules,
                         const std::map<std::string, std::string>& scope,
                         const std::string& expr);

private:
  PyScope m_scope;
};

class PyExprParser
{
public:
  static std::map<std::string, std::vector<std::string>> parse(
    const std::vector<std::string>& input, const std::set<std::string>& one,
    const std::set<std::string>& many);
};
}