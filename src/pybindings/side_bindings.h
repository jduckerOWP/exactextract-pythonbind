#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace exactextract
{
    void bind_side(py::module &m);
}