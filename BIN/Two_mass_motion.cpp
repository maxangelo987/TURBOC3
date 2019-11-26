//@ author Shubham Jain

#include<graph.h>
#include<mouse.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<gravity.h>

#define COL1  13
#define COL2  14
#define BGCOL 6
#define ACOL  4
int charheight;
/*------------------------------------------------------------------------*/
class event
{public:
 int b,x,y,key;
 char ch;
};
/*------------------------------------------------------------------------*/
void status(char *str)
 {setcolor(0);
  outtextxy(2,350-charheight-3,str);
 }
/*------------------------------------------------------------------------*/
class editor
{char *str;
 int x,y,h,w,w1,num,no,color;
public:
 int flag;
 char *st;
 editor(char* string,int x1,int y1,int number,int col);
 void handle(event me[2]);
};
 editor::editor(char* string,int x1,int y1,int number,int col)
 {str=string; x=x1;y=y1;num=number;no=0;flag=0;
  h=charheight+4;w=639-x1-2;
  w1=textwidth(str); st=new char[num+1];st[0]=0;
  color=col;
 }
 void editor::handle(event me[2])
 { if(is1(flag,0)&&is1(me[1].b,0))
   { if(me[1].x>=x&&me[1].x<(x+w)&&me[1].y>=y&&me[1].y<(y+h))
      set1(flag,1);
     else
      set0(flag,1);
   }
   if(is1(flag,1))
   {if(me[1].key==1)
    {
     if(me[1].ch==8){if(no>0){no--;st[no]=0;}}
     else if(me[1].ch==13){set1(flag,2);}
     else if(no<num&&isalnum(me[1].ch))
     {st[no]=me[1].ch;
      no++;
      st[no]=0;
     }
    }
    if(me[1].key==2)
    {if(me[1].ch==72)set1(flag,3);
     else if(me[1].ch==80)set1(flag,4);
    }
    setfillstyle(SOLID_FILL,ACOL);
    bar(x-2,y-2,x+w+1,y+h+2);
   }
   setfillstyle(SOLID_FILL,8);
   bar(x+w1,y,x+w-1,y+h);
   setcolor(color);
   outtextxy(x+1,y+1,str);
   setcolor(15);
   outtextxy(x+1+w1,y+1,st);
 }
/*-----------------------------------------------------------------------*/
class button
{public:
 char *str;
 int x,y,h,w,w1,w2;
 int flag;
 button(int x1,int y1) ;
 void handle(event me[2]);

};
 button::button(int x1,int y1)
 {x=x1;y=y1;flag=0;
  h=charheight+4;w=639-x1-2;
  w1=textwidth(" PLAY : ");
  w2=textwidth(" PAUSE : ");
  set1(flag,1);
 }
 void button::handle(event me[2])
 {if(is1(flag,0))
  {if(is1(flag,1))
   {if(me[1].x>=x+w1-2&&me[1].y>y&&me[1].x<x+w1+charheight+2&&me[1].y<y+charheight+8)
    {setfillstyle(SOLID_FILL,ACOL);bar(x+w1-2,y,x+w1+charheight+2,y+charheight+8);
     if((me[1].b&1)==1){set1(flag,3);set0(flag,1);set1(flag,2);}
    }
   }
   if(is1(flag,2))
   {if(me[1].x>x+w/2+w2+1&&me[1].y>y&&me[1].x<x+w/2+w2+charheight+9&&me[1].y<y+charheight+8)
    {setfillstyle(SOLID_FILL,ACOL);bar(x+w/2+w2+1,y,x+w/2+w2+charheight+9,y+charheight+8);
     if((me[1].b&1)==1){set1(flag,4);set0(flag,2);set1(flag,1);}
    }
   }
  }
  if(is1(flag,1)&&is1(flag,0))setcolor(1);else setcolor(8);
  outtextxy(x+1,y+2," PLAY : ");
  setcolor(0);
  setfillstyle(SOLID_FILL,1);
  int pol[8];
  pol[0]=x+w1+2;pol[1]=y;
  pol[2]=x+w1+2;pol[3]=y+charheight+7;
  pol[4]=x+w1+(charheight+6)/sqrt(2);pol[5]=y+(charheight+6)/2+1;
  pol[6]=x+w1+2;pol[7]=y;
  fillpoly(4,pol);
  setcolor(9);
  drawpoly(4,pol);
  if(is1(flag,2)&&is1(flag,0))setcolor(2);else setcolor(8);
  outtextxy(x+1+w/2,y+2," PAUSE : ");
  setcolor(0);
  setfillstyle(SOLID_FILL,2);
  bar(x+w/2+w2+3,y+2,x+w/2+w2+charheight+7,y+charheight+6);
  setcolor(11);
  rectangle(x+w/2+w2+3,y+2,x+w/2+w2+charheight+7,y+charheight+6);
  line(x+w/2+7+w2,y+5,x+w/2+7+w2,y+charheight+3);
  line(x+w/2+11+w2,y+5,x+w/2+11+w2,y+charheight+3);

 }
/*---------------------------------------------------------------------*/
class radiobutton
{public:
 int x,y,flag;
 char *str1,*str2;
 radiobutton(char *string1,char *string2,int x1,int y1)
 {x=x1;y=y1;str1=string1;str2=string2;flag=0;
 }
 void handle(event me[2]);

};
 void radiobutton::handle(event me[2])
 {setcolor(0);
  setfillstyle(SOLID_FILL,15);
  fillellipse(x+4,y+charheight/2+3,3,3);
  if(is1(flag,1))
  {if(is1(flag,0))
   {setfillstyle(SOLID_FILL,0);
    fillellipse(x+4,y+charheight/2+3,1,1);
   }
   else
   {setcolor(8);
    setfillstyle(SOLID_FILL,8);
    fillellipse(x+4,y+charheight/2+3,1,1);
   }
  }
  else if(is1(flag,0)&&(me[1].b&1)==1)
  {if(me[1].x>=x+1&&me[1].x<=x+7&&me[1].y>=y+charheight/2+1&&me[1].y<=y+charheight/2+7)
   set1(flag,2);
  }
  setcolor(7);
  outtextxy(x+12,y+1,str1);
  outtextxy(x+12,y+1+charheight+3,str2);
 }
/*---------------------------------------------------------------------*/
class text
{public:
 int x,y,col;
 char *str;
 text(char *string,int x1,int y1,int color)
 {x=x1;y=y1;str=string;col=color;
 }
 void handle(event me[2])
 {setcolor(col);
  outtextxy(x+2,y+3,str);
 }
};
/*----------------------------------------------------------------------*/
class scrollbar
{public:
 int x,y,x1,w,flag;
 scrollbar(int px,int py)
 {x=px;y=py+charheight-4;flag=0;w=639-x-26;x1=w/4;
 }
 void handle(event me[2]);

};
 void scrollbar::handle(event me[2])
 {if(is1(flag,0))
  {if((me[1].b&3)==1)
   { if((me[2].b&3)==0&&me[1].x>=x+x1+11&&me[1].x<=x+x1+15&&me[1].y>=y-5&&me[1].y<=y+5)
       set1(flag,2);
     else if(is1(flag,2)&&me[1].x-x-13>=0&&me[1].x-x-13<w-5)
       x1=me[1].x-x-13;
   }
   else set0(flag,2);
  }
  setcolor(7);
  outtextxy(x+3,y-8-charheight,"Speed of time :");
  setcolor(0);
  line(x+10,y,x+10+w,y);
  for(int i=0;i<=5;i++)
   line(x+10+i*w/5,y-2,x+10+i*w/5,y+2);
  setcolor(0);
  setfillstyle(SOLID_FILL,1);
  bar(x+x1+11,y-5,x+x1+15,y+5);
 }
/*----------------------------------------------------------------------*/
class screen
{public:
 int flag,height;
 double m1,m2,t,dt,rad1,rad2,*array[4];
 vector r1,r2,v1,v2,d1,d2,w1,w2,pw1,pw2;
 Two_Mass_System *tms;
 screen()
 {flag=0;
  height=344-charheight-7;
  r1=vector(40,0);
  r2=vector(-40,0);
  v1=vector(0,25);
  v2=vector(0,-25);
 }
 void handle(event me[2]);

};
 void screen::handle(event me[2])
 {setviewport(5,5,5+440,5+height,1);
  clearviewport();
  if(is1(flag,0))
  {rad1=pow(m1/500,0.33333333);
   rad2=pow(m2/500,0.33333333);
   //
   if(is1(flag,12))
   {delete tms;
    set0(flag,12);
    if(is1(flag,7))
    {delete array[0];delete array[1];delete array[2];delete array[3];
     set0(flag,7);
    }
    if(is1(flag,6))
    {delete array[0];delete array[1];delete array[2];delete array[3];
     set0(flag,6);
    }
    if(is1(flag,5))
    {delete array[0];delete array[1];delete array[2];delete array[3];
     set0(flag,5);
    }
   }
   //
    if((me[1].b&1)==1)
    {vector vm2(me[2].x-5-220,height/2-me[2].y+5),
	     vm1(me[1].x-5-220,height/2-me[1].y+5);
     if((me[2].b&1)==0)
     { if((r1+v1-vm1).mod()<=5)
       set1(flag,8);
       else if((r2+v2-vm1).mod()<=5)
       set1(flag,9);
       else if((r1-vm1).mod()<=rad1)
       set1(flag,10);
       else if((r2-vm1).mod()<=rad2)
       set1(flag,11);
     }
     else if(me[1].x>5&&me[1].x<445&&me[1].y>5&&me[1].y<(5+height))
     { if(is1(flag,8))
	v1=vm1-r1;
       else if(is1(flag,9))
	v2=vm1-r2;
       else if(is1(flag,10))
	r1=vm1;
       else if(is1(flag,11))
	r2=vm1;
     }
    }
    else
    {set0(flag,8);set0(flag,9);set0(flag,10);set0(flag,11);
    }
    setcolor(COL1);
    setfillstyle(SOLID_FILL,COL1);
    fillellipse(r1.x+220,height/2-r1.y,rad1,rad1*Ratio);
    setcolor(14);
    setfillstyle(SOLID_FILL,14);
    fillellipse(r2.x+220,height/2-r2.y,rad2,rad2*Ratio);
    //
    setcolor(1);
    line(220+r1.x,height/2-r1.y,220+r1.x+v1.x,height/2-r1.y-v1.y);
    double ang=angle(v1.x,-v1.y);
    int pol[8];
    setfillstyle(SOLID_FILL,1);
    pol[0]=220+r1.x+v1.x;pol[1]=height/2-r1.y-v1.y;
    pol[2]=220+r1.x+v1.x+4*cos(ang+2.5);pol[3]=height/2-r1.y-v1.y+4*sin(ang+2.5);
    pol[4]=220+r1.x+v1.x+4*cos(ang-2.5);pol[5]=height/2-r1.y-v1.y+4*sin(ang-2.5);
    pol[6]=220+r1.x+v1.x;pol[7]=height/2-r1.y-v1.y;
    fillpoly(4,pol);
    //
    setcolor(2);
    line(220+r2.x,height/2-r2.y,220+r2.x+v2.x,height/2-r2.y-v2.y);
    ang=angle(v2.x,-v2.y);
    setfillstyle(SOLID_FILL,2);
    pol[0]=220+r2.x+v2.x;pol[1]=height/2-r2.y-v2.y;
    pol[2]=220+r2.x+v2.x+4*cos(ang+2.5);pol[3]=height/2-r2.y-v2.y+4*sin(ang+2.5);
    pol[4]=220+r2.x+v2.x+4*cos(ang-2.5);pol[5]=height/2-r2.y-v2.y+4*sin(ang-2.5);
    pol[6]=220+r2.x+v2.x;pol[7]=height/2-r2.y-v2.y;
    fillpoly(4,pol);
  }
  if(is1(flag,1))
  {if(is0(flag,12))
   {set1(flag,12);
    tms=new Two_Mass_System(m1,m2,r1,r2,v1,v2);
    if(is1(flag,13))
    {  setviewport(0,0,639,349,1);
       active
       setfillstyle(SOLID_FILL,7);
       bar(0,349-charheight-1,639,349);
       status("Wait...");
       active
       setviewport(5,5,5+440,5+height,1);
     if((tms->s->flag==2||tms->s->flag==3)&&tms->s->T*2/0.05<2000)
     {array[0]=new double[tms->s->T*2/0.05+25];
      array[1]=new double[tms->s->T*2/0.05+25];
      array[2]=new double[tms->s->T*2/0.05+25];
      array[3]=new double[tms->s->T*2/0.05+25];
      long i=0;
      for(double q=0;q<=tms->s->T*2+0.6;q+=0.05,i++)
      {tms->position_wrt_cm(q,w1,w2);
       array[0][i]=w1.x;
       array[1][i]=w1.y;
       array[2][i]=w2.x;
       array[3][i]=w2.y;
      }
      set1(flag,7);
     }
     if(tms->s->flag==1||tms->s->flag==4)
     {array[0]=new double[20/0.05+25];
      array[1]=new double[20/0.05+25];
      array[2]=new double[20/0.05+25];
      array[3]=new double[20/0.05+25];
      long i=0;
      for(double q=0;q<=20+0.5;q+=0.05,i++)
      {tms->position_wrt_cm(q,w1,w2);
       array[0][i]=w1.x;
       array[1][i]=w1.y;
       array[2][i]=w2.x;
       array[3][i]=w2.y;
      }
      set1(flag,6);
     }
     if(tms->s->flag==2&&tms->s->T*2/0.05>=2000)
     {array[0]=new double[40/0.05+25];
      array[1]=new double[40/0.05+25];
      array[2]=new double[40/0.05+25];
      array[3]=new double[40/0.05+25];
      long i=0;
      for(double q=-20-0.5;q<=20+0.5;q+=0.05,i++)
      {tms->position_wrt_cm(q,w1,w2);
       array[0][i]=w1.x;
       array[1][i]=w1.y;
       array[2][i]=w2.x;
       array[3][i]=w2.y;
      }
      set1(flag,5);
     }
    }
    t=0;
   }

   if(is1(flag,7))
   {setcolor(8);
    for(long i=2;i<t/0.05&&i*0.05<=tms->s->T*2+0.5;i++)
    {line(220+array[0][i],height/2-array[1][i]*Ratio,220+array[0][i+1],height/2-array[1][i+1]*Ratio);
     line(220+array[2][i],height/2-array[3][i]*Ratio,220+array[2][i+1],height/2-array[3][i+1]*Ratio);
    }
   }
   if(is1(flag,6))
   {setcolor(8);
     for(long i=2;i<t/0.05&&i*0.05<=20;i++)
     {line(220+array[0][i],height/2-array[1][i]*Ratio,220+array[0][i+1],height/2-array[1][i+1]*Ratio);
      line(220+array[2][i],height/2-array[3][i]*Ratio,220+array[2][i+1],height/2-array[3][i+1]*Ratio);
     }
   }
   if(is1(flag,5))
   {setcolor(8);
     for(long i=(20+0.5)/0.05;i*0.05-(20+0.5)<t&&i*0.05-(20+0.5)<=20;i++)
     {line(220+array[0][i],height/2-array[1][i]*Ratio,220+array[0][i+1],height/2-array[1][i+1]*Ratio);
      line(220+array[2][i],height/2-array[3][i]*Ratio,220+array[2][i+1],height/2-array[3][i+1]*Ratio);
     }
     for(i=0.5/0.05;i*0.05<(20+0.5)+t-tms->s->T*2&&i*0.05<=(20+0.5);i++)
     {line(220+array[0][i],height/2-array[1][i]*Ratio,220+array[0][i+1],height/2-array[1][i+1]*Ratio);
      line(220+array[2][i],height/2-array[3][i]*Ratio,220+array[2][i+1],height/2-array[3][i+1]*Ratio);
     }
   }
   if(is1(flag,13))
   { tms->position_wrt_cm(t,d1,d2);
     setviewport(0,0,639,349,1);
     if(tms->s->flag==1)status("Moving in Parabolic path");
     if(tms->s->flag==2)status("Moving in Elliptical path");
     if(tms->s->flag==3)status("Moving in Circular path");
     if(tms->s->flag==4)status("Moving in Hyperbolic path");
     setviewport(5,5,5+440,5+height,1);
   }
   else tms->position(t,d1,d2);
   setcolor(COL1);
   setfillstyle(SOLID_FILL,COL1);
   fillellipse(d1.x+220,height/2-d1.y*Ratio,rad1,rad1*Ratio);
   setcolor(COL2);
   setfillstyle(SOLID_FILL,COL2);
   fillellipse(d2.x+220,height/2-d2.y*Ratio,rad2,rad2*Ratio);
   t+=dt;
  }
  if(is1(flag,15))
  {setcolor(15);
   char str[100]="An Application by ";
   char ma[13];
   for(int i=0;i<13;i++)
    ma[i]=char(~st_[i]);
   strcat(str,ma);
   strcat(str," to obserb how a Mass  ");
   outtextxy(5,5,str);
   outtextxy(5,5+charheight+5,    "Body is affected in the Gravitational Feild developed" );
   outtextxy(5,5+2*(charheight+5),"by anoher Mass Body. ( Written in CPP )");
  }
  setviewport(0,0,639,349,1);
  setcolor(8);
  line(445,6,445,5+height);
  line(444,7,444,5+height);
  line(443,8,443,5+height);
  line(6,5+height,445,5+height);
  line(7,5+height-1,445,5+height-1);
  line(8,5+height-2,445,5+height-2);
 }
/*------------------------------------------------------------------------*/
void exitprogram();
class GUI
{screen sc;
 editor e1,e2,e3,e4,e5,e6;
 button b;
 radiobutton rb1,rb2;
 scrollbar scrbar;
 text t1,t2,t3;
 event me[2];
 public:
 GUI():t1("        Application on ",450,10,0),
       t2("   Gravitation b/w 2 masses",450,12+charheight+8,0),
       e1("Mass 1 : ",450,12+3*(charheight+8),15,COL1),
       e2("Mass 2 : ",450,12+4*(charheight+8),15,COL2),
       e3("    X1 : ",450,12+5*(charheight+8),15,COL1),
       e4("    Y1 : ",450,12+6*(charheight+8),15,COL1),
       e5("    X2 : ",450,12+7*(charheight+8),15,COL2),
       e6("    Y2 : ",450,12+8*(charheight+8),15,COL2),
       b(450,15+17*(charheight+8)),
       rb1("Motion in Monitor's ","reference frame",450,12+10*(charheight+8)),
       rb2("Motion in reference","frame of C.M.",450,12+12*(charheight+8)),
       scrbar(450,12+15.5*(charheight+8)),
       t3("Press ESC to exit",450,12+19*(charheight+8),0)
 {set1(e1.flag,0);
  set1(e2.flag,0);
  set1(e1.flag,1);
  set1(rb1.flag,1);
  set1(scrbar.flag,0);
 }


 void handle(event mev)
 {int f=0;
  me[2]=me[1];
  me[1]=mev;
  if(is1(sc.flag,15))
  {if(me[1].key==1)endprogram();
   else status("Press any key to exit");

  }
  if(me[1].key==1&&me[1].ch==27)
  {set0(sc.flag,0);
   set0(sc.flag,1);
   set1(sc.flag,15);
   status("Press any key to exit");
  }
  t1.handle(me);
  t2.handle(me);
  t3.handle(me);
  sc.handle(me);
  e1.handle(me);
  e2.handle(me);
  e3.handle(me);e3.st[0]=0;
  e4.handle(me);e4.st[0]=0;
  e5.handle(me);e5.st[0]=0;
  e6.handle(me);e6.st[0]=0;
  b.handle(me);
  rb1.handle(me);
  rb2.handle(me);
  scrbar.handle(me);
  if(is1(sc.flag,15))return;
  sc.dt=(0.5*scrbar.x1)/scrbar.w;
  if(is1(e1.flag,2)||is1(e1.flag,4))
  {set0(e1.flag,1);set0(e1.flag,2);set0(e1.flag,4);set1(e2.flag,1);
  }
  if(is1(e2.flag,2))
  {set0(e2.flag,1);set0(e2.flag,2);
  }
  if(is1(e2.flag,3))
  {set0(e2.flag,3);set0(e2.flag,1);set1(e1.flag,1);
  }
  if(e1.st[0]!=0)
  { set1(f,2);for(int i=0;e1.st[i]!=0;i++)if(!isdigit(e1.st[i])){set1(f,0);break;}
  }
  if(e2.st[0]!=0)
  { set1(f,3);for(int i=0;e2.st[i]!=0;i++)if(!isdigit(e2.st[i])){set1(f,1);break;}
  }
  switch(f&3)
  {case 1:status("Invalid Mass 1");break;
   case 2:status("Invalid Mass 2");break;
   case 3:status("Invalid Mass 1 and Mass 2");
  };
  if((f&3)!=0||(f>>2)!=3)
  { set0(sc.flag,0);
    set0(b.flag,0);
    set0(rb1.flag,0);
    set0(rb2.flag,0);
  }
  if(is0(sc.flag,0)&&(f&3)==0&&is0(sc.flag,1))status("Enter Mass 1 and Mass 2");
  if(is1(sc.flag,0))status("Use Mouse to set position and direction of velocity of both masses");
  if((f&3)==0&&(f>>2)==3&&is0(sc.flag,1))
  {set1(sc.flag,0);
   long lm1,lm2;
   sscanf(e1.st,"%ld",&lm1);
   sscanf(e2.st,"%ld",&lm2);
   sc.m1=lm1;
   sc.m2=lm2;
   set1(b.flag,0);
   set1(rb1.flag,0);
   set1(rb2.flag,0);
  }
  if(is1(b.flag,3))          //play
  {set0(b.flag,3);
   set0(e1.flag,0);
   set0(e2.flag,0);
   set0(sc.flag,0);
   set1(sc.flag,1);
   set0(rb1.flag,0);
   set0(rb2.flag,0);
  }
  if(is1(b.flag,4))         //pause
  {set0(b.flag,4);
   set1(e1.flag,0);
   set1(e2.flag,0);
   set1(sc.flag,0);
   set0(sc.flag,1);
   set1(rb1.flag,0);
   set1(rb2.flag,0);
  }
  if(is1(sc.flag,0)&&(f&3)==0)
  {sprintf(e3.st,"%f",sc.r1.x);
   sprintf(e4.st,"%f",sc.r1.y);
   sprintf(e5.st,"%f",sc.r2.x);
   sprintf(e6.st,"%f",sc.r2.y);
  }
  if(is1(sc.flag,1)&&(f&3)==0)
  {sprintf(e3.st,"%f",sc.d1.x);
   sprintf(e4.st,"%f",sc.d1.y);
   sprintf(e5.st,"%f",sc.d2.x);
   sprintf(e6.st,"%f",sc.d2.y);
  }
  if(is1(rb1.flag,2))
  {set0(rb1.flag,2);
   set1(rb1.flag,1);
   set0(rb2.flag,1);
   set0(sc.flag,13);

  }
  if(is1(rb2.flag,2))
  {set0(rb2.flag,2);
   set1(rb2.flag,1);
   set0(rb1.flag,1);
   set1(sc.flag,13);

  }
 }
};
/*-----------------------------------------------------------------------*/
void showmouse(event me);
void main()
{int gd=VGA,gm=VGAMED;
 initgraph(&gd,&gm,0);
 settextstyle(2,HORIZ_DIR,4);
 charheight=textheight("j");
 char ch=0;
 event me;
 Mouse ms;
 ms.init();
 GUI gui;
  setfillstyle(SOLID_FILL,BGCOL);
  bar(0,0,639,349-charheight-2);
  setfillstyle(SOLID_FILL,7);
  bar(0,349-charheight-1,639,349);
  showmouse(me);
 do
 {if(kbhit())
  {ch=getch();
   if(ch!=0){me.key=1;me.ch=ch;}
   else {me.key=2;me.ch=getch();}
  }
  else me.key=0;
  ms.getkey(me.b,me.x,me.y);
  active
  cleardevice();
  setfillstyle(SOLID_FILL,BGCOL);
  bar(0,0,639,349-charheight-2);
  setfillstyle(SOLID_FILL,7);
  bar(0,349-charheight-1,639,349);
  gui.handle(me);
  showmouse(me);
  visual
  delay(20);
 }while(1);

}
void showmouse(event me)
{int pol[8];
 setcolor(15);
 setfillstyle(SOLID_FILL,15);
 pol[0]=me.x;pol[1]=me.y;
 pol[2]=me.x;pol[3]=me.y+10;
 pol[4]=me.x+7;pol[5]=me.y+7;
 pol[6]=me.x;pol[7]=me.y;
 fillpoly(4,pol);
 line(me.x,me.y,me.x+6,me.y+14);
}
void endprogram()
{closegraph();
 exit(0);
}