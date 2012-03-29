#ifndef _RAYTRACER_H_
#define _RAYTRACER_H_

#include <cstdlib>
#include <string>
#include <vector>
#include <map>


#include "Triangle.hpp"
#include "LightSource.hpp"
#include "Vector.hpp"
#include "Ray.hpp"
#include "Bvh.hpp"


#define RAYS_TO_TRACE 5000

class RayTracer
{
public:
  RayTracer(std::vector<Triangle *> meshData, std::vector<LightSource *> lights);
  bool loadSceneFile(std::string path);
  bool RayTrace(bool indorLightSources);
  bool createOutputFile(std::string finalFile);
  std::map<std::string, int> getHits();
  virtual ~RayTracer();

private:
  std::vector<Triangle *> __objects;
  std::vector<LightSource *> __lightSources;
  Bvh __bvh;
  
  std::map<std::string, int> __meshHits;
  Vector Trace(Ray* ray);
  Ray * castRay(LightSource* ls);
  double getMaxLightEnergy(std::string lightSourceType);
  double pointToPointDistance(Vector p1, Vector p2);
};


#endif /* _RAYTRACER_H_ */
