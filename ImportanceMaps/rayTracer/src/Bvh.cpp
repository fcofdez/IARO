#include "Bvh.hpp"
#include <iostream>

Bvh::Bvh()
{
}

Bvh::~Bvh()
{
}

Bvh::Bvh(std::vector<Triangle *>& surfaces)
{
  int surfacesNum = surfaces.size();
  if (surfaces.size() == 1) *this = Bvh(surfaces[0], surfaces[0]);
  if (surfaces.size() == 2) *this = Bvh(surfaces[0], surfaces[1]);
  
  __bbox = surfaces[0]->boundingBox();
  
  for (int i = 1; i < surfacesNum; i++)
    __bbox = surround(__bbox, surfaces[i]->boundingBox());
  
  Vector pivot = (__bbox.getMax() + __bbox.getMin()) / 2.0;

  int midPoint = qsplit(surfaces, surfacesNum, pivot.__x, 0);

  __left = buildBranch(surfaces, midPoint, 1);
  __right = buildBranch(std::vector<Triangle *>(surfaces.begin()+midPoint, surfaces.end()), surfacesNum - midPoint, 1);

}


Bvh::Bvh(Triangle* p1, Triangle* p2)
{
  __left = p1;
  __right = p2;
  __bbox = surround(p1->boundingBox(), p2->boundingBox());
}

Bvh::Bvh(Triangle* p1, Triangle* p2, BBox& bbox)
{
  __left = p1;
  __right = p2;
  __bbox = bbox;
}

bool
Bvh::testIntersection(Ray * ray)
{
  
  if (!(__bbox.rayIntersect(ray))) return false;
  
  bool rightHit = false;
  bool leftHit = false;
  
  rightHit = __right->testIntersection(ray);
  leftHit = __left->testIntersection(ray);
  
  

  return (rightHit || leftHit);
}

Primitive*
Bvh::buildBranch(std::vector<Triangle *> surfaces, int surfacesNumber, int axis)
{
  if (surfacesNumber == 1) return surfaces[0];
  if (surfacesNumber == 2) return new Bvh(surfaces[0], surfaces[1]);

  BBox box = surfaces[0]->boundingBox();
  
  for (unsigned int i = 1; i < surfacesNumber; i++)
    box = surround(box, surfaces[i]->boundingBox());
  
  Vector pivot = (box.getMax() + box.getMin()) / 2.0;

  int midPoint = -1;

  switch(axis)
    {
    case 0:
      midPoint = qsplit(surfaces, surfacesNumber, pivot.__x, 0);
      break;
    case 1:
      midPoint = qsplit(surfaces, surfacesNumber, pivot.__y, 1);
      break;
    case 2:
      midPoint = qsplit(surfaces, surfacesNumber, pivot.__z, 2);
      break;
    default:
      break;    
    }  
    
  Primitive* left = buildBranch(surfaces, midPoint, (axis + 1) % 3);
  Primitive* right = buildBranch(std::vector<Triangle *>(surfaces.begin()+midPoint, surfaces.end()), surfacesNumber - midPoint, (axis + 1) % 3);
  
  return new Bvh(left, right, box);
}

BBox
Bvh::boundingBox() const
{
  return __bbox;
}

int
Bvh::qsplit(std::vector<Triangle *> list, int size, float pivotVal, int axis)
{
  BBox bbox;
  double centroid;
  int ret_val = 0;

  for (int i = 0; i < size; i++) {
    bbox = list[i]->boundingBox();
    switch (axis) {
    case 0:
      centroid = ((bbox.getMin()).__x + (bbox.getMax()).__x) / 2.0f;
      break;
    case 1:
      centroid = ((bbox.getMin()).__y + (bbox.getMax()).__y) / 2.0f;
      break;
    case 2:
      centroid = ((bbox.getMin()).__z + (bbox.getMax()).__z) / 2.0f;
      break;
    default:
      break;
    }

    if (centroid < pivotVal) {
      Triangle *temp = list[i];
      list[i] = list[ret_val];
      list[ret_val] = temp;
      ret_val++;
    }
  }
  if (ret_val == 0 || ret_val == size) ret_val = size / 2;

  return ret_val;


}
   
