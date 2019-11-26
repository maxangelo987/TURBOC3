//@ author Shubham Jain
//This header file contains classes and functions
//for SVGA mode 105h : 1024*768(256 color)
#ifndef GRAPH256_H
#define GRAPH256_H

#include<base.h>
#include<svga.h>
#include<mouse.h>

#define sratio  0.55     //  sratio=ScreenHeight/ScreenWidth

enum Colors
{   BG,
    Blue,           /* dark colors */
    Green,
    Cyan,
    Red,
    Magenta,
    Brown,
    LightGray,
    DarkGray,       /* light colors */
    LightBlue,
    LightGreen,
    LightCyan,
    LightRed,
    LightMagenta,
    Yellow,
    White,
    Black
};
enum ColorRange
{   Default,
    BtoW,
    BtoR,
    RtoG,
    GtoB
};
char Color256(int type,int no,int cont=2,int bright=0)
{if(type==Default)return (char)no;
 if(type==BtoW)return(16+(no%16));
 if(type==BtoR)no=no%9;
 if(type==RtoG)no=8+no%9;
 if(type==GtoB)
 {if((no%9)==8)no=0;
  else no=16+no%9;
 }
 cont%=3;
 bright%=4;
 if(bright==3)return 19+6*cont;
 return(32+72*(2-cont)+24*bright+no);
}

class Source
{friend Graphics;
public:
 char color;
 char bkcolor;
 char fillcolor;
 Source()
 {color  =15;
  bkcolor=0 ;
 }
};

class Image
{int h,w;
 char *ptr;
 friend Graphics;
public:

 Image(char *add,int width,int height)
 {h=height;
  w=width;
  ptr=add;
 }
};

class Graphics
{
 union REGS i,o;  SREGS s;
 Source *sc;
 int oldmode,apage,vpage;
 int mouse_support;
 Mouse ms;

 void far (*ChangeBankFunc)();
 void (*showmouse)(Graphics &);

public:
 char far * vmem;

 Graphics(Source & source)
 {vmem=(char far *)0xA0000000;
  sc=&source;
  apage=0;vpage=0;
  mouse_support=0;
  struct MODEinfo modeinfo;
  getMODEinfo(0x105,&modeinfo);
  ChangeBankFunc=modeinfo.WinFuncptr;
 }
 void init()
 {i.h.ah=0xf;
  int86(0x10,&i,&o);
  oldmode=o.h.al;
  setSVGAmode(0x105);
 }

 void changebank(int b)
 {_BX=0;
  _DX=b+apage*12;
  ChangeBankFunc();
  //setbank(b+apage*12);   Interruption call beside of above code
 }

 void putpixel(int x,int y,char color)
 {if(x<0|x>1023|y<0|y>767)return;
  changebank(y>>6);
  *(vmem+(y&63)*1024+x)=color;
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
  ms.setrestriction(0,0,639,479);
 }

 void initmouse(void (*sm)(Graphics&))
 {mouse_support=1;
  showmouse=sm;
  ms.setrestriction(0,0,1023,767);
 }

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

 void clearscreen(){fillrect(0,0,1024,768,sc->bkcolor); }
 void drawrect(int x,int y,int width,int height,char color);
 void drawrect(int x,int y,int width,int height);
 void fillrect(int x,int y,int w,int h,char color);
 void fillrect(int x,int y,int w,int h)
 {fillrect(x,y,w,h,sc->fillcolor);
 }
 Image getImage(int x,int y,int w,int h);
 void drawImage(Image &im,int x,int y,int w,int h,int x1=0,int y1=0);
 void fillrect(int x,int y,int w,int h,Image &im);
};

//Functions---------------------------------------------------------------

void Graphics::fillrect(int x,int y,int w,int h,char color)
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
 im.ptr=(char*)l;im.w=w;im.h=h;
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