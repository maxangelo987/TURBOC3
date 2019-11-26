//@ author Shubham Jain
#ifndef MOUSE_H
#define MOUSE_H

#include<dos.h>
class Mouse
{union REGS i,o;
public:
 void init()          //For Initialize
 {i.x.ax=0;
  int86(0x33,&i,&o);
 }
 void show()
 {i.x.ax=1;
  int86(0x33,&i,&o);
 }
 void hide()
 {i.x.ax=2;
  int86(0x33,&i,&o);
 }
 void getkey(int& b,int& x,int& y)
 {i.x.ax=3;
  int86(0x33,&i,&o);
  b=o.x.bx;
  x=o.x.cx;
  y=o.x.dx;
 }
 void setrestriction(int x,int y,int width,int height)
 {i.x.ax=7;
  i.x.cx=x;
  i.x.dx=x+width;
  int86(0x33,&i,&o);
  i.x.ax=8;
  i.x.cx=y;
  i.x.dx=y+height;
  int86(0x33,&i,&o);
 }
 ~Mouse()
 {hide();
 }
};
#endif

/*How to use:

  1)Make a object of class "Mouse"
   //  Mouse me;
  2)Initialize the mouse
   // me.init();
  3)to show it in screen
   // me.show();
  4)to hide it from screen
   // me.hide();
  5)for a mouse input
   // me.getkey(b,x,y);
   after calling it with b,x,y
   x,y contains coordinates ( upper left top as x=0,y=0 )
   going right a pixel increases x coordinate with +1 in graphics mode
   going down a pixel increases y coordinate with +1 in graphics mode

   In console mode
    x increases with no. of pixels required for Character width
	 mostly is 8
    y increases with no. of pixels required for Character height
	 mostly is 8

   b contains mouse click state
   b as integer would be made of the following bits (an integer has 16 bits)
       b15 b14 ....... b5 b4 b3 b2 b1 b0
   where b* represents a bit field (here * from 0 to 15)
   b0 lowest bit field and b15 highest bit field

   Bit fields corressponds to different mouse buttons

   BitField   Mouse_button
   b0         Right
   b1         Left
   b2         Middle

   if bitfield is set 0 then button is up
   if bitfield is set 1 then button is down

   right button can be checked with some code like:
   //if((b&1)==1)
      statement(s);
      ......
   like this left can be checked with
   //if((b&2)==2)
      statement(s);
      ......

  6)To restrict the mouse in a given rectangular region use
   //me.setrestriction(x,y,width,height);
   x,y are the coordinates of upper left corner of the region
   width,height represents the width & height of region in pixels
*/


