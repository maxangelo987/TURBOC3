#ifndef display2
#define display2

#include<graphics.h>
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<process.h>

class display_2
{
public:
display_2()
	    {
	    }

~display_2(){}

void display_2_process();
};

void display_2::display_2_process()
{
int gd=DETECT, gm, c;
initgraph(&gd,&gm,"C:\\turboc3\\bgi");

	       clrscr();
	       initgraph(&gd,&gm,"C:\\turboc3\\bgi");
	       setbkcolor(BLUE);
	       settextstyle(TRIPLEX_FONT, HORIZ_DIR,2);
	       setcolor(WHITE);
	       outtextxy(62,100," CpE 412 - Structures of Programming Languages      ");
	       outtextxy(62,140,"                  PROJECT NO. 3                     ");
	       outtextxy(62,170,"        Context Free Grammar w/ Parse Tree          ");
	       outtextxy(70,320," Perin, Max Angelo                                  ");
	       outtextxy(70,340,"      BSCpE 4                                       ");
	       outtextxy(70,360,"                              Engr. Edgar Uy II     ");
	       outtextxy(70,380,"                                  Instructor        ");
    

return;
}


#endif