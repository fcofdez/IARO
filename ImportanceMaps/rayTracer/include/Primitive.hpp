#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_

#include "Ray.hpp"
#include "BBox.hpp"


enum PrimitiveType
  {
    TRIANGLE,
    BVH
  };

class Primitive
{
public:
  PrimitiveType type;
  virtual bool testIntersection(Ray *ray){return false;};
  virtual BBox boundingBox() const = 0;
};


#endif /* _PRIMITIVE_H_ */
