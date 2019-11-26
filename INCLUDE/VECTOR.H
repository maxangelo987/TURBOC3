//@ author Shubham Jain
#ifndef VECTOR_H
#define VECTOR_H

#include<math.h>

class vector
{public:
double x,y,z;
vector(double i=0,double j=0,double k=0)
{x=i;y=j;z=k;
}
void operator()(double i,double j,double k)
{x=i;y=j;z=k;
}
vector operator +(vector &a)
{vector b;
b.x=x+a.x;
b.y=y+a.y;
b.z=z+a.z;
return b;
}
vector operator -(vector &a)
{vector b;
b.x=x-a.x;
b.y=y-a.y;
b.z=z-a.z;
return b;
}
vector operator *(double a)
{vector b;
b.x=x*a;
b.y=y*a;
b.z=z*a;
return b;
}
vector operator -()
{vector b;
b.x=-x;
b.y=-y;
b.z=-z;
return b;
}
vector operator /(double a)
{vector b;
if(a==0)
{b.x=0;b.y=0;b.z=0;}
else
{b.x=x/a;
 b.y=y/a;
 b.z=z/a;
}
return b;
}
double  dot(vector &a)
{return(x*a.x+y*a.y+z*a.z);
}
vector cross(vector &a)
{vector b;
b.x=y*a.z-z*a.y;
b.y=z*a.x-x*a.z;
b.z=x*a.y-y*a.x;
return b;
}
double mod()
{return sqrt(x*x+y*y+z*z);
}
int operator ==(vector &a)
{return((x==a.x)&&(y==a.y)&&(z==a.z));
}
vector unit()
{return (*this)/mod();
}
vector comp(vector &a)
{return a*dot(a)/(a.mod()*a.mod());
}
vector rot(vector &a)
{vector b=comp(a);
 vector c=(*this)-b;
 c=c*cos(a.mod())+(a.unit()).cross(c)*sin(a.mod());
 b=b+c;
 return b;
}
#ifdef __IOSTREAM_H
friend ostream & operator <<(ostream &o,vector &v);
#endif
};
vector operator *(double,vector&);
vector operator *(double d,vector& a)
{return a*d;
}
#ifdef __IOSTREAM_H
ostream & operator <<(ostream &o,vector &v)
{return o<<v.x<<"i "<<v.y<<"j "<<v.z<<"k ";
}
#endif
#endif