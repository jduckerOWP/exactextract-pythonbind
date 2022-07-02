#include <string>

#include <ogr_geometry.h>
#include <ogr_spatialref.h>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

namespace py = pybind11;

namespace exactextract
{

    void init_box(py::module &);
    void init_cell(py::module &);
    void init_coordinate(py::module &);
    void init_grid(py::module &);
    void init_side(py::module &);
    void init_gdal_dataset_wrapper(py::module &);

    PYBIND11_MODULE(_exactextract, m)
    {
        m.doc() = "test docs!";

        init_box(m);
        init_cell(m);
        init_coordinate(m);
        init_grid(m);
        init_side(m);
        init_gdal_dataset_wrapper(m);

        m.def("print_geom_wkt", [](intptr_t p)
              { 
                OGRGeometry* geom = (OGRGeometry *)p;
                char* buf;
                geom->exportToWkt(&buf);
                py::print(buf); });
    }
}