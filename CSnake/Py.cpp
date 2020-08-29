#include "Py.h"

#include <fstream>
#include <stdexcept>
#include <utility>

#include "Python.h"

namespace CSnake {
PyScope::PyScope()
{
  Py_Initialize();
}

PyScope::~PyScope()
{
  Py_Finalize();
}

std::string Py::operator()(const std::string& expr)
{
  auto* local = PyDict_New();
  auto* global = PyDict_New();
  auto* result = PyRun_String(expr.c_str(), Py_eval_input, global, local);
  auto* repr = PyObject_Repr(result);
  return { PyUnicode_AsUTF8(repr) };
}

std::string Py::operator()(const std::vector<std::string>& modules,
                           const std::map<std::string, std::string>& scope,
                           const std::string& expr)
{
  auto* local = PyDict_New();
  for (const auto& it : scope) {
    PyDict_SetItem(local, PyUnicode_FromString(it.first.c_str()),
                   PyUnicode_FromString(it.second.c_str()));
  }

  auto* global = PyDict_New();
  for (const auto& item : modules) {
    auto* module = PyImport_ImportModule(item.c_str());
    PyDict_SetItemString(global, item.c_str(), module);
  }

  auto* result = PyRun_String(expr.c_str(), Py_eval_input, global, local);
  return { PyUnicode_AsUTF8(PyObject_Repr(result)) };
}

std::string Py::operator()(const std::vector<std::string>& inputs,
                           const std::string& modulePath,
                           const std::string& fn)
{
  auto* global = PyDict_New();
  auto* module = PyModule_New("csnake");
  PyModule_AddStringConstant(module, "__file__", modulePath.c_str());

  {
    auto* moduleScope = PyModule_GetDict(module);
    std::ifstream file{ modulePath, std::ios::in };
    std::string fileContents(std::istreambuf_iterator<char>{ file }, {});
    auto* result = PyRun_String(fileContents.c_str(), Py_file_input,
                                moduleScope, moduleScope);
    assert(result != nullptr);
  }

  auto* func = PyObject_GetAttrString(module, fn.c_str());
  assert(func && PyCallable_Check(func));

  auto* argsTuple = PyTuple_New(inputs.size());
  for (size_t i = 0; i < inputs.size(); ++i) {
    PyTuple_SetItem(argsTuple, i, PyUnicode_FromString(inputs[i].c_str()));
  }

  auto* result = PyObject_CallObject(func, argsTuple);
  assert(result);

  return { PyUnicode_AsUTF8(PyObject_Repr(result)) };
}
}

namespace CSnake {
std::map<std::string, std::vector<std::string>> CMakeArgParser::parse(
  const std::vector<std::string>& input, const std::set<std::string>& one,
  const std::set<std::string>& many)
{
  std::map<std::string, std::vector<std::string>> result;
  auto it = input.begin();
  auto end = input.end();
  while (it != end) {
    if (one.find(*it) != one.end()) {
      if (it + 1 == end) {
        throw std::runtime_error{ "Missing value for key " + *it };
      }
      result[*it].emplace_back(*(it + 1));
      it += 2;
    } else if (many.find(*it) != many.end()) {
      const auto key = *it++;
      while (it != end && one.find(*it) == one.end() &&
             many.find(*it) == many.end()) {
        result[key].emplace_back(*it);
        ++it;
      }
    } else {
      throw std::runtime_error{ "Can not find key for token " + *it };
    }
  }
  return result;
}
}