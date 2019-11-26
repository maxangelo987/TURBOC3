#ifndef display1
#define display1

#include<graphics.h>
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<process.h>

class display_1
{
public:
display_1()
	    {
	    }

~display_1(){}

void display_1_process();
};

void display_1::display_1_process()
{
int gd=DETECT, gm, c;
initgraph(&gd,&gm,"C:\\turboc3\\bgi");

setbkcolor(YELLOW);
settextstyle(SANS_SERIF_FONT, HORIZ_DIR,4);
setcolor(GREEN);
outtextxy(20,170,"Context Free Grammar w/ Parse Tree    ");
outtextxy(20,200,"    Palindromic Prime in Base 16       ");
setcolor(RED);
settextstyle(TRIPLEX_FONT, HORIZ_DIR,4);
outtextxy(60,430,"   Press any key to continue    ");
getch();

initgraph(&gd,&gm,"C:\\turboc3\\bgi");
settextstyle(TRIPLEX_FONT, HORIZ_DIR,2);
setbkcolor(RED);
setcolor(WHITE);
outtextxy(15,20,"A number is called a Palindromic Prime if the number is   ");
outtextxy(15,50," a palindrome and also a prime. We can use this problem   ");
outtextxy(15,80,"  in different base. In my program, I used base of 16.     ");
outtextxy(15,110,"  Therefore, if the hex is palindrome it converts into ");
outtextxy(15,140,"       decimal and check if it is a prime number. ");
outtextxy(15,170,"        If it is, then it is a PALINROMIC PRIME.");
settextstyle(TRIPLEX_FONT, HORIZ_DIR,1);
setcolor(YELLOW);
outtextxy(15,230,"Grammar: {A16=a^n*b*c^m | where n=m and A10%j!=0, j=2<A10} ");
outtextxy(15,270,"         let a||b = {0 1 2 3 4 5 6 7 8 9 A B C D E F} ");
outtextxy(15,300,"Production: S=>LSL | E ");
outtextxy(15,330,"         let L = {0 1 2 3 4 5 6 7 8 9 A B C D E F} ");

setcolor(GREEN);
settextstyle(TRIPLEX_FONT, HORIZ_DIR,4);
outtextxy(70,430,"   Press any key to continue    ");
getch();


initgraph(&gd,&gm,"C:\\turboc3\\bgi");
setbkcolor(GREEN);
setcolor(YELLOW);
settextstyle(TRIPLEX_FONT, HORIZ_DIR,1);
outtextxy(10,60,"ENTER HEXADECIMAL NUMBER: ");
outtextxy(10,80,"EX: 1B1 is Palindrome and its conversion is 433 and 433 is prime. ");
setcolor(GREEN);
gotoxy(10,8);
printf("<HEXADECIMAL NUMBER>:");
    

getch();
return;
}


#endif