//@ author Shubham Jain
#ifndef GRAPH_H
#define GRAPH_H

#include<graphics.h>
#include<base.h>
#include<svga.h>
#include<mouse.h>

#define Ratio 0.994

int cs_=0;
#define active       \
{if(is0(cs_,0))      \
  setactivepage(1);  \
 else                \
  setactivepage(0);  \
 cs_^=1;             \
}
#define visual       \
{if(is0(cs_,1))      \
  setvisualpage(1);  \
 else                \
  setvisualpage(0);  \
 cs_^=2;             \
}

#endif