#ifndef _BVH_H_
#define _BVH_H_
#include <vector>
#include "Triangle.hpp"
#include "Primitive.hpp"
#include "BBox.hpp"

class Bvh: public Primitive
{
public:
  Bvh();
  //Bvh(std::vecto** surfaces, int num_surfaces);
  Bvh(Triangle * prim1, Triangle* prim2);
  Bvh(Triangle* prim1, Triangle* prim2, BBox&);
  Bvh(std::vector<Triangle *> & objects);
  virtual ~Bvh();
  bool testIntersection(Ray* ray);
  BBox boundingBox() const;
  Primitive * buildBranch(std::vector<Triangle *> surfaces, int numSurfaces, int axis = 0);
  
private:
  BBox __bbox;
  Primitive * __left;
  Primitive * __right;
  int qsplit(std::vector<Triangle *> list, int size, float pivotVal, int axis);
};
 
#endif /* _BVH_H_ */
