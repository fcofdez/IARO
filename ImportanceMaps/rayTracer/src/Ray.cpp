#include "Ray.hpp"
 
Ray::Ray()
{
  __nearestHitDistance = MAXDISTANCE;
  __nearestObject = NULL;
}

Ray::~Ray(){}

Ray::Ray(Vector origin, Vector direction)
{
  __origin = origin;
  __direction = direction;
  __nearestHitDistance = MAXDISTANCE;
  __nearestObject = NULL;
}

void
Ray::SetDirection(Vector direction)
{
  __direction = direction;
  __direction.Normalize();
  __invDirection = Vector(1.0/direction.__x, 1.0/direction.__y, 1.0/direction.__z);

  __posneg[0] = (__direction.__x > 0 ? 0 : 1);
  __posneg[1] = (__direction.__y > 0 ? 0 : 1);
  __posneg[2] = (__direction.__z > 0 ? 0 : 1);
}

int
Ray::GetPosNeg(int index)
{
  if (index < 0 || index > 2)
    return -1;
  
  return __posneg[index];
}


