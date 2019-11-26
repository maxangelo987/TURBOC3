#ifndef parstree
#define parstree

#include<graphics.h>
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<process.h>

char strpar[100],*pr,pw,o;
char *palprime[10];

class parse_tree
{
public:
parse_tree()
	    {
	    }

~parse_tree(){}

void parse_tree_process();
};

void parse_tree::parse_tree_process()
{
int gd=DETECT, gm, c,i;
int y1,y2,y3,y4,y5,y6,p;
char *word[10];
clrscr();
initgraph(&gd,&gm,"C:\\turboc3\\bgi");

settextstyle(TRIPLEX_FONT, HORIZ_DIR,1);
setcolor(RED);
printf("Parse Tree for %s: ",palprime[o]);

word[0]="S";	
word[1]="E";
setbkcolor(YELLOW);
setfillstyle(1,BLUE);

// FIRST CIRCLE:
fillellipse(320,50,22,22);
line(320, 73, 320, 100);
line(310, 90, 320, 100);
line(330, 90, 320, 100);
outtextxy(320-4,50-10,word[0]);

y1=123;
y2=145;
y3=160;
y4=113;
y5=133;
y6=170;
// MULTIPLE CIRCLE DEPENDING FOR PALINDROME y1=193-123=70
// y2=215-145=70; y3=230-160;


		strcpy(strpar,palprime[o]);
		getch();
		p=strlen(strpar);

for (i=0;i<p;i++)
	{
	*pr=strpar[i];	
	fillellipse(320,y1,22,22);
	line(320, y2, 320, y6);
	line(310, y3, 320, y6);
	line(330, y3, 320, y6);
	outtextxy(320-4,y1-10,word[0]);

	fillellipse(390,y1,22,22);
	line(343, y1, 368, y1);
	line(368, y1, 353, y4);
	line(368, y1, 353, y5);
	outtextxy(390-4,y1-10,pr);
	
	fillellipse(250,y1,22,22);
	line(273, y1, 297, y1);
	line(273, y1, 287, y4);
	line(273, y1, 287, y5);
	outtextxy(250-4,y1-10,pr);
	y1=y1+70;
	y2=y2+70;
	y3=y3+70;
	y4=y4+70;
	y5=y5+70;
	y6=y6+70;
	getch();
	}

	fillellipse(320,y1,22,22);
	outtextxy(320-4,y1-10,word[1]);

getch();
clrscr();
closegraph();
return;
}

#endif