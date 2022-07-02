#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from osgeo import gdal, ogr

from _exactextract import GDALDatasetWrapper
from .utils import get_addr


def process_polygon_geometry(geom: ogr.Geometry, ds: gdal.Dataset, layer: str,
                             id_field: str):

    print(ds, get_addr(ds.this))
    ds_wrapper = GDALDatasetWrapper(ds.GetDescription(), layer, id_field)

    print(ds_wrapper.id_field())

    ds_wrapper = None
