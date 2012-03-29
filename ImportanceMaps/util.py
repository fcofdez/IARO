#!/usr/bin/python
# -*- mode:python; coding:utf-8; tab-width:4 -*-
import bpy

def getIndexElement(attribute, lista):
    lista2 = [i for i, x in enumerate(lista) if x._name == attribute ]
    if len(lista2) > 0:
        return lista2[0]
    else:
        return None

def readConfigFile(path):
    f = open(path, 'r')
    lines = f.readlines()
    for line in lines:
        if line[0] != '#':
            ratios = line.split()
    numericRatio = []
    sum = 0
    
    for ratio in ratios:
        numericRatio.append(float(ratio))
        sum += float(ratio)
    if sum > 1:
        print('Error in config file')
    else:
        return numericRatio



def setRenderSettings(backGround):
    """Sets render settings to render ratio detection image
    """
    bpy.context.scene.world.ambient_color[0] = backGround
    bpy.context.scene.world.ambient_color[1] = backGround
    bpy.context.scene.world.ambient_color[2] = backGround

    bpy.context.scene.world.horizon_color[0] = backGround
    bpy.context.scene.world.horizon_color[1] = backGround
    bpy.context.scene.world.horizon_color[2] = backGround
    
    bpy.context.scene.world.use_sky_blend = False
    bpy.context.scene.world.use_sky_paper = False
    bpy.context.scene.world.use_sky_real = False

    bpy.context.scene.render.resolution_percentage = 50

    bpy.context.scene.render.resolution_x = 1920
    bpy.context.scene.render.resolution_y = 1080
    
    bpy.context.scene.render.use_raytrace = False
    bpy.context.scene.render.use_textures = False
    bpy.context.scene.render.use_shadows = False
    bpy.context.scene.render.use_envmaps = False

