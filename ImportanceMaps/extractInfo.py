#!/usr/bin/python
# -*- mode:python; coding:utf-8; tab-width:4 -*-
import bpy

from math import *
from material import Material
from light import *
from meshInfo import *
from util import *
from ratio import *

def getSubdivisionLevels(element):
    """Gets number of subdivision levels
    FIXME - First Subdivision modifier only?
    Arguments:
    - `element`:
    """
    for modifier in element.modifiers:
        if modifier.type == 'SUBSURF':
            return modifier.render_levels


def getDistance(pointA, pointB):
    return sqrt(pow(pointA[0]-pointB[0],2)+
                pow(pointA[1]-pointB[1],2)+
                pow(pointA[2]-pointB[2],2))


def getMaterialPropertys(element):
    """Gets the material propertys like
    Mirror, Transparency Depth
    Texture propertys...

    Arguments:
    - `element`:
    """
    materials = []
    for meshMaterial in element.data.materials:
        name = meshMaterial.name
        transparencyRT = False
        transparencyDepth = 0
        mirrorRT = False
        mirrorDepth = 0
        tmpMaterial = None

        if meshMaterial.transparency_method == 'RAYTRACE':
            transparencyRT = True
            transparencyDepth = meshMaterial.raytrace_transparency.depth
        if meshMaterial.raytrace_mirror.use == True:
            mirrorRT = True
            mirrorDepth = meshMaterial.raytrace_mirror.depth

        tmpMaterial = Material(name, transparencyRT, transparencyDepth,
                               mirrorRT, mirrorDepth)

        for materialTexture in meshMaterial.texture_slots:
            if materialTexture:
                if materialTexture.texture.type == 'IMAGE':
                    if materialTexture.texture.image:
                        tmpMaterial.setImageTextureData(materialTexture.texture.image.name,
                                                        materialTexture.texture.image.size[0],
                                                        materialTexture.texture.image.size[1])
        materials.append(tmpMaterial)

    return materials


def extractInfo(path):
    """
    """
    camera = bpy.data.objects['Camera']
    meshInfoList = []
    for element in bpy.data.objects:
        if element.type == 'MESH':
            name = element.name
            subDivisionlevels = 0
            poligons = len(element.data.faces)
            cameraDistance = getDistance(camera.location,element.location)
            if len(element.modifiers) > 0:
                subDivisionlevels = getSubdivisionLevels(element)
            materials = getMaterialPropertys(element)
            meshInfoList.append(MeshInfo(name, poligons, cameraDistance,
                                             materials, subDivisionlevels))
                
    meshRatioList = getSceneRatio()
    lightImpactsList = getLightImpacts(bpy.data, path)


    for meshRatio in meshRatioList:
        index = getIndexElement(meshRatio[0],meshInfoList)
        meshInfoList[index].setRatio(meshRatio[1])

    for lightImpact in lightImpactsList:
        index = getIndexElement(lightImpact[0],meshInfoList)
        if index != None:
            meshInfoList[index].setImpacts(lightImpact[1])
    return meshInfoList
