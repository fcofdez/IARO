#!/usr/bin/python
# -*- mode:python; coding:utf-8; tab-width:4 -*-
#import commands
import os

import random
import itertools
import bpy

from util import setRenderSettings

global colorList 

def convertRGBIMFormat(colors):
    """Converts from Blender RGB format
    to 0-255 format.
    Arguments:
    - `colors`:
    """
    return (colors[0], colors[1]*255, colors[2]*255, colors[3]*255)      
    

def buildColorList():
    """
    """
    colorPercentage = [255,192,128,64,0]
    global colorList
    colorList = list(itertools.permutations([255,192,128,64,0],3))


def generateRandomNumber():
    """Generates a random Number
    """
    return random.randint(0,59)
    

def convertScene(sceneData):
    """ 
    """
    
    global colorList
    
    colorIndex = 0
    
    color = []
    for mesh in sceneData.objects:
        if mesh.type == 'MESH':
            if len(mesh.material_slots) == 0:
                mesh.data.materials.append(bpy.data.materials.new('ratio'))
            texture = mesh.material_slots[0]
            texture.material.use_shadeless = True
            colorIndex = generateRandomNumber()
            texture.material.diffuse_color[0] = colorList[colorIndex][0]/255
            texture.material.diffuse_color[1] = colorList[colorIndex][1]/255
            texture.material.diffuse_color[2] = colorList[colorIndex][2]/255
            color.append(convertRGBIMFormat((mesh.name, 
                                            texture.material.diffuse_color[0], 
                                            texture.material.diffuse_color[1], 
                                            texture.material.diffuse_color[2])))
            
  
    return color


def getRatiofromMesh(name, r, g, b):
    """
    
    Arguments:
    - `data`:
    """
    
    subcommand1 = 'convert -fuzz 25% -fill \'rgb(0,0,0)\' +opaque \'rgb('  
    subcommand2 = ')\' -fill \'rgb(255,255,255)\' -opaque \'rgb(' 
    subcommand3 = ')\' -print "%[fx:w*h*image.mean]" /tmp/untitled0001.png null:' 
    
    colorCommand = str(int(r))+','+str(int(g))+','+str(int(b))
    
    p = os.popen(subcommand1+colorCommand+subcommand2+colorCommand+subcommand3).read()
    number = float(p)
    ratio = (number)/(960*540)
    return (name, ratio)



def getSceneRatio():
    """Returns a list containing mesh name and his approximate
    """#ratio in the scene 2d image

    buildColorList()

    colors = convertScene(bpy.data)

    meshRatio = []
    
    setRenderSettings(1)

 
    bpy.ops.wm.save_as_mainfile(filepath='/tmp/ea2.blend')
    os.system('blender -b /tmp/ea2.blend -o /tmp/untitled -F PNG -x 1 -f 1')
    for color in colors:
        meshRatio.append(getRatiofromMesh(color[0], color[1], color[2], color[3]))

    return meshRatio


