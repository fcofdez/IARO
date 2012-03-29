#!/usr/bin/python
# -*- mode:python; coding:utf-8; tab-width:4 -*-
class Texture(object):
    """Represents texture data
    """
    
    def __init__(self, image, xSize, ySize):
        """
        
        Arguments:
        - `image`:
        - `xSize`:
        - `ySize`:
        """
        self._image = image
        self._xSize = xSize
        self._ySize = ySize


