#!/usr/bin/python
# -*- mode:python; coding:utf-8; tab-width:4 -*-
from xmlParser import *
import os

def getLightImpacts(scene,path):
    """Returns a list containing mesh and light hits
    
    Arguments:
    - `scene`:
    """
    exportMesh(scene.objects)
    exportLight(scene.objects, scene.lamps)
    os.system(path+"/rayTracer/build/raytracer")
    return importLightImpacts('/tmp/lightsImpacts.xml')
