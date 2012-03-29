#ifndef _RAY_H_
#define _RAY_H_

#include "Vector.hpp"
#include <stdio.h>

#define MAXDISTANCE 999 

class Ray
{
public:
  Ray();
  Ray(Vector aOrigin, Vector aDirection);
  virtual ~Ray();
  
  inline void SetOrigin(Vector origin){__origin = origin;}
  inline Vector GetOrigin(){return __origin;}

  void SetDirection(Vector direction);
  inline Vector GetDirection(){return __direction;}
  
  inline Vector GetInvDirection(){return __invDirection;}
  
  inline void SetNearestHitDistance(double d){ __nearestHitDistance = d;}
  inline double GetNearestHitDistance(){return __nearestHitDistance;}

  int GetPosNeg(int index);
  
  inline void SetNearestObject(void * obj){ __nearestObject = obj; }
  inline void * GetNearestObject(){ return __nearestObject; }
  
private:
  Vector __origin;
  Vector __direction;
  Vector __invDirection;
  double __nearestHitDistance;
  void * __nearestObject;
  int __posneg[3]; //Represents if any axis is negative

};

#endif /* _RAY_H_ */
