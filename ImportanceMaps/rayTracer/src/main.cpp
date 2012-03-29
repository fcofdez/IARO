#include "xmlExporter.hpp"
#include "RayTracer.hpp"


int main(int argc, char *argv[])
{
  std::vector<Triangle *> mesh;
  std::vector<LightSource *> lights;
  mesh = readXMLMesh("/tmp/scene.xml");
  lights = readXMLLight("/tmp/light.xml");
  RayTracer * rt = new RayTracer(mesh, lights);
  rt->RayTrace(true);
  createXMLLightImpacts(rt->getHits());
  
  return 0;
}
