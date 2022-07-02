#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include "side.h"

namespace py = pybind11;

namespace exactextract
{

    void init_side(py::module &m)
    {
        py::enum_<Side>(m, "Side")
            .value("NONE", Side::NONE)
            .value("LEFT", Side::LEFT)
            .value("RIGHT", Side::RIGHT)
            .value("TOP", Side::TOP)
            .value("BOTTOM", Side::BOTTOM)
            .export_values();
    }

}