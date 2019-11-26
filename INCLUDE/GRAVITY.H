//@ author Shubham Jain
#ifndef GRAVITY_H
#define GRAVITY_H

#include<vector.h>
#include<math.h>
double angle(double x,double y)
{ if(x>-0.00001&&x<0.00001)
  {if(y>0)
   return M_PI/2;
   else
   return -M_PI/2;
  }
  else
  {if(x>0)
   return atan(y/x);
   else
   return atan(y/x)+M_PI;
  }
}
double acosh(double a)
{return log(a+sqrt(a*a-1));
}
class System
{public:
 double M,GM,L,E,vt,vn,A,B,a,ae,r1,r2,t0,T,rad,sign;
 int flag;

 double f1(double r)
 {double R=fabs(r-r1);
  return((2.*r1*sqrt(R)+2./3*sqrt(R)*sqrt(R)*sqrt(R))/sqrt(2.*A));
 }
 double f2(double r)
 {double R=(a-r)/ae;
  if(R>=1)R=1;
  if(R<=-1)R=-1;
  return((a*acos(R)-sqrt(fabs(ae*ae-(r-a)*(r-a))))/sqrt(-2*E));
 }
 double f3(double r)
 {double R=(a+r)/ae;
  if(R<1)R=1;
  return((sqrt(fabs((r+a)*(r+a)-ae*ae))-a*acosh(R))/sqrt(2*E));
 }
 double f(double r)
 {if(flag==1)return f1(r);
  else if(flag==2)return f2(r);
  else return f3(r);
 }
 System(double m,double r0,double vn0,double vt0);

 double pos(double t);

 vector posxy(double r);

 vector position(double t);

};
 System::System(double m,double r0,double vn0,double vt0)
 {M=m;GM=M;vt=vt0;vn=vn0;
  L=vt*r0;
  E=1/2.*vn*vn+1/2.*L*L/(r0*r0)-GM/r0;
  if(E>-0.1&&E<0.1)
  {
   flag=1;
   A=GM;
   B=L*L/2.;
   r1=B/A;
   t0=(vn>0)?f1(r0):-f1(r0);
  }
  else if(E<=-0.1)
  {A=GM/(-E);
   B=L*L/(-2.*E);
   if((A*A/4.-B)>-0.1&&(A*A/4.-B)<0.1)
   {flag=3;
    rad=r0;
   }
   else
   {flag=2;
    a=A/2.;
    ae=sqrt(A*A/4.-B);
    r1=a-ae;
    r2=a+ae;
    T=f2(r2);
    t0=(vn>0)?f2(r0):2*T-f2(r0);
   }
  }
  else if(E>=0.1)
  {flag=4;
   A=GM/E;
   B=L*L/(2.*E);
   a=A/2.;
   ae=sqrt(A*A/4.+B);
   r1=ae-a;
   t0=(vn>0)?f3(r0):-f3(r0);
  }
 }
 double System::pos(double t)
 {double t1,t2,x1=r1,x2,time;
  if(flag==1){x2=1000;time=fabs(t+t0);if((t+t0)>0)sign=1;else sign=-1;}
  else if(flag==4){x2=1000;time=fabs(t+t0);if((t+t0)>0)sign=1;else sign=-1;}
  else if(flag==3)return rad;
  else if(flag==2)
  {x2=r2;
   int k=(int)((t+t0)/T);
   if(k%2==0)
   {time=(t+t0)-k*T;sign=1;}
   else
   {time=(k+1)*T-(t+t0); sign=-1;}
  }
  t1=f(x1);
  for(double i=x1;i<x2;i+=0.01)
  { t2=f(i);
    if((t1<=time&&t2>=time)||(t1>=time&&t2<=time))
    break;
    t1=t2;
  }
  return i;
 }
 vector System::posxy(double r)
 {vector v;
  if(flag==1)
  {v.x=2*r1-r;
   v.y=2*sqrt(fabs(r*r1-r1*r1))*sign;
  }
  else if(flag==2||flag==4)
  {v.x=(B-a*r)/ae;
   v.y=sqrt(fabs(r*r-v.x*v.x))*sign;
  }
  return v;
 }
 vector System::position(double t)
 {vector v;
  double ang,theta,dist;
  if(flag!=3)
  {v=posxy(pos(0));
   ang=angle(v.x,v.y);
   v=posxy(pos(t));
   theta=angle(v.x,v.y)-ang;
   dist=sqrt(v.x*v.x+v.y*v.y);
   v.x=dist*cos(theta);
   v.y=dist*sin(theta);
   if(vt<0)v.y*=-1;
  }
  else
  {v.x=rad*cos(vt*t/rad);
   v.y=rad*sin(vt*t/rad);
  }
  return v;
 }
/************************************************************************/
class Two_Mass_System
{double m1,m2,d0,theta;
 vector r1,r2,v1,v2,rc,vc;
 public:
 System *s;
 Two_Mass_System(double mass1,double mass2,vector pos1,vector pos2
			  ,vector vel1,vector vel2)
 {m1=mass1;m2=mass2;r1=pos1;r2=pos2;v1=vel1;v2=vel2;
  rc=(r1*m1+r2*m2)/(m1+m2);
  vc=(v1*m1+v2*m2)/(m1+m2);
  d0=(r1-r2).mod();
  theta=angle((r2-r1).x,(r2-r1).y);
  double vx=((v2-v1).unit()).dot((r2-r1).unit())*(v2-v1).mod();
  vector c=(v2-v1)-(v2-v1).comp(r2-r1) ;
  double vy=((r2-r1).cross(c).z>=0)?c.mod():-c.mod();
  s=new System(m1+m2,d0,vx,vy);
 }
 void position_wrt_cm(double t,vector &a1,vector &a2)
 {vector r=s->position(t);
  vector pc=(r*m2)/(m1+m2);
  a1=(pc*(-1)).rot(vector(0,0,theta));
  a2=(r-pc).rot(vector(0,0,theta));
 }
 void position(double t,vector &a1,vector &a2)
 {vector b1,b2;
  position_wrt_cm(t,b1,b2);
  a1=rc+vc*t+b1;
  a2=rc+vc*t+b2;
 }
};
#endif