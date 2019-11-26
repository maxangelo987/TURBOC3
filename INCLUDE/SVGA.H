//@ author Shubham Jain
#ifndef SVGA_H
#define SVGA_H

#include<dos.h>

struct SVGAinfo
{char       VESASignature[4];
 short      VESAVersion;
 char far  *OEMstr;
 long       Capabilities;
 short far *Modeptr;
 short      TotalMemory;
 char       Reserved[236];
};
struct MODEinfo
{unsigned short ModeAttributes;
 unsigned char  WinAAttributes;
 unsigned char  WinBAttributes;
 unsigned short WinGranularity;
 unsigned short WinSize;
 unsigned short WinASegment;
 unsigned short WinBSegment;
 void far       (*WinFuncptr)();
 unsigned short BytesPerScanLine;
 unsigned short XResolution;
 unsigned short YResolution;
 unsigned char  XCharSize;
 unsigned char  YCharSize;
 unsigned char  NumberOfPlanes;
 unsigned char  BitsPerPixel;
 unsigned char  NumberOfBanks;
 unsigned char  MemoryModel;
 unsigned char  BankSize;
 unsigned char  NumberOfImagePages;
 unsigned char  reserved1;
 unsigned char  RedMaskSize;
 unsigned char  RedFieldPosition;
 unsigned char  GreenMaskSize;
 unsigned char  GreenFieldPosition;
 unsigned char  BlueMaskSize;
 unsigned char  BlueFieldPosition;
 unsigned char  RsvdMaskSize;
 unsigned char  RsvdFieldPosition;
 unsigned char  DirectColorModeInfo;
 void far       *PhysBaseptr;
 unsigned long  reserved2;
 unsigned short reserved3;
 unsigned short LinBytesPerScanLine;
 unsigned char  BnkNumberOfImagePages;
 unsigned char  LinNumberOfImagePages;
 unsigned char  reserved[202];
};
int getSVGAinfo(struct SVGAinfo *v)
{union REGS i,o;
 SREGS s;
 i.x.ax=0x4f00;
 i.x.di=FP_OFF(v);
 s.es=FP_SEG(v);
 int86x(0x10,&i,&o,&s);
 return o.x.ax;
}
int getMODEinfo(int mode,struct MODEinfo *m)
{union REGS i,o;
 SREGS s;
 i.x.ax=0x4f01;
 i.x.cx=mode;
 i.x.di=FP_OFF(m);
 s.es=FP_SEG(m);
 int86x(0x10,&i,&o,&s);
 return o.x.ax;
}
int setSVGAmode(int mode)
{union REGS i,o;
 i.x.ax=0x4f02;
 i.x.bx=mode;
 i.x.dx=0;
 int86(0x10,&i,&o);
 return o.x.ax;
}
int setbank(int b)
{union REGS i,o;
 i.x.ax=0x4f05;
 i.x.bx=0;
 i.x.dx=b;
 int86(0x10,&i,&o);
 return o.x.ax;
}
int setstartpixel(int x,int y)
{union REGS i,o;
 i.x.ax=0x4f07;
 i.x.bx=0;
 i.x.cx=x;
 i.x.dx=y;
 int86(0x10,&i,&o);
 return o.x.ax;
}

#endif