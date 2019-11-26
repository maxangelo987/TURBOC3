//@ author Shubham Jain
#include<stdlib.h>
#include<iostream.h>
#include<conio.h>
#include<camera.h>
#include<base.h>
#include<graph.h>
Camera cam(vector(0,0,-400),vector(0,1,0),vector(-1,0,0));
class planet
{public:
 double radius;
 double distance;
 int color;
 double w;
 vector v;
 int t;
 planet(double r,double d,double a,int c)
 {radius=r;
  distance=d;
  w=a;
  color=c;
  v=vector(d,0,0);
  t=rand()/3.7;
 }
};
planet* pl[9];
void planet8();
void plot();
void showtext();
double Star[50][2];
void main()
{showtext();
 int gd=VGA,gm=VGAMED;
 initgraph(&gd,&gm,0);
 cam.m=500;
 randomize();
 int ch=0;
 planet8();
 while(ch!=27)
 {active
  cleardevice();
  plot();
  visual
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
   else if(ch=='a'||ch=='A')cam.move(vector(0,0,1));
   else if(ch=='z'||ch=='Z')cam.move(vector(0,0,-1));
   else if(ch=='x'||ch=='X')cam.rotate(vector(0,-0.01,0));
   else if(ch=='e'||ch=='E')cam.rotate(vector(0,0.01,0));
   else if(ch=='d'||ch=='D')cam.rotate(vector(0.01,0,0));
   else if(ch=='s'||ch=='S')cam.rotate(vector(-0.01,0,0));
  }
 }
 closegraph();
 restorecrtmode();
}
void planet8()
{pl[0]=new planet(200,30,2.35,6);
 pl[1]=new planet(750,50,1.53,12);
 pl[2]=new planet(1000,80,1.01,1);
 pl[3]=new planet(500,110,0.71,4);
 pl[4]=new planet(3000,175,0.52,6);
 pl[5]=new planet(2500,225,0.33,13);
 pl[6]=new planet(1500,280,0.18,10);
 pl[7]=new planet(1400,340,0.13,11);
 pl[8]=new planet(10000,0.1,0,14);
 for(int i=0;i<50;i++)
 {Star[i][0]=Random(360);
  Star[i][1]=M_PI/2-acos(1-Random(2));
 }
}
vector r[9],v1,v2;
planet *p;
double t=0;
int d[9],t1,t2;
void plot()
{for(int i=0;i<8;i++)
 {p=pl[i];
  p->v.x=p->distance*cos(p->w*t+p->t);
  p->v.y=p->distance*sin(p->w*t+p->t);
 }
 t+=0.002;

 for(i=0;i<9;i++)
 {r[i]=cam.position(pl[i]->v);
  r[i].x+=320;r[i].y=175-r[i].y;
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
 {v1=vector(10000*cos(Star[i][1])*cos(Star[i][0]),
	    10000*sin(Star[i][1]),
	    10000*cos(Star[i][1])*sin(Star[i][0]));
  v2=cam.position(v1);
  if(v2.z>0)
   putpixel(v2.x+320,175-v2.y,15);
 }
 for(i=0;i<9&&r[d[i]].z>0;i++)
 { setcolor(pl[d[i]]->color);
   setfillstyle(SOLID_FILL,pl[d[i]]->color);
   fillellipse(r[d[i]].x,r[d[i]].y,pl[d[i]]->radius/r[d[i]].z,(pl[d[i]]->radius/r[d[i]].z)*Ratio);
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
