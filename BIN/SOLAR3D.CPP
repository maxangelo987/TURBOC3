//@ author Shubham Jain
#include<stdlib.h>
#include<iostream.h>
#include<conio.h>
#include<base.h>
#include<graphrgb.h>
#include<camera.h>

Camera cam(vector(0,0,-400),vector(0,1,0),vector(-1,0,0));
class planet
{public:
 double radius;
 double distance;
 Color c1,c2;
 double w;
 vector v;
 int t;
 planet(double r,double d,double a,Color col1,Color col2)
 {radius=r;
  distance=d;
  w=a;
  c1=col1;
  c2=col2;
  v=vector(d,0,0);
  t=rand()/3.7;
 }
};
planet* pl[9];
void planet8();
void plot();
void showtext();
double Star[50][2];
Source sc;
Graphics g(sc);

void main()
{showtext();
 if(g.init()==0)
 {cout<<"\nComputer doesn't support the SVGA mode : 1024x768 RGB(32Bit) under DOS Mode";
  exit(0);
 }
 int ch=0;
 randomize();
 planet8();
 g.setflipping();
 while(ch!=27)
 {
  g.clearscreen();
  plot();
  g.next();
  delay(15);
  if(kbhit())
  {ch=getch();
   if(ch==0)
   {ch=getch();
    if(ch==72)cam.rmove(vector(0,0.02,0));
    else if(ch==80)cam.rmove(vector(0,-0.02,0));
    else if(ch==75)cam.rmove(vector(-0.02,0,0));
    else if(ch==77)cam.rmove(vector(0.02,0,0));
   }
   else
   {
    while(kbhit())ch=getch();
	 if(ch=='a'||ch=='A')cam.move(vector(0,0,1));
    else if(ch=='z'||ch=='Z')cam.move(vector(0,0,-1));
    else if(ch=='x'||ch=='X')cam.rotate(vector(0,-0.01,0));
    else if(ch=='e'||ch=='E')cam.rotate(vector(0,0.01,0));
    else if(ch=='d'||ch=='D')cam.rotate(vector(0.01,0,0));
    else if(ch=='s'||ch=='S')cam.rotate(vector(-0.01,0,0));
   }
  }
 }
 g.close();
}
void planet8()
{pl[0]=new planet(1000,30,2.35,Color(5,10,0),Color(250*0.5,245*0.3,0));
 pl[1]=new planet(1500,50,1.53,Color(15,10,10),Color(240,245*0.2,245*0.2));
 pl[2]=new planet(2000,80,1.01,Color(5,5,15),Color(0,250*0.2,240));
 pl[3]=new planet(1500,95,0.71,Color(15,5,5),Color(240,250*0.2,0));
 pl[4]=new planet(6000,130,0.32,Color(15,10,5),Color(240,250*0.6,0));
 pl[5]=new planet(5000,165,0.23,Color(20,10,10),Color(235,245*0.3,245*0.1));
 pl[6]=new planet(3500,225,0.15,Color(10,20,10),Color(245*0.2,235,245*0.2));
 pl[7]=new planet(3000,300,0.05,Color(10,10,30),Color(0,235,225));
 pl[8]=new planet(15000,0,0,Color(255,255,50),Color(0,0,0));
 for(int i=0;i<50;i++)
 {Star[i][0]=Random(360);
  Star[i][1]=M_PI/2-acos(1-Random(2));
 }
}
vector r[9],v1,v2,bx,by,bz,c;
planet *p;
double t=0;
int d[9],t1,t2;
void plot()
{for(int i=0;i<8;i++)
 {p=pl[i];
  p->v.x=p->distance*cos(p->w*t+p->t);
  p->v.y=p->distance*sin(p->w*t+p->t);
 }
 t+=0.01;

 for(i=0;i<9;i++)
 {r[i]=cam.position(pl[i]->v);
  r[i].x=r[i].x/Ratio;
 }
 t1=0;

 for(i=0;i<8;i++)
  if(r[t1].z<r[i+1].z)
  t1=i+1;
 d[0]=t1;
 for(int j=1;j<9;j++)
 {for(i=0;i<9;i++)
   if(i!=t1&&r[i].z<r[t1].z)
   {t2=i;
    break;
   }
  for(i=0;i<9;i++)
   if(i!=t1&&r[i].z<r[t1].z&&r[i].z>r[t2].z)
   t2=i;
  t1=t2;
  d[j]=t2;
 }
 for(i=0;i<50;i++)
 {v1=vector(1000000*cos(Star[i][1])*cos(Star[i][0]),
	    1000000*sin(Star[i][1]),
	    1000000*cos(Star[i][1])*sin(Star[i][0]));
  v2=cam.position(v1);
  if(v2.z>0)
   g.putpixel(v2.x+512,384-v2.y,Color::RGB(255,255,255));
 }
 bx=cam.c.unit();
 by=cam.b.unit();
 bz=(bx.cross(by)).unit();
 for(i=0;i<9&&r[d[i]].z>0;i++)
 { c.x=bx.dot(pl[d[i]]->v);
   c.y=by.dot(pl[d[i]]->v);
   c.z=bz.dot(pl[d[i]]->v);
   if(d[i]==8)g.fillcircle(vector(r[d[i]].x,r[d[i]].y),int(pl[d[i]]->radius/r[d[i]].z),pl[d[i]]->c1);
   else g.circle3d(vector(r[d[i]].x,r[d[i]].y),int(pl[d[i]]->radius/r[d[i]].z),c,pl[d[i]]->c1,pl[d[i]]->c2);
 }
}
void showtext()
{cout<<"3d Solar System by ";
 mn_();
 cout<<endl;
 cout<<"Use up,down,left and right arrow keys and A,Z,S,D,E,X keys for move Camera\n";
 cout<<"Press esc to exit\n";
 cout<<"Press any key to continue\n";
 getch();
}
