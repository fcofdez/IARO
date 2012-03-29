#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <math.h>

#define MAX_DISTANCE 99999

class Vector
{
public:
  Vector();
  Vector(double ax, double ay, double az);
  virtual ~Vector();
 
  void Set(double ax, double ay, double az);
  double DotProduct(Vector b);
  double DotProduct(double ax, double ay, double az);
  double DotProduct(double value);
  double DotProduct(Vector a, Vector b);
  Vector CrossProduct(Vector a);
  Vector CrossProduct(double ax, double ay, double az);
  Vector CrossProduct(Vector a, Vector b);
  inline void Normalize(){double len = Length(); __x /= len; __y /= len; __z /= len;};
  inline double Length(){return sqrt(pow(__x,2)+pow(__y,2)+pow(__z,2));};
  
  
  void operator=(Vector a);
  Vector operator-(Vector a);
  Vector operator-();
  Vector operator+(double a);
  Vector operator+(Vector a);
  Vector operator*(Vector a);
  Vector operator*(double a);
  Vector operator/(double a);
  void operator/=(double a);
  void operator*=(double a);
  void operator+=(Vector a);
  bool operator==(Vector a);
  bool operator!=(Vector a);


  double __x , __y , __z; 

};


#endif /* _VECTOR_H_ */
