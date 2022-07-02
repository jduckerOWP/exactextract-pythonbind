#include <stdint.h>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <gdal.h>
#include <gdal_priv.h>

#include "gdal_dataset_wrapper.h"
#include "gdal_raster_wrapper.h"
#include "operation.h"
#include "output_writer.h"
#include "processor.h"
#include "feature_sequential_processor.h"
#include "raster_sequential_processor.h"
#include "raster_source.h"

namespace py = pybind11;

namespace exactextract
{

    void init_gdal_dataset_wrapper(py::module &m)
    {
        py::class_<GDALDatasetWrapper>(m, "GDALDatasetWrapper")
            .def(py::init<const std::string &, const std::string &, const std::string &>())
            .def("feature_field", &GDALDatasetWrapper::feature_field)
            .def("id_field", &GDALDatasetWrapper::id_field);

        py::class_<RasterSource>(m, "RasterSource")
            .def("set_name", &RasterSource::set_name, py::arg("name"))
            .def("name", &RasterSource::name);

        py::class_<GDALRasterWrapper, RasterSource>(m, "GDALRasterWrapper")
            .def(py::init<const std::string &, int>())
            .def("grid", &GDALRasterWrapper::grid)
            .def("read_box", &GDALRasterWrapper::read_box, py::arg("box"));

        py::class_<Operation>(m, "Operation")
            .def(py::init<std::string, std::string, RasterSource *, RasterSource *>())
            .def("weighted", &Operation::weighted)
            .def("grid", &Operation::grid)
            .def_readonly("stat", &Operation::stat)
            .def_readonly("name", &Operation::name)
            .def_readonly("values", &Operation::values)
            .def_readonly("weights", &Operation::weights);

        py::class_<OutputWriter>(m, "OutputWriter")
            .def("write", &OutputWriter::write, py::arg("fid"))
            .def("add_operation", &OutputWriter::add_operation, py::arg("op"))
            .def("set_registry", &OutputWriter::set_registry, py::arg("reg"))
            .def("finish", &OutputWriter::finish);

        py::class_<Processor>(m, "Processor")
            .def("process", &Processor::process)
            .def("set_max_cells_in_memory", &Processor::set_max_cells_in_memory, py::arg("n"))
            .def("show_progress", &Processor::show_progress, py::arg("val"));

        py::class_<FeatureSequentialProcessor, Processor>(m, "FeatureSequentialProcessor")
            .def(py::init<GDALDatasetWrapper &, OutputWriter &, const std::vector<Operation> &>())
            .def("process", &FeatureSequentialProcessor::process);

        py::class_<RasterSequentialProcessor, Processor>(m, "RasterSequentialProcessor")
            .def(py::init<GDALDatasetWrapper &, OutputWriter &, const std::vector<Operation> &>())
            .def("read_features", &RasterSequentialProcessor::read_features)
            .def("populate_index", &RasterSequentialProcessor::populate_index)
            .def("process", &RasterSequentialProcessor::process);
    }

}