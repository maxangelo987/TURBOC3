//@auther Shubham Jain
#ifndef BOOLEAN_H
#define BOOLEAN_H

class bool16;
class bool
{int *p;
 int i;
 bool(int *ptr,int in)
 {p=ptr;
  i=in;
 }
 friend bool16;
public:
 int operator = (int a)
 { if(a==0) (*p)&=~(1<<i);
   if(a==1) (*p)|=(1<<i);
   return a;
 }
 int operator ==(int a)
 { if(a==0) return(((*p)&(1<<i))==0);
   else if(a==1) return(((*p)&(1<<i))!=0);
 }
 operator int()
 { if(((*p)&(1<<i))==0) return 0;
   else return 1;
 }
 int operator !()
 { return !int(*this);
 }
 int operator !=(int a)
 {return !((*this)==a);
 }
};

class bool16
{int a;
public:
 bool16()
 {a=0;
 }
 bool16(int b)
 {a=b;
 }
 bool16(bool16 & bl)
 {a=bl.a;
 }
 bool operator [](int i)
 {return bool(&a,i);
 }
};


#endif
