#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import ctypes
from typing import Any


def get_addr(c: Any):
    return ctypes.c_long(c).value