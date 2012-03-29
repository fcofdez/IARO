#include <iostream>
#include <tinyxml.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <map>


#include "Triangle.hpp"
#include "LightSource.hpp"


void createXMLLightImpacts(std::map<std::string,int> hits);
std::vector<Triangle *> readXMLMesh(std::string path);
std::vector<LightSource *> readXMLLight(std::string path);

