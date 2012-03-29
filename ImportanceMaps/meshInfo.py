#!/usr/bin/python
# -*- mode:python; coding:utf-8; tab-width:4 -*-

class MeshInfo(object):

    def __init__(self, name, poligons, cameraDistance, materials, subdivisionlevels):
        self._name = name
        self._poligons = poligons
        self._cameraDistance = cameraDistance
        self._materials = materials
        self._subdivisionlevels = subdivisionlevels
        self._ratio = 0
        self._impacts = 0
        self._textureMean = 0
        self._transpDepth = 0
        self._mirrorDepth = 0
        self._importance = 0

    def printM(self):
        print(self._ratio)
        print(self._impacts)
        print(self._poligons)
        

    def setRatio(self , ratio):
        self._ratio = ratio


    def setImpacts(self , impacts):
        self._impacts = impacts


    def setTotalImportance(self, maxPoligons, maxCameraDistance, 
                           maxTranspRTD, maxMirrorRTD, 
                           maxImpacts, maxTextSize):
        self._poligons /= maxPoligons
        self._cameraDistance /= maxCameraDistance 
        self._impacts /= maxImpacts
        
        meshTextMean = 0
        meshTranspDepth = 0
        meshMirrorDepth = 0

        for material in self._materials:
            if material._mirrorRT:
                material._mirrorDepth /= maxMirrorRTD

            if material._transparencyRT:
                material._transparencyDepth /= maxTranspRTD

            textureMean = 0
            for texture in material._textures:
                textureMean += texture._xSize*texture._ySize / maxTextSize
            if len(material._textures):
                material._textureMean = textureMean / len(material._textures)
            
            meshTextMean += material._textureMean
            meshTranspDepth += material._transparencyDepth
            meshMirrorDepth += material._mirrorDepth
            
        if len(self._materials) > 0:
            self._textureMean = meshTextMean / len(self._materials)
            self._transpDepth = meshTranspDepth / len(self._materials)
            self._mirrorDepth = meshMirrorDepth / len(self._materials)

    def setImportance(self, poligonsRatio, cameraDistanceRatio, 
                      transpRatio, mirrorRatio, impactsRatio, textSizeRatio, imageRatio):
        self._importance = self._poligons*poligonsRatio + self._cameraDistance*cameraDistanceRatio  + self._transpDepth*transpRatio  + self._mirrorDepth*mirrorRatio  +  self._textureMean*textSizeRatio  + self._ratio*imageRatio  + self._impacts * impactsRatio
        
                
