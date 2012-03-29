#ifndef _BBOX_H_
#define _BBOX_H_

#define MIN 0
#define MAX 1

#include <algorithm>
#include "Vector.hpp"
#include "Ray.hpp"



class BBox
{
public:
  BBox();
  BBox(Vector min,Vector max);

  Vector getMin() const;
  Vector getMax() const;
  bool rayIntersect(Ray *r) const;

  virtual ~BBox();

private:
  Vector pp[2];

};

BBox surround(const BBox& b1, const BBox& b2);


#endif /* _BBOX_H_ */
