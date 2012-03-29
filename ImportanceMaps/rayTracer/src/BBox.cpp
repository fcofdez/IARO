#include "BBox.hpp"
#include <iostream>

BBox::BBox()
{
}

BBox::BBox(Vector min,  Vector max)
{
  pp[MIN] = min;
  pp[MAX] = max;
}

BBox::~BBox()
{}

Vector
BBox::getMin() const 
{
return pp[MIN];
}

Vector
BBox::getMax() const 
{
return pp[MAX];
}


bool
BBox::rayIntersect(Ray * r)const 
{
  float minInterval = -99999.9999f;
  float maxInterval = 99999.9999f;
  
  int posneg = r->GetPosNeg(0);
  float t0 = (pp[posneg].__x - r->GetOrigin().__x) * r->GetInvDirection().__x;
  float t1 = (pp[1 - posneg].__x - r->GetOrigin().__x) * r->GetInvDirection().__x;
  if (t0 > minInterval) minInterval = t0;
  if (t1 < maxInterval) maxInterval = t1;
  if (minInterval > maxInterval) return false;


  posneg = r->GetPosNeg(1);
  t0 = (pp[posneg].__y - r->GetOrigin().__y) * r->GetInvDirection().__y;
  t1 = (pp[1 - posneg].__y - r->GetOrigin().__y) * r->GetInvDirection().__y;
  if (t0 > minInterval) minInterval = t0;
  if (t1 < maxInterval) maxInterval = t1;
  if (minInterval > maxInterval) return false;

  posneg = r->GetPosNeg(2);
  t0 = (pp[posneg].__z - r->GetOrigin().__z) * r->GetInvDirection().__z;
  t1 = (pp[1 - posneg].__z - r->GetOrigin().__z) * r->GetInvDirection().__z;
  if (t0 > minInterval) minInterval = t0;
  if (t1 < maxInterval) maxInterval = t1;
  return (minInterval <= maxInterval);
}

BBox
surround(const BBox& b1, const BBox& b2)
{
  
  return BBox(Vector(std::min(b1.getMin().__x, b2.getMin().__x),
                     std::min(b1.getMin().__y, b2.getMin().__y),
                     std::min(b1.getMin().__z, b2.getMin().__z)),
              Vector(std::max(b1.getMax().__x, b2.getMax().__x),
                     std::max(b1.getMax().__y, b2.getMax().__y),
                     std::max(b1.getMax().__z, b2.getMax().__z)));
}

