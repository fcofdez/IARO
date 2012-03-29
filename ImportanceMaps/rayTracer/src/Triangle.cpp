#include "Triangle.hpp"
#include <iostream>

Triangle::Triangle(Vector p0, Vector p1, Vector p2, Vector normal, std::string meshName)
{
  __p0 = p0; 
  __p1 = p1;
  __p2 = p2;
  __normal = normal;
  __meshName = meshName;
  type = TRIANGLE;
  
}

Triangle::~Triangle(){}
 
bool Triangle::testIntersection(Ray *ray)
{
  double A = __p0.__x - __p1.__x; double B = __p0.__y - __p1.__y; double C = __p0.__z - __p1.__z;
  double D = __p0.__x - __p2.__x; double E = __p0.__y - __p2.__y; double F = __p0.__z - __p2.__z;
  double G = ray->GetDirection().__x;
  double H = ray->GetDirection().__y;
  double I = ray->GetDirection().__z;
  
  double J = __p0.__x - ray->GetOrigin().__x;
  double K = __p0.__y - ray->GetOrigin().__y;
  double L = __p0.__z - ray->GetOrigin().__z;
  
  double EIHF = E*I-H*F; double GFDI = G*F-D*I; double DHEG = D*H-E*G;
  double AKJB = A*K-J*B; double JCAL = J*C-A*L; double BLKC = B*L-K*C;
  
  double denom = (A*EIHF + B*GFDI + C*DHEG);
  
  double beta = (J*EIHF + K*GFDI + L*DHEG) / denom;
  double teta = (I*AKJB + H*JCAL + G*BLKC) / denom;
  double inter = -(F*AKJB + E*JCAL + D*BLKC) / denom;
  
  if ((beta > 0.0 && teta > 0.0) && (beta + teta < 1.0) &&
      (inter > 0.0 && ray->GetNearestHitDistance() > inter)) {
    ray->SetNearestHitDistance(inter);
    ray->SetNearestObject(new Triangle(__p0, __p1, __p2, __normal, __meshName));
    return true;	
  } 
  else 
    return false; 
}

BBox Triangle::boundingBox() const
{
  const float epsilon = 0.00001f;
  Vector min;
  Vector max;
  

  min.__x = std::min(__p0.__x , __p1.__x);
  min.__y = std::min(__p0.__y , __p1.__y);
  min.__z = std::min(__p0.__z , __p1.__z);

  min.__x = std::min(__p2.__x , min.__x);
  min.__y = std::min(__p2.__y , min.__y);
  min.__z = std::min(__p2.__z , min.__z);

  max.__x = std::max(__p0.__x , __p1.__x);
  max.__y = std::max(__p0.__y , __p1.__y);
  max.__z = std::max(__p0.__z , __p1.__z);

  max.__x = std::max(__p2.__x , max.__x);
  max.__y = std::max(__p2.__y , max.__y);
  max.__z = std::max(__p2.__z , max.__z);

  min.__x -= epsilon;
  min.__y -= epsilon;
  min.__z -= epsilon;

  max.__x += epsilon;
  max.__y += epsilon;
  max.__z += epsilon;

  return BBox(min, max);
}

Vector Triangle::GetVNormal()
{
  return __normal;
}



