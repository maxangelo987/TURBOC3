//@ author Shubham Jain
#ifndef CAMERA_H
#define CAMERA_H

#include<vector.h>

class Camera
{public:
 double m;
 vector r,b,c,d;
 Camera(vector pos,vector x,vector y)
 {r=pos;
  b=x.unit();
  c=y.unit();
  m=1000;
 }
 void move(vector &a)
 {r=r+c*a.x+b*a.y+b.cross(c)*a.z;
 }
 void rotate(vector &a)
 {d=b.cross(c);
  b=b*cos(a.y)-d*sin(a.y);
  c=c*cos(a.x)-d*sin(a.x);
  d=b*cos(a.z)+c*sin(a.z);
  c=c*cos(a.z)-b*sin(a.z);
  b=d;
 }
 void rmove(vector &a)
 {d=c*r.dot(c);
  r=d+(r-d)*cos(a.y)+((r-d).cross(c))*sin(a.y);
  rotate(vector(0,-a.y,0));
  d=b*r.dot(b);
  r=d+(r-d)*cos(a.x)+((b).cross(r-d))*sin(a.x);
  rotate(vector(-a.x,0,0));
 }
 vector &position(vector &r1)
 {d.x=m*((r1-r).dot(c))/((r1-r).mod());
  d.y=m*((r1-r).dot(b))/((r1-r).mod());
  if(((r1-r).dot(b.cross(c)))>=0)
  d.z=(r1-r).mod();
  else d.z=-(r1-r).mod();
  return d;
 }
};
#endif