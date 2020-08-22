#include "PyExpr.h"

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

PyExpr::PyExpr(std::string expr)
  : m_str{ std::move(expr) }
{
}

std::string PyExpr::operator()()
{
  auto* local = PyDict_New();
  auto* global = PyDict_New();
  auto* result = PyRun_String(m_str.c_str(), Py_eval_input, global, local);
  auto* repr = PyObject_Repr(result);
  auto reprString = std::string(PyUnicode_AsUTF8(repr));
  return reprString;
}
}