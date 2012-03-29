#!/usr/bin/python
# -*- mode:python; coding:utf-8; tab-width:4 -*-
from operator import attrgetter
from meshInfo import *

def normalizeMeshInfo(meshInfoListB):
    """
    Arguments:
    - `meshInfoList`:
    """
    meshInfoList = meshInfoListB
    maxSubDivisionLevel = max(meshInfoList, key=attrgetter('_subdivisionlevels'))._subdivisionlevels
    maxPoligons = max(meshInfoList, key=attrgetter('_poligons'))._poligons
    maxTranspRTD = -2
    maxMirrorRTD = -2
    maxDistance = max(meshInfoList, key=attrgetter('_cameraDistance'))._cameraDistance
    maxImpacts = max(meshInfoList, key=attrgetter('_impacts'))._impacts 
    maxTextSize = -2

    for meshInfo in meshInfoList:
        if len(meshInfo._materials) > 0:
            maxTranspRTD = max(meshInfo._materials, key=attrgetter('_transparencyDepth'))._transparencyDepth
            maxMirrorRTD = max(meshInfo._materials, key=attrgetter('_mirrorDepth'))._mirrorDepth
        
            for meshMaterial in meshInfo._materials:
                for texture in meshMaterial._textures:
                    if texture._xSize * texture._ySize > maxTextSize:
                        maxTextSize = texture._xSize * texture._ySize
    
    for meshInfo in meshInfoList:
        meshInfo.setTotalImportance(maxPoligons , maxDistance, 
                                    maxTranspRTD , maxMirrorRTD,
                                    maxImpacts , maxTextSize)
    return meshInfoList

def normalizeMeshComplexity(meshInfoL):
    meshInfoList = meshInfoL
    maxComplex = max(meshInfoList, key=attrgetter('_importance'))._importance
    
    for meshInfo in meshInfoList:
        
        meshInfo._importance /= maxComplex
        
    return meshInfoList
