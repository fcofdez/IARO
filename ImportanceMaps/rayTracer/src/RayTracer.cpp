#include "RayTracer.hpp"
#include <iostream> 
RayTracer::RayTracer(std::vector<Triangle *> meshData, std::vector<LightSource *> lights)
{
  __objects = meshData;
  __bvh = Bvh(__objects);
  __lightSources = lights;
  
  //std::cout << __lightSources.at(0)->location.__x << std::endl;
  // LightSource  light;
  // light.name = "lamparica";
  // light.location = Vector(0,0,4);
  // light.vDirection = Vector(0,0,1);
  // light.energy = 1.0;
  // light.lampType = LAMP;
  // __lightSources.push_back(&light);
}

RayTracer::~RayTracer()
{}


Vector
RayTracer::Trace(Ray *ray)
{
  Vector Pos;
  __bvh.testIntersection(ray);
  
  if (ray->GetNearestObject() != NULL)
    Pos = ray->GetOrigin() + ray->GetDirection() * ray->GetNearestHitDistance();
  else
    Pos.Set(MAX_DISTANCE, MAX_DISTANCE, MAX_DISTANCE);
      
  return Pos;
}

Ray * 
RayTracer::castRay(LightSource * ls)
{
  Vector lampVNormal = ls->vDirection;
  Ray * rayToCast ;

  bool cast = false;

  while (!cast)
    {
      double x = ((double)rand() / (double)RAND_MAX);
      double y = ((double)rand() / (double)RAND_MAX);
      double z = ((double)rand() / (double)RAND_MAX);
      
      int die = rand() % 2;
      if (die == 1) x *= -1;
      die = rand() % 2;
      if (die == 1) y *= -1;
      die = rand() % 2;
      if (die == 1) z *= -1;
      
      Vector dir(x, y, z);

      if (dir.Length() <= 1.0) //Unit Sphere
        {
          if (ls->lampType == LAMP)
            {
	      rayToCast = new Ray();
              rayToCast->SetOrigin(ls->location);
              rayToCast->SetDirection(dir);
              cast = true;
            }
          else
            {
              if (lampVNormal.DotProduct(dir) >= 0.0f) //Rays unnecesary
                {
                  rayToCast->SetOrigin(ls->location);
                  rayToCast->SetDirection(dir);
                  cast = true;
                }
            }
        }
    }

  return rayToCast;
}

bool
RayTracer::RayTrace(bool indoorLightSources)
{
  
  std::vector<LightSource *>::iterator lamp;
  
  
  Vector pInt;
  int nonNullIntersectPoints = 0;
  int nonVisible = 0;
  int didntHit = 0;
  Triangle *hitSurface;
  std::map<std::string, int>::iterator it;
  Ray * ray;
  
  for (lamp = __lightSources.begin() ; lamp != __lightSources.end() ; lamp++)
    {
      
      for (unsigned int r = 0; r < RAYS_TO_TRACE ; r++)
        {
	  ray = castRay((*lamp));
          
	  pInt = Trace(ray);
          if (ray->GetNearestObject() != NULL)
            {
              hitSurface = (Triangle *)ray->GetNearestObject();
              //std::cout << hitSurface->__meshName << std::endl;
              it = __meshHits.find(hitSurface->__meshName);
              if (it != __meshHits.end())
                (*it).second += 1;
              else
                __meshHits.insert(std::pair<std::string, int>(hitSurface->__meshName, 1));            
	      nonNullIntersectPoints += 1;
              double whiteLevel = 0; //FIX
              double pDistToLam = 0; //FIX
	      
            }
          else
            didntHit += 1;
        }
    }
  //std::cout << ea << std::endl;
  return true;
}

std::map<std::string, int> 
RayTracer::getHits()
{
  return __meshHits;
}
