#include "Vector.hpp"

Vector::Vector()
{
  __x = MAX_DISTANCE;
  __y = MAX_DISTANCE;
  __z = MAX_DISTANCE; 
}

Vector::Vector(double x, double y, double z)
{
  __x = x;
  __y = y;
  __z = z;
}

Vector::~Vector(){}

void
Vector::Set(double x, double y, double z)
{
  __x = x;
  __y = y;
  __z = z;
}

double
Vector::DotProduct(Vector a)
{
  return (a.__x*__x + a.__y*__y + a.__z*__z);
}

double
Vector::DotProduct(double x, double y, double z)
{
  return (__x*x + __y*y + __z*z);
}

double
Vector::DotProduct(double a)
{
  return (a*__x + a*__y + a*__z);
}

double 
Vector::DotProduct(Vector a, Vector b)
{
  return (a.__x*b.__x + a.__y*b.__y + a.__z*b.__z);
}

Vector
Vector::CrossProduct(Vector a)
{
  Vector result;
  
  result.__x = __y*a.__z - __z*a.__y;
  result.__y = __z*a.__x - __x*a.__z;
  result.__z = __x*a.__y - __y*a.__x;

  return result;
}

Vector
Vector::CrossProduct(double ax, double ay, double az)
{
  return CrossProduct(Vector(ax, ay, az));
}

Vector 
Vector::CrossProduct(Vector a, Vector b)
{
  return a.CrossProduct(b);
}

void Vector::operator=(Vector a)
{
	__x=a.__x;
	__y=a.__y;
	__z=a.__z;
}

Vector Vector::operator-(Vector a)
{
	Vector b(__x-a.__x, __y-a.__y, __z-a.__z);
	return b;
}

Vector Vector::operator-()
{
	Vector b(-__x, -__y, -__z);
	return b;
}

Vector Vector::operator+(Vector a)
{
	Vector b(__x+a.__x, __y+a.__y, __z+a.__z);
	return b;
}

Vector Vector::operator+(double a)
{
	Vector b(__x+a, __y+a, __z+a);
	return b;
}

Vector Vector::operator/(double a)
{
  Vector v(__x / a, __y / a, __z / a);
  return v;
}

void Vector::operator/=(double a)
{
	__x/=a;
	__y/=a;
	__z/=a;
}

void Vector::operator*=(double a)
{
	__x*=a;
	__y*=a;
	__z*=a;
}

Vector Vector::operator*(Vector a)
{
	Vector b(__x*a.__x, __y*a.__y, __z*a.__z);
	return b;
}

Vector Vector::operator*(double a)
{
	Vector b(__x*a, __y*a, __z*a);
	return b;
}

void Vector::operator+=(Vector a)
{
	__x += a.__x;
	__y += a.__y;
	__z += a.__z;
}

bool Vector::operator==(Vector a)
{
  return ((__x == a.__x) && (__y == a.__y) && (__z == a.__z));
}

bool Vector::operator!=(Vector a)
{
  return !((__x == a.__x) && (__y == a.__y) && (__z == a.__z));
}
