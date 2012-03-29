#ifndef _LIGHTSOURCE_H_
#define _LIGHTSOURCE_H_
#include <string>

 enum lightType
  {
    LAMP,
    OTHER
  };


typedef struct LightSource
{
  bool internal;
  std::string name;
  lightType lampType;
  Vector location;
  Vector vDirection;
  double energy;
  
  LightSource(std::string _name,Vector loc, Vector vDir, double ener)
  {
    name = _name;
    location = loc;
    vDirection = vDir;
    energy = ener;
    lampType = LAMP;
  }

} LightSource;
 

#endif /* _LIGHTSOURCE_H_ */
 
