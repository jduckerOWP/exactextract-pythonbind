#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from typing import List, Union
from _exactextract import FeatureSequentialProcessor as _FeatureSequentialProcessor, RasterSequentialProcessor as _RasterSequentialProcessor

from .dataset import GDALDatasetWrapper
from .operation import Operation
from .writer import MapWriter, GDALWriter


class FeatureSequentialProcessor(_FeatureSequentialProcessor):

    def __init__(self, ds_wrapper: GDALDatasetWrapper,
                 writer: Union[MapWriter,
                               GDALWriter], op_list: List[Operation]):
        super().__init__(ds_wrapper, writer, op_list)


class RasterSequentialProcessor(_RasterSequentialProcessor):
    pass