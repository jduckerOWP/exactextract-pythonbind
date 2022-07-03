#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pathlib
from typing import Optional, Union
from osgeo import gdal

from _exactextract import GDALRasterWrapper

from .utils import get_ds_path


def to_gdal_raster_wrapper(filename_or_ds: Union[str, pathlib.Path,
                                                 gdal.Dataset],
                           band_idx: int = 1):
    """
    Return exactextract GDALRasterWrapper object from Python OSGeo Dataset
    object or from file path.

    Args:
        filename_or_ds (Union[str, pathlib.Path, gdal.Dataset]): File path or OSGeo Dataset / DataSource
        band_idx (int, optional): Raster band index. Defaults to 1.

    Raises:
        ValueError: If raster band index is <= 0
        RuntimeError: If path to dataset is not found.
        RuntimeError: If dataset could not be opened.
        ValueError: If raster band index is invalid.

    Returns:
        GDALRasterWrapper: exactextract GDALRasterWrapper object
    """
    # Sanity check inputs, set default band_idx
    if band_idx is not None and band_idx <= 0:
        raise ValueError('Raster band index starts from 1!')
    elif band_idx is None:
        band_idx = 1

    # Get file path based on input, filename or dataset
    if isinstance(filename_or_ds, gdal.Dataset):
        path = pathlib.Path(get_ds_path(filename_or_ds))
    else:
        path = pathlib.Path(filename_or_ds)

    # Assert the path exists and resolve the full path
    if not path.exists():
        raise RuntimeError('File path not found: %s' % str(path))
    path = path.resolve()

    # Name of the dataset
    this_ds_name = str(path)

    # Open the dataset and load the layer of interest
    try:
        tmp_ds: Optional[gdal.Dataset] = gdal.Open(this_ds_name)
        if tmp_ds is None:
            raise RuntimeError('Failed to open dataset!')

        if band_idx > tmp_ds.RasterCount():
            raise ValueError('Band index is greater than raster count!')
    finally:
        # Clean up
        tmp_ds = None

    # Put it all together
    return GDALRasterWrapper(this_ds_name, band_idx)
