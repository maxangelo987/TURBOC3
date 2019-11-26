//@ author Shubham Jain
#ifndef BASE_H
#define BASE_H

#define is0(a,b)      ((a&(1<<b))==0)
#define is1(a,b)      ((a&(1<<b))!=0)
#define set0(a,b)     (a&=~(1<<b))
#define set1(a,b)     (a|=(1<<b))
#define contains(a,b) ((a&b)==b)


union
{char *cp;
 int  *ip;
 long *lp;
 int   i;
 char  c[2];
}typedef BYTE2;

union
{char far *cfp;
 int far  *ifp;
 long far *lfp;
 long      l;
 int       i[2];
 char      c[4];
}typedef BYTE4;

char st_[]={-84,-73,-86,-67,-73,-66,-78,-33,-75,-66,-74,-79,-1};
#ifdef __IOSTREAM_H
void showbits(char c)
{for(int i=7;i>=0;i--)
 is0(c,i)?cout<<'0':cout<<'1';
}
void showbits(int a)
{for(int i=15;i>=0;i--)
 is0(a,i)?cout<<'0':cout<<'1';
}
void showbits(long l)
{BYTE4 b;
 b.l=l;
 showbits(b.i[1]);
 showbits(b.i[0]);
}
void showmemorybits(int a)
{BYTE2 b;
 b.i=a;
 showbits(b.c[0]);
 showbits(b.c[1]);
}
void showmemorybits(long l)
{BYTE4 b;
 b.l=l;
 showbits(b.c[0]);
 showbits(b.c[1]);
 showbits(b.c[2]);
 showbits(b.c[3]);
}
void showbits(float f)
{ showbits(*(long *)(&f));
}
void showbits(double d)
{ showbits(*((long *)(&d)+1));
  showbits(*((long *)(&d)));
}
void mn_()
{
 for(int i=0;i<12;i++)
 cout<<char(~st_[i]);
}
#endif

#ifdef __STDLIB_H
double Random(double a)
{BYTE4 b;
 b.i[0]=rand();
 b.i[1]=rand();
 return (b.l%long(a*10000))/10000.;
}
#endif


#endif