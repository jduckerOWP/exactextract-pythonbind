#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from typing import Union

from . import Grid__infinite_extent, Grid__bounded_extent


def grid_class_from_extent(
        extent_tag: str) -> Union[Grid__infinite_extent, Grid__bounded_extent]:
    if extent_tag == 'infinite_extent':
        return Grid__infinite_extent
    elif extent_tag == 'bounded_extent':
        return Grid__bounded_extent
    else:
        raise ValueError(
            'Unknown extent tag: \'%s\'! Expected \'infinite_extent\' or \'bounded_extent\'.'
            % repr(extent_tag))
