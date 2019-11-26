//@ author Shubham Jain
#ifndef GRAPHRGB_H
#define GRAPHRGB_H

#include<base.h>
#include<svga.h>
#include<mouse.h>
#include<vector.h>

#define Ratio 1.3636

class Color
{static BYTE4 c;
public:
 unsigned char R,G,B,V;
 Color(char r=0,char g=0,char b=0,char v=0)
 {R=r;G=g;B=b;V=v;
 }
 static long RGB(char r,char g,char b,char v=0)
 {c.c[0]=b;
  c.c[1]=g;
  c.c[2]=r;
  c.c[3]=v;
  return c.l;
 }
 operator long()
 {c.c[0]=B;
  c.c[1]=G;
  c.c[2]=R;
  c.c[3]=V;
  return c.l;
 }
};
BYTE4 Color:: c;

class Point
{public:
 int x,y;
 Point(int X=0,int Y=0)
 {x=X;y=Y;
 }
};

class Rect
{public:
 int x,y,w,h;
 Rect(int X=0,int Y=0,int W=0,int H=0)
 {x=X;y=Y;w=W;h=H;
 }
 Rect operator &(Rect &r)
 {Rect a;
  a.x=(x>r.x)?x:r.x;
  a.y=(y>r.y)?y:r.y;
  a.w=((x+w)<(r.x+r.w))?(x+w-a.x):(r.x+r.w-a.x);
  a.h=((y+h)<(r.y+r.h))?(y+h-a.y):(r.y+r.h-a.y);
  return a;
 }
 Rect operator |(Rect &r)
 {Rect a;
  a.x=(x<r.x)?x:r.x;
  a.y=(y<r.y)?y:r.y;
  a.w=((x+w)>(r.x+r.w))?(x+w-a.x):(r.x+r.w-a.x);
  a.h=((y+h)>(r.y+r.h))?(y+h-a.y):(r.y+r.h-a.y);
  return a;
 }
};

class Source
{friend Graphics;
 Rect viewport;
public:
 long color;
 long bkcolor;
 long fillcolor;

 Source()
 {color  =Color::RGB(255,255,255);
  bkcolor=Color::RGB(0,0,0);
  fillcolor=Color::RGB(255,255,255);
  viewport=Rect(0,0,1024,768);
 }

};

class Image
{int h,w;
 long *ptr;
 friend Graphics;
public:

 Image(long *add,int width,int height)
 {h=height;
  w=width;
  ptr=add;
 }
};



class Graphics
{struct SVGAinfo svgainfo;
 struct MODEinfo modeinfo;
 union REGS i,o;  SREGS s;
 Source *sc;
 int oldmode,apage,vpage;
 BYTE4 v;
 int mode_support,mouse_support;
 Mouse ms;

 void far (*ChangeBankFunc)();
 void (*showmouse)(Graphics &);

public:
 long far * vmem;
 int ModeNo,shift,bpp/*banksperpage*/,offset,lpb/*scanlinesperbank*/;

 Graphics(Source & source);
 int init();

 void changebank(int b)
 {
  _BX=0;
  _DX=b+apage*bpp;
  ChangeBankFunc();
  //setbank(b+apage*bpp);   Interruption call beside of above code
 }

 void putpixel(int x,int y,long color)
 {if(x<0||x>1023||y<0||y>767)return;
  changebank(y>>shift);
  *(vmem+((y&offset)<<10)+x)=color;
 }

 void close()
 {if(oldmode<0x100)
  {i.h.ah=0;
   i.h.al=oldmode;
   int86(0x10,&i,&o);
  }
  else
   setSVGAmode(oldmode);
 }

 ~Graphics()
 {close();
  if(mode_support==1)
  ms.setrestriction(0,0,639,479);
 }

 void initmouse(void (*sm)(Graphics&));

 Source & changeSource(Source &s)
 {Source &p=*sc;
  *sc=s;
  return p;
 }

 void setvisualpage(int p){ vpage=p%2; setstartpixel(0,768*vpage); }
 void setactivepage(int p){ apage=p%2; }
 void nextactive(){ apage^=1; }
 void nextvisual(){ vpage^=1;setvisualpage(vpage);}
 void setflipping(){ setactivepage(1);  setvisualpage(0); }

 void next()
 { if(mouse_support)showmouse(*this);
   nextactive();
   nextvisual();
 }

 void fillcircle(vector r0,double rad,Color c);
 void circle3d(vector r0,double rad,vector s,Color c1,Color c2);
 void clearscreen(){fillrect(0,0,1024,768,sc->bkcolor); }
 void drawrect(int x,int y,int width,int height,long color);
 void drawrect(int x,int y,int width,int height);
 void fillrect(int x,int y,int w,int h,long color);
 void fillrect(int x,int y,int w,int h)
 {fillrect(x,y,w,h,sc->fillcolor);
 }
 Image getImage(int x,int y,int w,int h);
 void drawImage(Image &im,int x,int y,int w,int h,int x1=0,int y1=0);
 void fillrect(int x,int y,int w,int h,Image &im);
};

//Functions---------------------------------------------------------------
Graphics::Graphics(Source & source)
{ vmem=(long far *)0xA0000000l;
  v.lfp=(long far *)0xA0000000l;
  sc=&source;
  apage=0;vpage=0;
  mouse_support=0;
  int f=getSVGAinfo(&svgainfo);
  mode_support=0;
  if(f==0x004f)
  {for(int no=0;svgainfo.Modeptr[no]!=int(0xffff);no++);
   for(int j=0;j<no;j++)
   { f=getMODEinfo(svgainfo.Modeptr[j],&modeinfo);
     if(f!=0x004f)break;
     if(contains(modeinfo.ModeAttributes,27)&&contains(modeinfo.WinAAttributes,7)
       &&modeinfo.XResolution==1024&&modeinfo.YResolution==768
       &&modeinfo.BitsPerPixel==32&&modeinfo.NumberOfImagePages>=2)
     {	  mode_support=1;
	  ModeNo=svgainfo.Modeptr[j];
	  ChangeBankFunc=modeinfo.WinFuncptr;
	  int gr=modeinfo.WinGranularity/4;
	  lpb=gr;
	  bpp=768/gr;
	  offset=gr-1;
	  for(shift=0;gr!=1;shift++)gr=gr>>1;
	  break;
     }
   }
  }
}

int Graphics::init()
{ if(mode_support==1)
  {i.h.ah=0xf;
   int86(0x10,&i,&o);
   oldmode=o.h.al;
   setSVGAmode(ModeNo);
   return 1;
  }
  else return 0;
}

void Graphics::initmouse(void (*sm)(Graphics&))
{mouse_support=1;
 showmouse=sm;
 ms.setrestriction(0,0,1023,767);
}

void Graphics::circle3d(vector r0,double rad,vector s,Color c1,Color c2)
{s=s.unit();
 double f,x0;
 vector r;
 int j,b,j1,b1,j2,b2,y1,y2,x1,x2,x;
 if(rad<0.6)
 {if(s.z>0)putpixel(512+r0.x,384-r0.y,c1);
  else putpixel(512+r0.x,384-r0.y,c2);
  return;
 }
 y1=385-r0.y-rad*Ratio;
 if(y1<0)y1=0;
 y2=384-r0.y+rad*Ratio;
 if(y2>767)y2=767;
 if(y2<y1)return;
 b1=y1>>shift;
 j1=y1&offset;
 b2=y2>>shift;
 j2=y2&offset;
 if(b1==b2)
 { changebank(b1);
   for(j=j1;j<=j2;j++)
   {r.y=(384-r0.y-b1*lpb-j)/Ratio;
    x0=sqrt(fabs(rad*rad-r.y*r.y));
    x1=512+r0.x-x0;
    x2=512+r0.x+x0;
    if(x1<0)x1=0;
    if(x2>1023)x2=1023;
    for(x=x1;x<=x2;x++)
    {r.x=x-512-r0.x;
     r.z=sqrt(fabs(rad*rad-r.x*r.x-r.y*r.y));
     f=((-r).unit()).dot(s);
     if(f<0)f=0;
     *(vmem+(j<<10)+x)=Color::RGB(c1.R+f*c2.R,c1.G+f*c2.G,c1.B+f*c2.B);
    }
   }
 }
 else
 {
   changebank(b1);
   for(j=j1;j<lpb;j++)
   {r.y=(384-r0.y-b1*lpb-j)/Ratio;
    x0=sqrt(fabs(rad*rad-r.y*r.y));
    x1=512+r0.x-x0;
    x2=512+r0.x+x0;
    if(x1<0)x1=0;
    if(x2>1023)x2=1023;
    for(x=x1;x<=x2;x++)
    {r.x=x-512-r0.x;
     r.z=sqrt(fabs(rad*rad-r.x*r.x-r.y*r.y));
     f=((-r).unit()).dot(s);
     if(f<0)f=0;
     *(vmem+(j<<10)+x)=Color::RGB(c1.R+f*c2.R,c1.G+f*c2.G,c1.B+f*c2.B);
    }
   }
  for(b=b1+1;b<b2;b++)
  {changebank(b);
   for(j=0;j<lpb;j++)
   {r.y=(384-r0.y-b*lpb-j)/Ratio;
    x0=sqrt(fabs(rad*rad-r.y*r.y));
    x1=512+r0.x-x0;
    x2=512+r0.x+x0;
    if(x1<0)x1=0;
    if(x2>1023)x2=1023;
    for(x=x1;x<=x2;x++)
    {r.x=x-512-r0.x;
     r.z=sqrt(fabs(rad*rad-r.x*r.x-r.y*r.y));
     f=((-r).unit()).dot(s);
     if(f<0)f=0;
     *(vmem+(j<<10)+x)=Color::RGB(c1.R+f*c2.R,c1.G+f*c2.G,c1.B+f*c2.B);
    }
   }
  }
  changebank(b2);
   for(j=0;j<=j2;j++)
   {r.y=(384-r0.y-b2*lpb-j)/Ratio;
    x0=sqrt(fabs(rad*rad-r.y*r.y));
    x1=512+r0.x-x0;
    x2=512+r0.x+x0;
    if(x1<0)x1=0;
    if(x2>1023)x2=1023;
    for(x=x1;x<=x2;x++)
    {r.x=x-512-r0.x;
     r.z=sqrt(fabs(rad*rad-r.x*r.x-r.y*r.y));
     f=((-r).unit()).dot(s);
     if(f<0)f=0;
     *(vmem+(j<<10)+x)=Color::RGB(c1.R+f*c2.R,c1.G+f*c2.G,c1.B+f*c2.B);
    }
   }
 }
}
void Graphics::fillcircle(vector r0,double rad,Color c)
{
 double x0;
 vector r;
 int j,b,j1,b1,j2,b2,y1,y2,x1,x2,x;
 if(rad<0.6)
 {putpixel(512+r0.x,384-r0.y,c);
 }
 y1=385-r0.y-rad*Ratio;
 if(y1<0)y1=0;
 y2=384-r0.y+rad*Ratio;
 if(y2>767)y2=767;
 if(y2<y1)return;
 b1=y1>>shift;
 j1=y1&offset;
 b2=y2>>shift;
 j2=y2&offset;
 if(b1==b2)
 { changebank(b1);
   for(j=j1;j<=j2;j++)
   {r.y=(384-r0.y-b1*lpb-j)/Ratio;
    x0=sqrt(fabs(rad*rad-r.y*r.y));
    x1=512+r0.x-x0;
    x2=512+r0.x+x0;
    if(x1<0)x1=0;
    if(x2>1023)x2=1023;
    for(x=x1;x<=x2;x++)
    *(vmem+(j<<10)+x)=c;
   }
 }
 else
 {
   changebank(b1);
   for(j=j1;j<lpb;j++)
   {r.y=(384-r0.y-b1*lpb-j)/Ratio;
    x0=sqrt(fabs(rad*rad-r.y*r.y));
    x1=512+r0.x-x0;
    x2=512+r0.x+x0;
    if(x1<0)x1=0;
    if(x2>1023)x2=1023;
    for(x=x1;x<=x2;x++)
    *(vmem+(j<<10)+x)=c;
   }
  for(b=b1+1;b<b2;b++)
  {changebank(b);
   for(j=0;j<lpb;j++)
   {r.y=(384-r0.y-b*lpb-j)/Ratio;
    x0=sqrt(fabs(rad*rad-r.y*r.y));
    x1=512+r0.x-x0;
    x2=512+r0.x+x0;
    if(x1<0)x1=0;
    if(x2>1023)x2=1023;
    for(x=x1;x<=x2;x++)
    *(vmem+(j<<10)+x)=c;
   }
  }
  changebank(b2);
   for(j=0;j<=j2;j++)
   {r.y=(384-r0.y-b2*lpb-j)/Ratio;
    x0=sqrt(fabs(rad*rad-r.y*r.y));
    x1=512+r0.x-x0;
    x2=512+r0.x+x0;
    if(x1<0)x1=0;
    if(x2>1023)x2=1023;
    for(x=x1;x<=x2;x++)
    *(vmem+(j<<10)+x)=c;
   }
 }
}

void Graphics::fillrect(int x,int y,int w,int h,long color)
{if(w<0){w*=-1;x=x-w+1;}
 if(h<0){h*=-1;y=y-h+1;}
 if(x<0){w=w+x;x=0;}
 if(y<0){h=h+y;y=0;}
 if((x+w)>1024){w=1024-x;}
 if((y+h)>768){h=768-y;}
 int b1=y>>4,b2=(y+h-1)>>4;
 changebank(b1);
 if(b1==b2)
 {for(int i=(y%16);i<=((y+h-1)%16);i++)
   for(int j=0;j<w;j++)
    *(vmem+i*1024+x+j)=color;
 }
 else
 { for(int i=(y%16);i<16;i++)
    for(int j=0;j<w;j++)
     *(vmem+i*1024+x+j)=color;
   for(int b=b1+1;b<b2;b++)
   {changebank(b);
    for(i=0;i<16;i++)
     for(j=0;j<w;j++)
      *(vmem+i*1024+x+j)=color;
   }
   changebank(b);
   for(i=0;i<=((y+h-1)%16);i++)
    for(j=0;j<w;j++)
     *(vmem+i*1024+x+j)=color;
 }
}
void Graphics::fillrect(int x,int y,int w,int h,Image &im)
{if(w<0){w*=-1;x=x-w+1;}
 if(h<0){h*=-1;y=y-h+1;}
 if(x<0){w=w+x;x=0;}
 if(y<0){h=h+y;y=0;}
 if((x+w)>1024){w=1024-x;}
 if((y+h)>768){h=768-y;}
 int b1=y>>4,b2=(y+h-1)>>4,c=0;
 BYTE4 color;
 changebank(b1);
 if(b1==b2)
 {for(int i=(y%16);i<=((y+h-1)%16);i++,c++)
   for(int j=0;j<w;j++)
   {color.l=*(im.ptr+(c%im.h)*im.w+j%im.w);
    if(color.c[3]==0)*(vmem+i*1024+x+j)=color.l;
   }
 }
 else
 { for(int i=(y%16);i<16;i++,c++)
    for(int j=0;j<w;j++)
    {color.l=*(im.ptr+(c%im.h)*im.w+j%im.w);
    if(color.c[3]==0)*(vmem+i*1024+x+j)=color.l;
    }
   for(int b=b1+1;b<b2;b++)
   {changebank(b);
    for(i=0;i<16;i++,c++)
     for(j=0;j<w;j++)
     {color.l=*(im.ptr+(c%im.h)*im.w+j%im.w);
     if(color.c[3]==0)*(vmem+i*1024+x+j)=color.l;
     }
   }
   changebank(b);
   for(i=0;i<=((y+h-1)%16);i++,c++)
    for(j=0;j<w;j++)
    {color.l=*(im.ptr+(c%im.h)*im.w+j%im.w);
     if(color.c[3]==0)*(vmem+i*1024+x+j)=color.l;
    }
 }
}

void Graphics::drawImage(Image &im,int x,int y,int w,int h,int x1,int y1)
{if(w<0||h<0||x1<0||y1<0||x1>=im.w||y1>=im.h||x>=1024||y>=768)return;
 if((x1+w)>im.w)w=im.w-x1;
 if((y1+h)>im.h)h=im.h-y1;
 if(x<0){x1-=x;w+=x;x=0;}
 if(y<0){y1-=y;h+=y;y=0;}
 if(x1>=im.w||y1>=im.h)return;
 if((x+w)>1024){w=1024-x;}
 if((y+h)>768 ){h=768 -y;}
 int b1=y>>4,b2=(y+h-1)>>4,c=0;
 BYTE4 color;
 changebank(b1);
 if(b1==b2)
 {for(int i=(y%16);i<=((y+h-1)%16);i++,c++)
   for(int j=0;j<w;j++)
   {color.l=*(im.ptr+(y1+c)*im.w+x1+j);
    if(color.c[3]==0)*(vmem+i*1024+x+j)=color.l;
   }
 }
 else
 { for(int i=(y%16);i<16;i++,c++)
    for(int j=0;j<w;j++)
    {color.l=*(im.ptr+(y1+c)*im.w+x1+j);
    if(color.c[3]==0)*(vmem+i*1024+x+j)=color.l;
    }
   for(int b=b1+1;b<b2;b++)
   {changebank(b);
    for(i=0;i<16;i++,c++)
     for(j=0;j<w;j++)
     {color.l=*(im.ptr+(y1+c)*im.w+x1+j);
     if(color.c[3]==0)*(vmem+i*1024+x+j)=color.l;
     }
   }
   changebank(b);
   for(i=0;i<=((y+h-1)%16);i++,c++)
    for(j=0;j<w;j++)
    {color.l=*(im.ptr+(y1+c)*im.w+x1+j);
     if(color.c[3]==0)*(vmem+i*1024+x+j)=color.l;
    }
 }
}
Image Graphics::getImage(int x,int y,int w,int h)
{Image im(0,0,0);
 if(w<0){w*=-1;x=x-w+1;}
 if(h<0){h*=-1;y=y-h+1;}
 if(x<0){w=w+x;x=0;}
 if(y<0){h=h+y;y=0;}
 if((x+w)>1024){w=1024-x;}
 if((y+h)>768){h=768-y;}
 long *l=new long[w*h];
 if(l==0){return im;}
 im.ptr=l;im.w=w;im.h=h;
 int b1=y>>4,b2=(y+h-1)>>4,c=0;
 changebank(b1);
 if(b1==b2)
 {for(int i=(y%16);i<=((y+h-1)%16);i++,c++)
   for(int j=0;j<w;j++)
    *(im.ptr+c*w+j)=*(vmem+i*1024+x+j);
 }
 else
 { for(int i=(y%16);i<16;i++,c++)
    for(int j=0;j<w;j++)
     *(im.ptr+c*w+j)=*(vmem+i*1024+x+j);
   for(int b=b1+1;b<b2;b++)
   {changebank(b);
    for(i=0;i<16;i++,c++)
     for(j=0;j<w;j++)
     *(im.ptr+c*w+j)=*(vmem+i*1024+x+j);
   }
   changebank(b);
   for(i=0;i<=((y+h-1)%16);i++,c++)
    for(j=0;j<w;j++)
    *(im.ptr+c*w+j)=*(vmem+i*1024+x+j);
 }
 return im;
}
#endif