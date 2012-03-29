#!/usr/bin/python
# -*- mode:python; coding:utf-8; tab-width:4 -*-
from xml.dom.minidom import *
import sys
import bpy

def exportMesh(sceneData):
    """Exports meshes from a scene to an xml file
    
    Arguments:
    - `sceneData`:
    """
    doc = Document()
    node = doc.createElement('Scene')

    for element in sceneData:
        if element.type == 'MESH':
            worldMatrix = element.matrix_world
            vertices = element.data.vertices
            nodeMesh = doc.createElement('Mesh')
            nodeMesh.setAttribute('name',element.name)
            for face in element.data.faces:
                nodeTriangle = doc.createElement('Triangle')
                for verticeIndex in face.vertices:
                    nodePoint = doc.createElement('point')
                    coord = worldMatrix * vertices[verticeIndex].co
                    nodePoint.appendChild(doc.createTextNode(str(coord[0])
                                                             +' '+str(coord[1])+' '+
                                                             str(coord[2])))
                    nodeTriangle.appendChild(nodePoint)
                nodeNormal = doc.createElement('vectorNormal')
                nodeNormal.appendChild(doc.createTextNode(str(face.normal[0])+' '+
                                                          str(face.normal[1])+' '+
                                                          str(face.normal[2])))
                nodeTriangle.appendChild(nodeNormal)
                nodeMesh.appendChild(nodeTriangle)
            node.appendChild(nodeMesh)
    doc.appendChild(node)
    f = open('/tmp/scene.xml', 'w')
    doc.writexml(f)
    f.close()

def exportLight(sceneData, lamps):
    doc = Document()
    node = doc.createElement('Scene')

    for element in sceneData:
        if element.type == 'LAMP':
            nodeLight = doc.createElement('Light')
            nodeLight.setAttribute('name',element.name)
            nodeRotation = doc.createElement('Rotation')
            nodeLocation = doc.createElement('Location')
            nodeEnergy = doc.createElement('Energy')

            nodeLocation.appendChild(doc.createTextNode(str(element.location[0])+' '+
                                     str(element.location[1])+' '+
                                     str(element.location[2])))
            nodeRotation.appendChild(doc.createTextNode(str(element.rotation_euler[0])+' '+
                                     str(element.rotation_euler[1])+' '+
                                     str(element.rotation_euler[2])))
            nodeEnergy.appendChild(doc.createTextNode(str(lamps[element.name].energy)))
            nodeLight.appendChild(nodeLocation)
            nodeLight.appendChild(nodeRotation)
            nodeLight.appendChild(nodeEnergy)
            node.appendChild(nodeLight)
    doc.appendChild(node)
    f = open('/tmp/light.xml', 'w')
    doc.writexml(f)
    f.close()


def importLightImpacts(path):
    """Import from an xml file light impacts on a scene
    
    Arguments:
    - `path`:
    """
    dom = parse(path)
    lightImpacts = []
    meshes = dom.getElementsByTagName('Mesh')
    for mesh in meshes:
        meshName = mesh.getAttribute('name')
        lightImpacts.append((meshName, int(mesh.childNodes[0].nodeValue)))
    return lightImpacts
