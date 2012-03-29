#!/usr/bin/python
# -*- mode:python; coding:utf-8; tab-width:4 -*-
import sys

path = '/home/fran/ImportanceMaps'
sys.path.append(path)

from extractInfo import *
from normalizeInfo import *
from util import *
import bpy

if __name__ == '__main__':
    global path
    configPath = path+'/config.cfg'
    ratiosList = readConfigFile(configPath)
    
    meshInfoList = extractInfo(path)
    meshInfoList = normalizeMeshInfo(meshInfoList)
    
    for meshInfo in meshInfoList:
        meshInfo.setImportance(ratiosList[0], ratiosList[1], ratiosList[2] , 
                               ratiosList[3], ratiosList[4], ratiosList[5], ratiosList[6])
    
    meshInfoList = normalizeMeshComplexity(meshInfoList)
    for meshInfo in meshInfoList:
        bpy.data.objects[meshInfo._name].data.materials[0].use_shadeless = True
        bpy.data.objects[meshInfo._name].data.materials[0].diffuse_color[0] = meshInfo._importance
        bpy.data.objects[meshInfo._name].data.materials[0].diffuse_color[1] = meshInfo._importance
        bpy.data.objects[meshInfo._name].data.materials[0].diffuse_color[2] = meshInfo._importance

    setRenderSettings(0)
    
    
    bpy.ops.wm.save_as_mainfile(filepath='/tmp/ea3.blend')
    os.system('blender -b /tmp/ea3.blend -o '+path+'/map -F PNG -x 1 -f 1')


        
        
        
        
    
