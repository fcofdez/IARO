#!/usr/bin/python
# -*- mode:python; coding:utf-8; tab-width:4 -*-
from texture import *  

class Material(object):
    """Class that contains information about material
    """
    
    def __init__(self, name, transparencyRT = False , transparencyDepth = -1, 
                 mirrorRT = False , mirrorDepth = -1 ):
        """
        
        Arguments:
        - `name`:
        - `transparencyRT`:
        - `transparencyDepth`:
        - `mirrorRT`:
        - `mirrorDepth`:
        """
        self._name = name
        self._transparencyRT = transparencyRT
        self._transparencyDepth = transparencyDepth
        self._mirrorRT = mirrorRT
        self._mirrorDepth = mirrorDepth
        self._textures = []
        self._textureMean = 0
        
    def setImageTextureData(self, image, xSize, ySize):
        self._textures.append(Texture(image,xSize,ySize))
     
