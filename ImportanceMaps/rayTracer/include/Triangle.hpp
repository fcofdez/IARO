#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "Primitive.hpp"
#include "Vector.hpp"

#include <algorithm>
#include <string>

class Triangle: public Primitive
{
public:
  
  Vector __p0, __p1, __p2;
  Vector __normal;

  std::string __meshName;
  
  Triangle(Vector p0, Vector p1, Vector p2, Vector Normal,std::string __meshName);
  bool testIntersection(Ray *ray);
  BBox boundingBox() const;
  Vector GetVNormal();
  virtual ~Triangle();
};


#endif /* _TRIANGLE_H_ */
