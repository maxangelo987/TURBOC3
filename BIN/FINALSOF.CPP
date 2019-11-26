#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <time.h>
#include <bios.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define ESC 27
#define YES 1
#define NO 0

void *p;
size_t area;
//	Matrix of board

//------------------------------------------------------------------------
//				Function Prototypes
//------------------------------------------------------------------------
void cong();
void loading();
void Marble(int x,int y,int c);
void G();
int check();
int GetXY(int X,int Y);
int GetBoard(int X,int Y);
void SetBoard(int X,int Y,int element);
void Blink(int x,int y,int c);
void DrawBoard();
int MakeMove(int X,int Y);
void Init();
int finish();
void win(char *text,int sx,int sy,int ex,int ey,int ck);
void winp(int sx,int sy,int ex,int ey,int state);
void Menu();
void LCD(int left,int top,int NUM);
void Lcd(int x,int y,int n);
void Intro();
void Drawborder(int x,int y);
void Background();
int mydelay(float);
int mybar(int sx,int sy,int ex,int ey);
void easybrain();
int x=320,y=220,emarble=11,marble_color=12;
int eboard[7][7]=
{
	{-1,-1,-1,-1,-1,-1,-1},
	{-1,-1,1,1,1,1,-1},
	{-1,-1,1,1,1,1,-1},
	{-1,-1,1,1,1,1,-1},
	{-1,-1,-1,-1,-1,-1,-1},
	{-1,-1,-1,-1,-1,-1,-1},
	{-1,-1,-1,-1,-1,-1,-1}
    };
 //level 2
int mx=320,my=220,mmarble=29,mmarble_color=12;
void *mp;
size_t marea;
//	Matrix of board
int mboard[7][7]=
{
	{-1, 1,1,1,1,1,-1},
	{-1, 1,1,1,1,1,-1},
	{-1, 1,1,1,1,1,-1},
	{-1, 1,1,1,1,1,-1},
	{-1, 1,1,1,1,1,-1},
	{-1, 1,1,1,1,1,-1},
	{-1, -1,-1,-1,-1,-1,-1}
};
void mMarble(int mx,int my,int c);
void mG();
int mcheck();
int mGetXY(int X,int Y);
int mGetBoard(int X,int Y);
void mSetBoard(int X,int Y,int element);
void mBlink(int x,int y,int c);
void mDrawBoard();
int mMakeMove(int X,int Y);
void mInit();
int mfinish();
void mwin(char *text,int sx,int sy,int ex,int ey,int ck);
void mwinp(int sx,int sy,int ex,int ey,int state);
void mMenu();
void mLCD(int left,int top,int NUM);
void mLcd(int x,int y,int n);
void mIntro();
void mDrawborder(int x,int y);
void mBackground();
void mediumbrain();
//level 3
void *hp;
size_t harea;
void hMarble(int hx,int hy,int c);
void hG();
int hcheck();
int hGetXY(int X,int Y);
int hGetBoard(int X,int Y);
void hSetBoard(int X,int Y,int element);
void hBlink(int hx,int hy,int c);
void hDrawBoard();
int hMakeMove(int X,int Y);
void hInit();
int hfinish();
void hwin(char *text,int sx,int sy,int ex,int ey,int ck);
void hwinp(int sx,int sy,int ex,int ey,int state);
void hMenu();
void hLCD(int left,int top,int NUM);
void hLcd(int hx,int hy,int n);
void hDrawborder(int hx,int hy);
void hBackground();
int hx=320,hy=220,hmarble=32,hmarble_color=12;
int hboard[7][7]=
{
	{-1,-1,1,1,1,-1,-1},
	{-1,-1,1,1,1,-1,-1},
	{ 1, 1,1,1,1, 1, 1},
	{ 1, 1,1,1,1, 1, 1},
	{ 1, 1,1,1,1, 1, 1},
	{-1,-1,1,1,1,-1,-1},
	{-1,-1,1,1,1,-1,-1}
};
void hardbrain();
//------------------------------------------------------------------------
//				Main Function
//------------------------------------------------------------------------
void main()
{
  G();
 //  cong();
   easybrain();
   getch();
}
void easybrain()
{
   int i;
   G();
 //  cleardevice();
   Intro();
   Background();
   DrawBoard();
   Marble(320,220,0);
   eboard[3][3]=0;
   Init();
   setcolor(0);
   for(i=0;i<=220;i++)
   {
   rectangle(0+i,0+i,640-i,480-i);
   delay(10);
   }
   closegraph();
   getch();
}
void Marble(int x,int y,int c)
{
   setfillstyle(1,c);
   setcolor(c);
   fillellipse(x,y,8,8);
   if(c!=0)
   {
   if(c==15){setcolor(7);setfillstyle(1,7);}
   else {setfillstyle(1,15);setcolor(15);}
   fillellipse(x+3,y-2,1,2);
   }
}
int mydelay(float secs)
{
	clock_t start, end;
	start = clock();
	do
	{
		end = clock();
		if(kbhit()) break;
	}while(((end - start)/CLK_TCK)<secs);
	return 0;
}
void Intro()
{
   int i,e,c=150;
   char pattern[8] ={0xfe,0xbc,0xda,0xe4,0xe2,0xc0,0x88,0x00};
   setfillpattern(pattern,1);
   bar(0,0,640,480);
   settextstyle(3,0,5);
   setcolor(14);
   outtextxy(210,140,"BRAINVITA");
   settextstyle(2,0,5);
   setcolor(15);
   outtextxy(250,200,"BY : wattymjc");
   settextstyle(1,0,6);
   setcolor(5);
   outtextxy(230,280,"PLAY");
   getch();
   setcolor(0);
//   loading();
   for(e=0;e<5;e++)
 {
  for(i=50;i<80;i++)
  {
    setcolor(4);
    settextstyle(SMALL_FONT, HORIZ_DIR, 10);
    outtextxy(x,y,"Loading...");
    settextstyle(SMALL_FONT, HORIZ_DIR, 5);
    outtextxy(x+5,y+5,"Ready... ");
    circle(x,y,i);
    circle(x,y,c);
    c--;
    delay(10);
    cleardevice();
  }
  delay(100);
  }
    // win("BRAINVITA",1,1,638,478,1);*/
}
void Drawborder(int x,int y)
{
   setwritemode(COPY_PUT);
   setcolor(0);
   line(x+60,y-20,x+180,y-20);//       __
   line(x+60,y+60,x+60,y-20);//      |
   line(x-40,y+60,x+60,y+60);//   __
   line(x-40,y+60,x-40,y+180);// |
   setcolor(15);
   line(x-40,y+180,x+60,y+180);// __
   setcolor(0);
   line(x+60,y+180,x+60,y+280);//   |
   setcolor(15);
   line(x+180,y-20,x+180,y+60);//        |
   setcolor(0);
   line(x+180,y+60,x+290,y+60);//         __
   setcolor(15);
   line(x+290,y+60,x+290,y+180);//          |
   line(x+180,y+180,x+290,y+180);//       __
   line(x+180,y+180,x+180,y+280);//      |
   line(x+180,y+280,x+60,y+280);//    __
   setwritemode(XOR_PUT);
}

void Background()
{
   int i;
   setfillstyle(1,3);
   bar(0,0,640,480);
   for(i=0;i<=15;i++)
   {
   setcolor(i);
   rectangle(0+i,0+i,640-i,480-i);
   }
  win("LEVEL 1",145,45,505,400,1);
//  winp(159,79,491,381,1);
  win("Keys",24,45,135,290,1);
  win("Help !",510,45,625,250,1);
  setfillstyle(1,1);
  bar(35,75,125,280);
  bar(520,75,618,240);
  winp(35,75,125,280,1);
  winp(520,75,618,240,1);
  setcolor(5);
  settextstyle(2,0,4);
  outtextxy(42,80,"Keys used");
  setcolor(15);
  outtextxy(42,100,"+ or- : color");
  outtextxy(47,120,"/\  : Up");
  outtextxy(47,140,"\/  : Down");
  outtextxy(42,160,"<- : Left");
  outtextxy(42,180,"-> : Right");
  outtextxy(42,200,"Enter : Pick");
  outtextxy(42,220,"Esc : Exit");
  line(47,120,50,123);
  line(47,120,43,123);
  line(47,140,50,143);
  line(47,140,43,143);
  outtextxy(523,80,"Use Arrow Keys");
  outtextxy(523,100,"to move around");
  outtextxy(523,120,"then press enter");
  outtextxy(523,140,"to select any");
  outtextxy(523,160,"marble,then jump");
  outtextxy(523,180,"over another to");
  outtextxy(523,200,"remove it.");
  win("",190,410,480,460,0);
  setfillstyle(1,1);
  bar(200,420,470,450);
  settextstyle(1,0,3);
  setcolor(5);
  outtextxy(220,420,"Marbles :");
}

//------------------------------------------------------------------------
//			Draw The Whole Board on Screen
//------------------------------------------------------------------------

void DrawBoard()
{
   int i,j,x=200,y=100;
   x=200;y=100;
   setfillstyle(1,1);
   bar(x-40,y-20,x+290,y+280);
   setfillstyle(1,7);
   bar(x-41,y-21,x+290,y+60);
   bar(x+140,y-21,x+290,y+220);
   bar(x-41,y+20,x+20,y+290);
   bar(x+20,y+220,x+290,y+290);
   //Drawborder(x,y);
   //Drawborder(x+1,y+1);
   setfillstyle(1,12);
   setcolor(11);
   for(i=0;i<7;i++)
   {
	for(j=0;j<7;j++)
	{
	    if(eboard[j][i]!=-1)
	    {
	     if(eboard[j][i]==1)
	     Marble(x,y,marble_color);
	     if(eboard[j][i]==0)
	     Marble(x,y,0);
	    }
	    x+=40;
	}
	x=200;
	y+=40;
   }
   settextstyle(1,0,3);
}

//------------------------------------------------------------------------
//				Switch Into Graphics mode
//------------------------------------------------------------------------

void G()
{
   int gdriver = DETECT, gmode, errorcode;
   initgraph(&gdriver, &gmode, "c:\\turboc3\\bgi");
   errorcode = graphresult();
   if (errorcode != grOk)
   {
      printf("Graphics error: %s ", grapherrormsg(errorcode));
      exit(1);
   }
   area=imagesize(150,70,240,180);
   p=malloc(area);
   if(p==NULL)
   {closegraph();exit(1);}
}

//------------------------------------------------------------------------
//			Check the board if any move is possible
//------------------------------------------------------------------------

int check() // a know bug is there
{
   int i,j,flag;
   flag=0;
   for(i=0;i<7;i++)
   {
    for(j=0;j<7;j++)
    if(eboard[j][i]!=-1)
    {
	if(eboard[j][i]==1)
	{
		if(eboard[j+1][i]==1)
		{
			  if(eboard[j+2][i]==0)
			  flag++;

		}
		if(eboard[j-1][i]==1)
		{
			  if(eboard[j-2][i]==0)
			  flag++;

		}
		if(eboard[j][i+1]==1)
		{
			  if(eboard[j][i+2]==0)
			  flag++;

		}
		if(eboard[j][i-1]==1)
		{
			  if(eboard[j][i-2]==0)
			  flag++;

		}

	}
    }
   }
   //count marble
   emarble=0;
   for(i=0;i<7;i++)
   {
    for(j=0;j<7;j++)
    if(eboard[j][i]==1)
    emarble++;
   }
   return flag;
}

//------------------------------------------------------------------------
//      Give the current x,y position on board & find is it valid or not
//------------------------------------------------------------------------

int GetXY(int X,int Y)
{
   int i,j,x=200,y=100,flag=0;
   for(i=0;i<7;i++)
   {
	for(j=0;j<7;j++)
	{
	    if(eboard[j][i]!=-1)
	    {
	     if(x==X && y==Y)
	     flag=1;
	    }
	    x+=40;
	}
	x=200;
	y+=40;
   }
   return flag;
}

//------------------------------------------------------------------------
//		check current position is filled or not
//------------------------------------------------------------------------

int GetBoard(int X,int Y)
{
   int i,j,x=200,y=100,f=-1;
   for(i=0;i<7;i++)
   {
	for(j=0;j<7;j++)
	{
	    if(eboard[j][i]!=-1)
	    {
	     if(x==X && y==Y)
	     f=eboard[j][i];
	    }
	    x+=40;
	}
	x=200;
	y+=40;
   }
   return f;
}

//------------------------------------------------------------------------
//	Sets the board to 1 or 0 ,represents filled & empty respectively
//------------------------------------------------------------------------

void SetBoard(int X,int Y,int element)
{
   int i,j,x=200,y=100;
   for(i=0;i<7;i++)
   {
	for(j=0;j<7;j++)
	{
	    if(eboard[j][i]!=-1)
	    {
	     if(x==X && y==Y)
	     eboard[j][i]=element;
	    }
	    x+=40;
	}
	x=200;
	y+=40;
   }
}

//------------------------------------------------------------------------
//			Blinks the cursor or square
//------------------------------------------------------------------------

void Blink(int x,int y,int c)
{
 int i;
 setcolor(c);
 do
 {
	rectangle(x-10,y-10,x+10,y+10);
	rectangle(x-11,y-11,x+11,y+11);
	mydelay(0.5);
	rectangle(x-10,y-10,x+10,y+10);
	rectangle(x-11,y-11,x+11,y+11);
	mydelay(0.5);
 }while(!kbhit());
}

//------------------------------------------------------------------------
//		 When ENTER pressed check for conditions & perform task
//------------------------------------------------------------------------

int MakeMove(int X,int Y)
{
 int flag,key;
 flag=NO;
 if(marble_color==11)
 Marble(X,Y,9);
 else Marble(X,Y,11);
 key = bioskey(0);
 if(key==0x4800)//up
 {
	if(GetBoard(X,Y-80)==0 && GetBoard(X,Y-40)==1)
	{
		  Marble(X,Y,0);
		  SetBoard(X,Y,0);
		  Y-=40;
		  Marble(X,Y,0);
		  SetBoard(X,Y,0);
		  Y-=40;
		  SetBoard(X,Y,1);
		  y=Y;
		  flag=YES;
	}
 }
 if(key==0x5000)//down
 {
	if(GetBoard(X,Y+80)==0 && GetBoard(X,Y+40)==1)
	{
		  Marble(X,Y,0);
		  SetBoard(X,Y,0);
		  Y+=40;
		  Marble(X,Y,0);
		  SetBoard(X,Y,0);
		  Y+=40;
		  SetBoard(X,Y,1);
		  y=Y;
		  flag=YES;
	}
 }
 if(key==0x4b00)//left
 {
	if(GetBoard(X-80,Y)==0 && GetBoard(X-40,Y)==1)
	{
		  Marble(X,Y,0);
		  SetBoard(X,Y,0);
		  X-=40;
		  Marble(X,Y,0);
		  SetBoard(X,Y,0);
		  X-=40;
		  SetBoard(X,Y,1);
		  x=X;
		  flag=YES;
	}
 }
 if(key==0x4d00)//right
 {
	if(GetBoard(X+80,Y)==0 && GetBoard(X+40,Y)==1)
	{
		  Marble(X,Y,0);
		  SetBoard(X,Y,0);
		  X+=40;
		  Marble(X,Y,0);
		  SetBoard(X,Y,0);
		  X+=40;
		  SetBoard(X,Y,1);
		  x=X;
		  flag=YES;
	}
  }
  if(kbhit()) getch();
  setcolor(11);
  if(flag==YES)
  {
	Marble(X,Y,marble_color);
  }
  else//invalid key
  {
	Marble(X,Y,marble_color);
	sound(800);
	delay(100);
	nosound();
  }
  return flag;
}

//------------------------------------------------------------------------
//		Handles All the funtions & Perform desired move
//------------------------------------------------------------------------

void Init()
{
   int i,j,e=1;
   char ch;
   setwritemode(XOR_PUT);
   setcolor(15);
   while(e)
   {
    setfillstyle(1,11);
    Lcd(360,425,emarble);
    Blink(x,y,11);
    ch=getch();
    Lcd(360,425,emarble);
    if(ch==ESC) e=0;
    if(GetXY(x,y)==1)
    {
	switch(ch)
	{
		case    UP :if(GetXY(x,y-40)==1)
				if(y>100) y-=40;break;
		case  DOWN :if(GetXY(x,y+40)==1)
				if(y<340) y+=40;break;
		case  LEFT :if(GetXY(x-40,y)==1)
				if(x>200) x-=40;break;
		case RIGHT :if(GetXY(x+40,y)==1)
				if(x<440) x+=40;break;
		case ENTER :if(GetBoard(x,y)==1)
			    {
			     MakeMove(x,y);
			    }
			    break;
		case ESC   :e=0;break;
		case '+': marble_color++;
			 if(marble_color>15) marble_color=2;
			 DrawBoard();
			 break;
		case '-':marble_color--;
			 if(marble_color<2) marble_color=15;
			 DrawBoard();
			 break;
	}//switch
    }//if
   if(check()==0) e=finish();
   }//while
   setwritemode(COPY_PUT);
}

//------------------------------------------------------------------------
//			Display Final Screen
//------------------------------------------------------------------------

int finish()
{
    int i,j,f;
    char opt=0;
    setwritemode(COPY_PUT);
    f=0;
    for(i=0;i<7;i++)
    {
    for(j=0;j<7;j++)
    if(eboard[j][i]==1)
    f++;
    }
    Lcd(360,425,emarble);
//    f-=1;
    win("Done !",220,155,425,240,1);
    setcolor(0);
    settextstyle(1,0,1);
    switch(f)
    {
	case 1:outtextxy(230,180,"You Are Intelligent !");break;
	case 2:outtextxy(255,180,"    Wonderful !");break;
	case 3:outtextxy(255,180,"  Good Job !");break;
	case 4:outtextxy(255,180,"  Can be better !");break;
	case 5:outtextxy(230,180," You Need Practice !");break;
	case 6:outtextxy(230,180,"   Very Poor !");break;
	case 7:outtextxy(230,180," Very Very Poor !");break;
	default:outtextxy(255,180," Try Again !");break;
    }
    if(f==1)
    {
      loading();
      mediumbrain();
      f=
      1;
    }
    else
    getch();
    win("Exit ?",220,155,425,240,1);
    settextstyle(1,0,1);
    setcolor(1);
    outtextxy(240,180,"Play Again [y/n] :");
    opt=getch();
    setfillstyle(1,3);
    bar(17,402,624,464);
    if(opt=='y' || opt=='Y')
    {
     for(i=0;i<7;i++)
     {
	for(j=0;j<7;j++)
	if(eboard[j][i]!=-1) eboard[j][i]=1;
     }
     Marble(320,220,0);
     eboard[3][3]=0;
     emarble=11;
     Background();
     DrawBoard();
     f=1;
    }
    else f=0;
    setwritemode(XOR_PUT);
    return f;
}
void win(char *text,int sx,int sy,int ex,int ey,int ck)
{
   setfillstyle(1,12);
   bar(sx,sy,ex,ey);
   setfillstyle(1,12);
   setcolor(15);
   line(sx,sy,sx,ey);
   line(sx,sy,ex,sy);
   line(sx,sy,sx,ey);
   line(sx,sy,ex,sy);
   setcolor(0);
   line(ex,sy,ex,ey);
   line(ex,sy,ex,ey);
   line(sx,ey,ex,ey);
   line(sx,ey,ex,ey);
   if(ck==1)
   {
   settextstyle(0,0,0);
   setfillstyle(1,4);
   bar(sx+2,sy+3,ex-2,sy+18);
   setcolor(14);
   outtextxy(sx+5,sy+5,text);
   //for x
   setfillstyle(1,7);
   bar(ex-15,sy+4,ex-4,sy+15);
   setcolor(15);
   line(ex-15,sy+4,ex-4,sy+4);
   line(ex-15,sy+4,ex-15,sy+15);
   setcolor(1);
   line(ex-15,sy+15,ex-4,sy+15);
   line(ex-4,sy+4,ex-4,sy+15);
   setcolor(1);
   outtextxy(ex-13,sy+5,"x");
   setfillstyle(1,7);
   }
}
void winp(int sx,int sy,int ex,int ey,int state)
{
   if(state==1)
   {
   setcolor(1);
   line(sx,sy,sx,ey);
   line(sx,sy,ex,sy);
   line(sx,sy,sx,ey);
   line(sx,sy,ex,sy);
   setcolor(2);
   line(ex,sy,ex,ey);
   line(ex,sy,ex,ey);
   line(sx,ey,ex,ey);
   line(sx,ey,ex,ey);
  }
  else
  {
   setcolor(2);
   line(sx,sy,sx,ey);
   line(sx,sy,ex,sy);
   line(sx,sy,sx,ey);
   line(sx,sy,ex,sy);
   setcolor(1);
   line(ex,sy,ex,ey);
   line(ex,sy,ex,ey);
   line(sx,ey,ex,ey);
   line(sx,ey,ex,ey);
  }
}
void Lcd(int x,int y,int n)
{
 int a,b;
 if(n<10)
 {
 LCD(x,y,0);
 LCD(x+15,y,n);
 }
 else if(n<100)
 {
  a=n/10;b=n%10;
  LCD(x,y,a);
  LCD(x+15,y,b);
 }
}
void LCD(int left,int top,int NUM)
{
   int i;
//   int right=100, bottom=100;
   setcolor(10);

   switch(NUM)
   {
   case 1:
	  line(left+11,top+2,left+11,top+9);	//  |
	  line(left+11,top+11,left+11,top+18);	//  |
	  break;
   case 2:
	   line(left,top,left+10,top);		//--
	   line(left+11,top+2,left+11,top+9);	//  |
	   line(left+1,top+10,left+9,top+10);	//--
	   line(left-1,top+11,left-1,top+18);	//|
	   line(left,top+20,left+10,top+20);	//--
	   break;
   case 3:
	   line(left,top,left+10,top);		//--
	   line(left+11,top+2,left+11,top+9);	//  |
	   line(left+1,top+10,left+9,top+10);	//--
	   line(left+11,top+11,left+11,top+18);	//  |
	   line(left,top+20,left+10,top+20);	//--
	   break;
   case 4:
	   line(left-1,top+2,left-1,top+9);	//|
	   line(left+11,top+2,left+11,top+9);	//  |
	   line(left+1,top+10,left+9,top+10);	//--
	   line(left+11,top+11,left+11,top+18);	//  |
	   break;
   case 5:
	   line(left,top,left+10,top);		//--
	   line(left-1,top+2,left-1,top+9);	//|
	   line(left+1,top+10,left+9,top+10);	//--
	   line(left+11,top+11,left+11,top+18);	//  |
	   line(left,top+20,left+10,top+20);	//--
	   break;
   case 6:
	   line(left,top,left+10,top);		//--
	   line(left-1,top+2,left-1,top+9);	//|
	   line(left+1,top+10,left+9,top+10);	//--
	   line(left-1,top+11,left-1,top+18);	//|
	   line(left+11,top+11,left+11,top+18);	//  |
	   line(left,top+20,left+10,top+20);	//--
	   break;
   case 7:
	   line(left,top,left+10,top);		//--
	   line(left-1,top+2,left-1,top+9);	//|
	   line(left+11,top+2,left+11,top+9);	//  |
	   line(left+11,top+11,left+11,top+18);	//  |
	   break;
   case 8:
	   line(left,top,left+10,top);		//--
	   line(left-1,top+2,left-1,top+9);	//|
	   line(left+11,top+2,left+11,top+9);	//  |
	   line(left+1,top+10,left+9,top+10);	//--
	   line(left-1,top+11,left-1,top+18);	//|
	   line(left+11,top+11,left+11,top+18);	//  |
	   line(left,top+20,left+10,top+20);	//--
	   break;
   case 9:
	   line(left,top,left+10,top);		//--
	   line(left-1,top+2,left-1,top+9);	//|
	   line(left+11,top+2,left+11,top+9);	//  |
	   line(left+1,top+10,left+9,top+10);	//--
	   line(left+11,top+11,left+11,top+18);	//  |
	   line(left,top+20,left+10,top+20);	//--
	   break;
   case 0:
	   line(left,top,left+10,top);		//--
	   line(left-1,top+2,left-1,top+9);	//|
	   line(left+11,top+2,left+11,top+9);	//  |
	   line(left-1,top+11,left-1,top+18);	//|
	   line(left+11,top+11,left+11,top+18);	//  |
	   line(left,top+20,left+10,top+20);	//--
	   break;
   }
}
//level 2
void mediumbrain()
{
   mG();
   cleardevice();
   mBackground();
   mDrawBoard();
   mMarble(320,220,0);
   mboard[3][3]=0;
   mInit();
   closegraph();
   getch();
}
void mMarble(int mx,int my,int c)
{
   setfillstyle(1,c);
   setcolor(c);
   fillellipse(mx,my,8,8);
   if(c!=0)
   {
   if(c==15){setcolor(7);setfillstyle(1,7);}
   else {setfillstyle(1,15);setcolor(15);}
   fillellipse(mx+3,my-2,1,2);
   }
}
void mmydelay(float secs)
{
	clock_t start, end;
	start = clock();
	do
	{
		end = clock();
		if(kbhit()) break;
	}while(((end - start)/CLK_TCK)<secs);
}
void mIntro()
{
   int i;
   char pattern[8] ={0xfe,0xbc,0xda,0xe4,0xe2,0xc0,0x88,0x00};
   setfillpattern(pattern,1);
   bar(0,0,640,480);
   settextstyle(3,0,5);
   setcolor(14);
   outtextxy(210,140,"BRAINVITA");
   settextstyle(2,0,5);
   setcolor(15);
   outtextxy(250,200,"BY : wattymjc");
   settextstyle(1,0,6);
   setcolor(5);
   outtextxy(230,280,"PLAY");
   getch();
   setcolor(0);
   for(i=0;i<=320;i++)
   {
   rectangle(0+i,0,640-i,480);
   delay(500);
   }
  //   win("BRAINVITA",1,1,638,478,1);
}
void mDrawborder(int mx,int my)
{
   setwritemode(COPY_PUT);
   setcolor(0);
   line(mx+60,my-20,mx+180,my-20);//       __
   line(mx+60,my+60,mx+60,my-20);//      |
   line(mx-40,my+60,mx+60,my+60);//   __
   line(mx-40,my+60,mx-40,my+180);// |
   setcolor(15);
   line(mx-40,my+180,mx+60,my+180);// __
   setcolor(0);
   line(mx+60,my+180,mx+60,my+280);//   |
   setcolor(15);
   line(mx+180,my-20,mx+180,my+60);//        |
   setcolor(0);
   line(mx+180,my+60,mx+290,my+60);//         __
   setcolor(15);
   line(mx+290,my+60,mx+290,my+180);//          |
   line(mx+180,my+180,mx+290,my+180);//       __
   line(mx+180,my+180,mx+180,my+280);//      |
   line(mx+180,my+280,mx+60,my+280);//    __
   setwritemode(XOR_PUT);
}

void mBackground()
{
   int i;
   setfillstyle(1,3);
   bar(0,0,640,480);
   for(i=0;i<=15;i++)
   {
   setcolor(i);
   rectangle(0+i,0+i,640-i,480-i);
   }
  mwin("LEVEL 2",145,45,505,400,1);
//  winp(159,79,491,381,1);
  mwin("Keys",24,45,135,290,1);
  mwin("Help !",510,45,625,250,1);
  setfillstyle(1,1);
  bar(35,75,125,280);
  bar(520,75,618,240);
  mwinp(35,75,125,280,1);
  mwinp(520,75,618,240,1);
  setcolor(5);
  settextstyle(2,0,4);
  outtextxy(42,80,"Keys used");
  setcolor(15);
  outtextxy(42,100,"+ or- : color");
  outtextxy(47,120,"?  : Up");
  outtextxy(47,140,"?  : Down");
  outtextxy(42,160,"<- : Left");
  outtextxy(42,180,"-> : Right");
  outtextxy(42,200,"Enter : Pick");
  outtextxy(42,220,"Esc : Exit");
  line(47,120,50,123);
  line(47,120,43,123);
  line(47,140,50,143);
  line(47,140,43,143);
  outtextxy(523,80,"Use Arrow Keys");
  outtextxy(523,100,"to move around");
  outtextxy(523,120,"then press enter");
  outtextxy(523,140,"to select any");
  outtextxy(523,160,"marble,then jump");
  outtextxy(523,180,"over another to");
  outtextxy(523,200,"remove it.");
  mwin("",190,410,480,460,0);
  setfillstyle(1,1);
  bar(200,420,470,450);
  settextstyle(1,0,3);
  setcolor(5);
  outtextxy(220,420,"Marbles :");
}

//------------------------------------------------------------------------
//			Draw The Whole Board on Screen
//------------------------------------------------------------------------

void mDrawBoard()
{
   int i,j,x=200,y=100;
   x=200;y=100;
   setfillstyle(1,1);
   bar(x-40,y-20,x+290,y+280);
   setfillstyle(1,7);
   bar(x-41,y-21,x+240,y+20);
   bar(x+220,y-21,x+290,y+220);
    bar(x-41,y+20,x-15,y+290);
   bar(x-15,y+220,x+290,y+290);
   //Drawborder(x,y);
   //Drawborder(x+1,y+1);
   setfillstyle(1,12);
   setcolor(11);
   for(i=0;i<7;i++)
   {
	for(j=0;j<7;j++)
	{
	    if(mboard[j][i]!=-1)
	    {
	     if(mboard[j][i]==1)
	     mMarble(x,y,mmarble_color);
	     if(mboard[j][i]==0)
	     mMarble(x,y,0);
	    }
	    x+=40;
	}
	x=200;
	y+=40;
   }
   settextstyle(1,0,3);
}

//------------------------------------------------------------------------
//				Switch Into Graphics mode
//------------------------------------------------------------------------

void mG()
{
   int gdriver = DETECT, gmode, errorcode;
   initgraph(&gdriver, &gmode, "c:\\turboc3\\bgi");
   errorcode = graphresult();
   if (errorcode != grOk)
   {
      printf("Graphics error: %s", grapherrormsg(errorcode));
      exit(1);
   }
   marea=imagesize(150,70,240,180);
   mp=malloc(marea);
   if(mp==NULL)
   {closegraph();exit(1);}
}

//------------------------------------------------------------------------
//			Check the board if any move is possible
//------------------------------------------------------------------------

int mcheck() // a know bug is there
{
   int i,j,flag;
   flag=0;
   for(i=0;i<7;i++)
   {
    for(j=0;j<7;j++)
    if(mboard[j][i]!=-1)
    {
	if(mboard[j][i]==1)
	{
		if(mboard[j+1][i]==1)
		{
			  if(mboard[j+2][i]==0)
			  flag++;

		}
		if(mboard[j-1][i]==1)
		{
			  if(mboard[j-2][i]==0)
			  flag++;

		}
		if(mboard[j][i+1]==1)
		{
			  if(mboard[j][i+2]==0)
			  flag++;

		}
		if(mboard[j][i-1]==1)
		{
			  if(mboard[j][i-2]==0)
			  flag++;

		}

	}
    }
   }
   //count marble
   mmarble=0;
   for(i=0;i<7;i++)
   {
    for(j=0;j<7;j++)
    if(mboard[j][i]==1)
    mmarble++;
   }
   return flag;
}

//------------------------------------------------------------------------
//      Give the current x,y position on board & find is it valid or not
//------------------------------------------------------------------------

int mGetXY(int X,int Y)
{
   int i,j,x=200,y=100,flag=0;
   for(i=0;i<7;i++)
   {
	for(j=0;j<7;j++)
	{
	    if(mboard[j][i]!=-1)
	    {
	     if(x==X && y==Y)
	     flag=1;
	    }
	    x+=40;
	}
	x=200;
	y+=40;
   }
   return flag;
}

//------------------------------------------------------------------------
//		check current position is filled or not
//------------------------------------------------------------------------

int mGetBoard(int X,int Y)
{
   int i,j,x=200,y=100,f=-1;
   for(i=0;i<7;i++)
   {
	for(j=0;j<7;j++)
	{
	    if(mboard[j][i]!=-1)
	    {
	     if(x==X && y==Y)
	     f=mboard[j][i];
	    }
	    x+=40;
	}
	x=200;
	y+=40;
   }
   return f;
}

//------------------------------------------------------------------------
//	Sets the board to 1 or 0 ,represents filled & empty respectively
//------------------------------------------------------------------------

void mSetBoard(int X,int Y,int element)
{
   int i,j,x=200,y=100;
   for(i=0;i<7;i++)
   {
	for(j=0;j<7;j++)
	{
	    if(mboard[j][i]!=-1)
	    {
	     if(x==X && y==Y)
	     mboard[j][i]=element;
	    }
	    x+=40;
	}
	x=200;
	y+=40;
   }
}

//------------------------------------------------------------------------
//			Blinks the cursor or square
//------------------------------------------------------------------------

void mBlink(int mx,int my,int c)
{
 int i;
 setcolor(c);
 do
 {
	rectangle(mx-10,my-10,mx+10,my+10);
	rectangle(mx-11,my-11,mx+11,my+11);
	mmydelay(0.5);
	rectangle(mx-10,my-10,mx+10,my+10);
	rectangle(mx-11,my-11,mx+11,my+11);
	mmydelay(0.5);
 }while(!kbhit());
}

//------------------------------------------------------------------------
//		 When ENTER pressed check for conditions & perform task
//------------------------------------------------------------------------

int mMakeMove(int X,int Y)
{
 int flag,key;
 flag=NO;
 if(mmarble_color==11)
 mMarble(X,Y,9);
 else mMarble(X,Y,11);
 key = bioskey(0);
 if(key==0x4800)//up
 {
	if(mGetBoard(X,Y-80)==0 && mGetBoard(X,Y-40)==1)
	{
		  mMarble(X,Y,0);
		  mSetBoard(X,Y,0);
		  Y-=40;
		  mMarble(X,Y,0);
		  mSetBoard(X,Y,0);
		  Y-=40;
		  mSetBoard(X,Y,1);
		  my=Y;
		  flag=YES;
	}
 }
 if(key==0x5000)//down
 {
	if(mGetBoard(X,Y+80)==0 && mGetBoard(X,Y+40)==1)
	{
		  mMarble(X,Y,0);
		  mSetBoard(X,Y,0);
		  Y+=40;
		  mMarble(X,Y,0);
		  mSetBoard(X,Y,0);
		  Y+=40;
		  mSetBoard(X,Y,1);
		  my=Y;
		  flag=YES;
	}
 }
 if(key==0x4b00)//left
 {
	if(mGetBoard(X-80,Y)==0 && mGetBoard(X-40,Y)==1)
	{
		  mMarble(X,Y,0);
		  mSetBoard(X,Y,0);
		  X-=40;
		  mMarble(X,Y,0);
		  mSetBoard(X,Y,0);
		  X-=40;
		  mSetBoard(X,Y,1);
		  mx=X;
		  flag=YES;
	}
 }
 if(key==0x4d00)//right
 {
	if(mGetBoard(X+80,Y)==0 && mGetBoard(X+40,Y)==1)
	{
		  mMarble(X,Y,0);
		  mSetBoard(X,Y,0);
		  X+=40;
		  mMarble(X,Y,0);
		  mSetBoard(X,Y,0);
		  X+=40;
		  mSetBoard(X,Y,1);
		  mx=X;
		  flag=YES;
	}
  }
  if(kbhit()) getch();
  setcolor(11);
  if(flag==YES)
  {
	mMarble(X,Y,mmarble_color);
  }
  else//invalid key
  {
	mMarble(X,Y,mmarble_color);
	sound(800);
	delay(100);
	nosound();
  }
  return flag;
}

//------------------------------------------------------------------------
//		Handles All the funtions & Perform desired move
//------------------------------------------------------------------------

void mInit()
{
   int i,j,e=1;
   char ch;
   setwritemode(XOR_PUT);
   setcolor(15);
   while(e)
   {
    setfillstyle(1,11);
    mLcd(360,425,mmarble);
    mBlink(mx,my,11);
    ch=getch();
    mLcd(360,425,mmarble);
    if(ch==ESC) e=0;
    if(mGetXY(mx,my)==1)
    {
	switch(ch)
	{
		case    UP :if(mGetXY(mx,my-40)==1)
				if(my>100) my-=40;break;
		case  DOWN :if(mGetXY(mx,my+40)==1)
				if(my<340) my+=40;break;
		case  LEFT :if(mGetXY(mx-40,my)==1)
				if(mx>200) mx-=40;break;
		case RIGHT :if(mGetXY(mx+40,my)==1)
				if(mx<440) mx+=40;break;
		case ENTER :if(mGetBoard(mx,my)==1)
			    {
			     mMakeMove(mx,my);
			    }
			    break;
		case ESC   :e=0;break;
		case '+': mmarble_color++;
			 if(mmarble_color>15) mmarble_color=2;
			 mDrawBoard();
			 break;
		case '-':mmarble_color--;
			 if(mmarble_color<2) mmarble_color=15;
			 mDrawBoard();
			 break;
	}//switch
    }//if
   if(mcheck()==0) e=mfinish();
   }//while
   setwritemode(COPY_PUT);
}

//------------------------------------------------------------------------
//			Display Final Screen
//------------------------------------------------------------------------

int mfinish()
{
    int i,j,f;
    char opt=0;
    setwritemode(COPY_PUT);
    f=0;
    for(i=0;i<7;i++)
    {
    for(j=0;j<7;j++)
    if(mboard[j][i]==1)
    f++;
    }
    mLcd(360,425,mmarble);
//    f-=1;
    mwin("Done !",220,155,425,240,1);
    setcolor(0);
    settextstyle(1,0,1);
    switch(f)
    {
	case 1:outtextxy(230,180,"You Are Intelligent !");break;
	case 2:outtextxy(255,180,"    Wonderful !");break;
	case 3:outtextxy(255,180,"  Good Job !");break;
	case 4:outtextxy(255,180,"  Can be better !");break;
	case 5:outtextxy(230,180," You Need Practice !");break;
	case 6:outtextxy(230,180,"   Very Poor !");break;
	case 7:outtextxy(230,180," Very Very Poor !");break;
	default:outtextxy(255,180," Try Again !");break;
    }
//    gotoxy(1,1);printf("%d",f);
    if(f==1)
    {
       loading();
       hardbrain();
       f=1;
    }
    else
    getch();
    mwin("Exit ?",220,155,425,240,1);
    settextstyle(1,0,1);
    setcolor(1);
    outtextxy(240,180,"Play Again [y/n] :");
    opt=getch();
    setfillstyle(1,3);
    bar(17,402,624,464);
    if(opt=='y' || opt=='Y')
    {
     for(i=0;i<7;i++)
     {
	for(j=0;j<7;j++)
	if(mboard[j][i]!=-1) mboard[j][i]=1;
     }
     mMarble(320,220,0);
     mboard[3][3]=0;
     mmarble=29;
     mBackground();
     mDrawBoard();
     f=1;
    }
    else f=0;
    setwritemode(XOR_PUT);
    return f;
}
void mwin(char *text,int sx,int sy,int ex,int ey,int ck)
{
   setfillstyle(1,12);
   bar(sx,sy,ex,ey);
   setfillstyle(1,12);
   setcolor(15);
   line(sx,sy,sx,ey);
   line(sx,sy,ex,sy);
   line(sx,sy,sx,ey);
   line(sx,sy,ex,sy);
   setcolor(0);
   line(ex,sy,ex,ey);
   line(ex,sy,ex,ey);
   line(sx,ey,ex,ey);
   line(sx,ey,ex,ey);
   if(ck==1)
   {
   settextstyle(0,0,0);
   setfillstyle(1,4);
   bar(sx+2,sy+3,ex-2,sy+18);
   setcolor(14);
   outtextxy(sx+5,sy+5,text);
   //for x
   setfillstyle(1,7);
   bar(ex-15,sy+4,ex-4,sy+15);
   setcolor(15);
   line(ex-15,sy+4,ex-4,sy+4);
   line(ex-15,sy+4,ex-15,sy+15);
   setcolor(1);
   line(ex-15,sy+15,ex-4,sy+15);
   line(ex-4,sy+4,ex-4,sy+15);
   setcolor(1);
   outtextxy(ex-13,sy+5,"x");
   setfillstyle(1,7);
   }
}
void mwinp(int sx,int sy,int ex,int ey,int state)
{
   if(state==1)
   {
   setcolor(1);
   line(sx,sy,sx,ey);
   line(sx,sy,ex,sy);
   line(sx,sy,sx,ey);
   line(sx,sy,ex,sy);
   setcolor(2);
   line(ex,sy,ex,ey);
   line(ex,sy,ex,ey);
   line(sx,ey,ex,ey);
   line(sx,ey,ex,ey);
  }
  else
  {
   setcolor(2);
   line(sx,sy,sx,ey);
   line(sx,sy,ex,sy);
   line(sx,sy,sx,ey);
   line(sx,sy,ex,sy);
   setcolor(1);
   line(ex,sy,ex,ey);
   line(ex,sy,ex,ey);
   line(sx,ey,ex,ey);
   line(sx,ey,ex,ey);
  }
}
void mLcd(int x,int y,int n)
{
 int a,b;
 if(n<10)
 {
 mLCD(x,y,0);
 mLCD(x+15,y,n);
 }
 else if(n<100)
 {
  a=n/10;b=n%10;
  mLCD(x,y,a);
  mLCD(x+15,y,b);
 }
}
void mLCD(int left,int top,int NUM)
{
   int i;
//   int right=100, bottom=100;
   setcolor(10);

   switch(NUM)
   {
   case 1:
	  line(left+11,top+2,left+11,top+9);	//  |
	  line(left+11,top+11,left+11,top+18);	//  |
	  break;
   case 2:
	   line(left,top,left+10,top);		//--
	   line(left+11,top+2,left+11,top+9);	//  |
	   line(left+1,top+10,left+9,top+10);	//--
	   line(left-1,top+11,left-1,top+18);	//|
	   line(left,top+20,left+10,top+20);	//--
	   break;
   case 3:
	   line(left,top,left+10,top);		//--
	   line(left+11,top+2,left+11,top+9);	//  |
	   line(left+1,top+10,left+9,top+10);	//--
	   line(left+11,top+11,left+11,top+18);	//  |
	   line(left,top+20,left+10,top+20);	//--
	   break;
   case 4:
	   line(left-1,top+2,left-1,top+9);	//|
	   line(left+11,top+2,left+11,top+9);	//  |
	   line(left+1,top+10,left+9,top+10);	//--
	   line(left+11,top+11,left+11,top+18);	//  |
	   break;
   case 5:
	   line(left,top,left+10,top);		//--
	   line(left-1,top+2,left-1,top+9);	//|
	   line(left+1,top+10,left+9,top+10);	//--
	   line(left+11,top+11,left+11,top+18);	//  |
	   line(left,top+20,left+10,top+20);	//--
	   break;
   case 6:
	   line(left,top,left+10,top);		//--
	   line(left-1,top+2,left-1,top+9);	//|
	   line(left+1,top+10,left+9,top+10);	//--
	   line(left-1,top+11,left-1,top+18);	//|
	   line(left+11,top+11,left+11,top+18);	//  |
	   line(left,top+20,left+10,top+20);	//--
	   break;
   case 7:
	   line(left,top,left+10,top);		//--
	   line(left-1,top+2,left-1,top+9);	//|
	   line(left+11,top+2,left+11,top+9);	//  |
	   line(left+11,top+11,left+11,top+18);	//  |
	   break;
   case 8:
	   line(left,top,left+10,top);		//--
	   line(left-1,top+2,left-1,top+9);	//|
	   line(left+11,top+2,left+11,top+9);	//  |
	   line(left+1,top+10,left+9,top+10);	//--
	   line(left-1,top+11,left-1,top+18);	//|
	   line(left+11,top+11,left+11,top+18);	//  |
	   line(left,top+20,left+10,top+20);	//--
	   break;
   case 9:
	   line(left,top,left+10,top);		//--
	   line(left-1,top+2,left-1,top+9);	//|
	   line(left+11,top+2,left+11,top+9);	//  |
	   line(left+1,top+10,left+9,top+10);	//--
	   line(left+11,top+11,left+11,top+18);	//  |
	   line(left,top+20,left+10,top+20);	//--
	   break;
   case 0:
	   line(left,top,left+10,top);		//--
	   line(left-1,top+2,left-1,top+9);	//|
	   line(left+11,top+2,left+11,top+9);	//  |
	   line(left-1,top+11,left-1,top+18);	//|
	   line(left+11,top+11,left+11,top+18);	//  |
	   line(left,top+20,left+10,top+20);	//--
	   break;
   }
}

//level 3
void hardbrain()
{
   hG();
   cleardevice();
   hBackground();
   hDrawBoard();
   hMarble(320,220,0);
   hboard[3][3]=0;
   hInit();
   closegraph();
   getch();
}
void hMarble(int hx,int hy,int c)
{
   setfillstyle(1,c);
   setcolor(c);
   fillellipse(hx,hy,8,8);
   if(c!=0)
   {
   if(c==15){setcolor(7);setfillstyle(1,7);}
   else {setfillstyle(1,15);setcolor(15);}
   fillellipse(hx+3,hy-2,1,2);
   }
}
void hmydelay(float secs)
{
	clock_t start, end;
	start = clock();
	do
	{
		end = clock();
		if(kbhit()) break;
	}while(((end - start)/CLK_TCK)<secs);
}
void hDrawborder(int hx,int hy)
{
   setwritemode(COPY_PUT);
   setcolor(0);
   line(hx+60,hy-20,hx+180,hy-20);//       __
   line(hx+60,hy+60,hx+60,hy-20);//      |
   line(hx-40,hy+60,hx+60,hy+60);//   __
   line(hx-40,hy+60,hx-40,hy+180);// |
   setcolor(15);
   line(hx-40,hy+180,hx+60,hy+180);// __
   setcolor(0);
   line(hx+60,hy+180,hx+60,hy+280);//   |
   setcolor(15);
   line(hx+180,hy-20,hx+180,hy+60);//        |
   setcolor(0);
   line(hx+180,hy+60,hx+290,hy+60);//         __
   setcolor(15);
   line(hx+290,hy+60,hx+290,hy+180);//          |
   line(hx+180,hy+180,hx+290,hy+180);//       __
   line(hx+180,hy+180,hx+180,hy+280);//      |
   line(hx+180,hy+280,hx+60,hy+280);//    __
   setwritemode(XOR_PUT);
}

void hBackground()
{
   int i;
   setfillstyle(1,3);
   bar(0,0,640,480);
   for(i=0;i<=15;i++)
   {
   setcolor(i);
   rectangle(0+i,0+i,640-i,480-i);
   }
  hwin("LEVEL 3",145,45,505,400,1);
//  winp(159,79,491,381,1);
  hwin("Keys",24,45,135,290,1);
  hwin("Help !",510,45,625,250,1);
  setfillstyle(1,1);
  bar(35,75,125,280);
  bar(520,75,618,240);
  hwinp(35,75,125,280,1);
  hwinp(520,75,618,240,1);
  setcolor(5);
  settextstyle(2,0,4);
  outtextxy(42,80,"Keys used");
  setcolor(15);
  outtextxy(42,100,"+ or- : color");
  outtextxy(47,120,"?  : Up");
  outtextxy(47,140,"?  : Down");
  outtextxy(42,160,"<- : Left");
  outtextxy(42,180,"-> : Right");
  outtextxy(42,200,"Enter : Pick");
  outtextxy(42,220,"Esc : Exit");
  line(47,120,50,123);
  line(47,120,43,123);
  line(47,140,50,143);
  line(47,140,43,143);
  outtextxy(523,80,"Use Arrow Keys");
  outtextxy(523,100,"to move around");
  outtextxy(523,120,"then press enter");
  outtextxy(523,140,"to select any");
  outtextxy(523,160,"marble,then jump");
  outtextxy(523,180,"over another to");
  outtextxy(523,200,"remove it.");
  hwin("",190,410,480,460,0);
  setfillstyle(1,1);
  bar(200,420,470,450);
  settextstyle(1,0,3);
  setcolor(5);
  outtextxy(220,420,"Marbles :");
}

//------------------------------------------------------------------------
//			Draw The Whole Board on Screen
//------------------------------------------------------------------------

void hDrawBoard()
{
   int i,j,x=200,y=100;
   x=200;y=100;
   setfillstyle(1,1);
   bar(x-40,y-20,x+290,y+280);
   setfillstyle(1,7);
   bar(x-41,y-21,x+60,y+60);
   bar(x+180,y-21,x+290,y+60);
   bar(x-41,y+180,x+60,y+290);
   bar(x+180,y+180,x+290,y+290);
   hDrawborder(x,y);
   hDrawborder(x+1,y+1);
   setfillstyle(1,12);
   setcolor(11);
   for(i=0;i<7;i++)
   {
	for(j=0;j<7;j++)
	{
	    if(hboard[j][i]!=-1)
	    {
	     if(hboard[j][i]==1)
	     hMarble(x,y,hmarble_color);
	     if(hboard[j][i]==0)
	     hMarble(x,y,0);
	    }
	    x+=40;
	}
	x=200;
	y+=40;
   }
   settextstyle(1,0,3);
}

//------------------------------------------------------------------------
//				Switch Into Graphics mode
//------------------------------------------------------------------------

void hG()
{
   int gdriver = DETECT, gmode, errorcode;
   initgraph(&gdriver, &gmode, "c:\\turboc3\\bgi");
   errorcode = graphresult();
   if (errorcode != grOk)
   {
      printf("Graphics error: %s", grapherrormsg(errorcode));
      exit(1);
   }
   harea=imagesize(150,70,240,180);
   hp=malloc(harea);
   if(hp==NULL)
   {closegraph();exit(1);}
}

//------------------------------------------------------------------------
//			Check the board if any move is possible
//------------------------------------------------------------------------

int hcheck() // a know bug is there
{
   int i,j,flag;
   flag=0;
   for(i=0;i<7;i++)
   {
    for(j=0;j<7;j++)
    if(hboard[j][i]!=-1)
    {
	if(hboard[j][i]==1)
	{
		if(hboard[j+1][i]==1)
		{
			  if(hboard[j+2][i]==0)
			  flag++;

		}
		if(hboard[j-1][i]==1)
		{
			  if(hboard[j-2][i]==0)
			  flag++;

		}
		if(hboard[j][i+1]==1)
		{
			  if(hboard[j][i+2]==0)
			  flag++;

		}
		if(hboard[j][i-1]==1)
		{
			  if(hboard[j][i-2]==0)
			  flag++;

		}

	}
    }
   }
   //count marble
   hmarble=0;
   for(i=0;i<7;i++)
   {
    for(j=0;j<7;j++)
    if(hboard[j][i]==1)
    hmarble++;
   }
   return flag;
}

//------------------------------------------------------------------------
//      Give the current x,y position on board & find is it valid or not
//------------------------------------------------------------------------

int hGetXY(int X,int Y)
{
   int i,j,x=200,y=100,flag=0;
   for(i=0;i<7;i++)
   {
	for(j=0;j<7;j++)
	{
	    if(hboard[j][i]!=-1)
	    {
	     if(x==X && y==Y)
	     flag=1;
	    }
	    x+=40;
	}
	x=200;
	y+=40;
   }
   return flag;
}

//------------------------------------------------------------------------
//		check current position is filled or not
//------------------------------------------------------------------------

int hGetBoard(int X,int Y)
{
   int i,j,x=200,y=100,f=-1;
   for(i=0;i<7;i++)
   {
	for(j=0;j<7;j++)
	{
	    if(hboard[j][i]!=-1)
	    {
	     if(x==X && y==Y)
	     f=hboard[j][i];
	    }
	    x+=40;
	}
	x=200;
	y+=40;
   }
   return f;
}

//------------------------------------------------------------------------
//	Sets the board to 1 or 0 ,represents filled & empty respectively
//------------------------------------------------------------------------

void hSetBoard(int X,int Y,int element)
{
   int i,j,x=200,y=100;
   for(i=0;i<7;i++)
   {
	for(j=0;j<7;j++)
	{
	    if(hboard[j][i]!=-1)
	    {
	     if(x==X && y==Y)
	     hboard[j][i]=element;
	    }
	    x+=40;
	}
	x=200;
	y+=40;
   }
}

//------------------------------------------------------------------------
//			Blinks the cursor or square
//------------------------------------------------------------------------

void hBlink(int hx,int hy,int c)
{
 int i;
 setcolor(c);
 do
 {
	rectangle(hx-10,hy-10,hx+10,hy+10);
	rectangle(hx-11,hy-11,hx+11,hy+11);
	hmydelay(0.5);
	rectangle(hx-10,hy-10,hx+10,hy+10);
	rectangle(hx-11,hy-11,hx+11,hy+11);
	hmydelay(0.5);
 }while(!kbhit());
}

//------------------------------------------------------------------------
//		 When ENTER pressed check for conditions & perform task
//------------------------------------------------------------------------

int hMakeMove(int X,int Y)
{
 int flag,key;
 flag=NO;
 if(hmarble_color==11)
 hMarble(X,Y,9);
 else hMarble(X,Y,11);
 key = bioskey(0);
 if(key==0x4800)//up
 {
	if(hGetBoard(X,Y-80)==0 && hGetBoard(X,Y-40)==1)
	{
		  hMarble(X,Y,0);
		  hSetBoard(X,Y,0);
		  Y-=40;
		  hMarble(X,Y,0);
		  hSetBoard(X,Y,0);
		  Y-=40;
		  hSetBoard(X,Y,1);
		  hy=Y;
		  flag=YES;
	}
 }
 if(key==0x5000)//down
 {
	if(hGetBoard(X,Y+80)==0 && hGetBoard(X,Y+40)==1)
	{
		  hMarble(X,Y,0);
		  hSetBoard(X,Y,0);
		  Y+=40;
		  hMarble(X,Y,0);
		  hSetBoard(X,Y,0);
		  Y+=40;
		  hSetBoard(X,Y,1);
		  hy=Y;
		  flag=YES;
	}
 }
 if(key==0x4b00)//left
 {
	if(hGetBoard(X-80,Y)==0 && hGetBoard(X-40,Y)==1)
	{
		  hMarble(X,Y,0);
		  hSetBoard(X,Y,0);
		  X-=40;
		  hMarble(X,Y,0);
		  hSetBoard(X,Y,0);
		  X-=40;
		  hSetBoard(X,Y,1);
		  hx=X;
		  flag=YES;
	}
 }
 if(key==0x4d00)//right
 {
	if(hGetBoard(X+80,Y)==0 && hGetBoard(X+40,Y)==1)
	{
		  hMarble(X,Y,0);
		  hSetBoard(X,Y,0);
		  X+=40;
		  hMarble(X,Y,0);
		  hSetBoard(X,Y,0);
		  X+=40;
		  hSetBoard(X,Y,1);
		  hx=X;
		  flag=YES;
	}
  }
  if(kbhit()) getch();
  setcolor(11);
  if(flag==YES)
  {
	hMarble(X,Y,hmarble_color);
  }
  else//invalid key
  {
	hMarble(X,Y,hmarble_color);
	sound(800);
	delay(100);
	nosound();
  }
  return flag;
}

//------------------------------------------------------------------------
//		Handles All the funtions & Perform desired move
//------------------------------------------------------------------------

void hInit()
{
   int i,j,e=1;
   char ch;
   setwritemode(XOR_PUT);
   setcolor(15);
   while(e)
   {
    setfillstyle(1,11);
    hLcd(360,425,hmarble);
    hBlink(hx,hy,11);
    ch=getch();
    hLcd(360,425,hmarble);
    if(ch==ESC) e=0;
    if(hGetXY(hx,hy)==1)
    {
	switch(ch)
	{
		case    UP :if(hGetXY(hx,hy-40)==1)
				if(hy>100) hy-=40;break;
		case  DOWN :if(hGetXY(hx,hy+40)==1)
				if(hy<340) hy+=40;break;
		case  LEFT :if(hGetXY(hx-40,hy)==1)
				if(hx>200) hx-=40;break;
		case RIGHT :if(hGetXY(hx+40,hy)==1)
				if(hx<440) hx+=40;break;
		case ENTER :if(hGetBoard(hx,hy)==1)
			    {
			     hMakeMove(hx,hy);
			    }
			    break;
		case ESC   :e=0;break;
		case '+': hmarble_color++;
			 if(hmarble_color>15) hmarble_color=2;
			 hDrawBoard();
			 break;
		case '-':hmarble_color--;
			 if(hmarble_color<2) hmarble_color=15;
			 hDrawBoard();
			 break;
	}//switch
    }//if
   if(hcheck()==0) e=hfinish();
   }//while
   setwritemode(COPY_PUT);
}

//------------------------------------------------------------------------
//			Display Final Screen
//------------------------------------------------------------------------

int hfinish()
{
    FILE * pFile;
    int i,j,f,ch(int x, int y);
    char opt=0;
    setwritemode(COPY_PUT);
    f=0;
    for(i=0;i<7;i++)
    {
    for(j=0;j<7;j++)
    if(hboard[j][i]==1)
    f++;
    }
    hLcd(360,425,hmarble);
//    f-=1;
    hwin("Done !",220,155,425,240,1);
    setcolor(0);
    settextstyle(1,0,1);
    switch(f)
    {
	case 1:outtextxy(230,180,"You Are Intelligent !");break;
	case 2:outtextxy(255,180,"    Wonderful !");break;
	case 3:outtextxy(255,180,"  Good Job !");break;
	case 4:outtextxy(255,180,"  Can be better !");break;
	case 5:outtextxy(230,180," You Need Practice !");break;
	case 6:outtextxy(230,180,"   Very Poor !");break;
	case 7:outtextxy(230,180," Very Very Poor !");break;
	default:outtextxy(255,180," Try Again !");break;
    }
   //  delay(1000);
    if(f==1)
    {
    cong();
       for(i=0;i<7;i++)
     {
	for(j=0;j<7;j++)
	if(eboard[j][i]!=-1) eboard[j][i]=1;
     }
     Marble(320,220,0);
     eboard[3][3]=0;
     emarble=32;
     eBackground();
     eDrawBoard();

       f=1;
    }
    else
    getch();
    mwin("Exit ?",220,155,425,240,1);
    settextstyle(1,0,1);
    setcolor(1);
    outtextxy(240,180,"Play Again [y/n] :");
    opt=getch();
    setfillstyle(1,3);
    bar(17,402,624,464);
    if(opt=='y' || opt=='Y')
    {
     for(i=0;i<7;i++)
     {
	for(j=0;j<7;j++)
	if(hboard[j][i]!=-1) hboard[j][i]=1;
     }
     hMarble(320,220,0);
     hboard[3][3]=0;
     hmarble=32;
     hBackground();
     hDrawBoard();
     f=1;
    }
    else f=0;
    setwritemode(XOR_PUT);
    return f;
}                                e
void hwin(char *text,int sx,int sy,int ex,int ey,int ck)
{
   setfillstyle(1,12);
   bar(sx,sy,ex,ey);
   setfillstyle(1,12);
   setcolor(15);
   line(sx,sy,sx,ey);
   line(sx,sy,ex,sy);
   line(sx,sy,sx,ey);
   line(sx,sy,ex,sy);
   setcolor(0);
   line(ex,sy,ex,ey);
   line(ex,sy,ex,ey);
   line(sx,ey,ex,ey);
   line(sx,ey,ex,ey);
   if(ck==1)
   {
   settextstyle(0,0,0);
   setfillstyle(1,4);
   bar(sx+2,sy+3,ex-2,sy+18);
   setcolor(14);
   outtextxy(sx+5,sy+5,text);
   //for x
   setfillstyle(1,7);
   bar(ex-15,sy+4,ex-4,sy+15);
   setcolor(15);
   line(ex-15,sy+4,ex-4,sy+4);
   line(ex-15,sy+4,ex-15,sy+15);
   setcolor(1);
   line(ex-15,sy+15,ex-4,sy+15);
   line(ex-4,sy+4,ex-4,sy+15);
   setcolor(1);
   outtextxy(ex-13,sy+5,"x");
   setfillstyle(1,7);
   }
}
void hwinp(int sx,int sy,int ex,int ey,int state)
{
   if(state==1)
   {
   setcolor(1);
   line(sx,sy,sx,ey);
   line(sx,sy,ex,sy);
   line(sx,sy,sx,ey);
   line(sx,sy,ex,sy);
   setcolor(2);
   line(ex,sy,ex,ey);
   line(ex,sy,ex,ey);
   line(sx,ey,ex,ey);
   line(sx,ey,ex,ey);
  }
  else
  {
   setcolor(2);
   line(sx,sy,sx,ey);
   line(sx,sy,ex,sy);
   line(sx,sy,sx,ey);
   line(sx,sy,ex,sy);
   setcolor(1);
   line(ex,sy,ex,ey);
   line(ex,sy,ex,ey);
   line(sx,ey,ex,ey);
   line(sx,ey,ex,ey);
  }
}
void hLcd(int hx,int hy,int n)
{
 int a,b;
 if(n<10)
 {
 hLCD(hx,hy,0);
 hLCD(hx+15,hy,n);
 }
 else if(n<100)
 {
  a=n/10;b=n%10;
  hLCD(hx,hy,a);
  hLCD(hx+15,hy,b);
 }
}
void hLCD(int left,int top,int NUM)
{
   int i;
//   int right=100, bottom=100;
   setcolor(10);

   switch(NUM)
   {
   case 1:
	  line(left+11,top+2,left+11,top+9);	//  |
	  line(left+11,top+11,left+11,top+18);	//  |
	  break;
   case 2:
	   line(left,top,left+10,top);		//--
	   line(left+11,top+2,left+11,top+9);	//  |
	   line(left+1,top+10,left+9,top+10);	//--
	   line(left-1,top+11,left-1,top+18);	//|
	   line(left,top+20,left+10,top+20);	//--
	   break;
   case 3:
	   line(left,top,left+10,top);		//--
	   line(left+11,top+2,left+11,top+9);	//  |
	   line(left+1,top+10,left+9,top+10);	//--
	   line(left+11,top+11,left+11,top+18);	//  |
	   line(left,top+20,left+10,top+20);	//--
	   break;
   case 4:
	   line(left-1,top+2,left-1,top+9);	//|
	   line(left+11,top+2,left+11,top+9);	//  |
	   line(left+1,top+10,left+9,top+10);	//--
	   line(left+11,top+11,left+11,top+18);	//  |
	   break;
   case 5:
	   line(left,top,left+10,top);		//--
	   line(left-1,top+2,left-1,top+9);	//|
	   line(left+1,top+10,left+9,top+10);	//--
	   line(left+11,top+11,left+11,top+18);	//  |
	   line(left,top+20,left+10,top+20);	//--
	   break;
   case 6:
	   line(left,top,left+10,top);		//--
	   line(left-1,top+2,left-1,top+9);	//|
	   line(left+1,top+10,left+9,top+10);	//--
	   line(left-1,top+11,left-1,top+18);	//|
	   line(left+11,top+11,left+11,top+18);	//  |
	   line(left,top+20,left+10,top+20);	//--
	   break;
   case 7:
	   line(left,top,left+10,top);		//--
	   line(left-1,top+2,left-1,top+9);	//|
	   line(left+11,top+2,left+11,top+9);	//  |
	   line(left+11,top+11,left+11,top+18);	//  |
	   break;
   case 8:
	   line(left,top,left+10,top);		//--
	   line(left-1,top+2,left-1,top+9);	//|
	   line(left+11,top+2,left+11,top+9);	//  |
	   line(left+1,top+10,left+9,top+10);	//--
	   line(left-1,top+11,left-1,top+18);	//|
	   line(left+11,top+11,left+11,top+18);	//  |
	   line(left,top+20,left+10,top+20);	//--
	   break;
   case 9:
	   line(left,top,left+10,top);		//--
	   line(left-1,top+2,left-1,top+9);	//|
	   line(left+11,top+2,left+11,top+9);	//  |
	   line(left+1,top+10,left+9,top+10);	//--
	   line(left+11,top+11,left+11,top+18);	//  |
	   line(left,top+20,left+10,top+20);	//--
	   break;
   case 0:
	   line(left,top,left+10,top);		//--
	   line(left-1,top+2,left-1,top+9);	//|
	   line(left+11,top+2,left+11,top+9);	//  |
	   line(left-1,top+11,left-1,top+18);	//|
	   line(left+11,top+11,left+11,top+18);	//  |
	   line(left,top+20,left+10,top+20);	//--
	   break;
   }
}

void loading()
{
 int i,e,c=150;
 setbkcolor(2);
 for(e=0;e<4;e++)
 {
  for(i=50;i<80;i++)
  {
    setcolor(14);
    settextstyle(3, HORIZ_DIR, 5);
    outtextxy(x-200,y-150,"CONGRATULATION!!");
    setcolor(MAGENTA);
    settextstyle(2, HORIZ_DIR, 7);
    outtextxy(x+10,y-90,"You completed the LEVEL");
    setcolor(5);
    settextstyle(SMALL_FONT, HORIZ_DIR, 10);
    outtextxy(x,y,"Loading...");
    setcolor(13);
    settextstyle(2, HORIZ_DIR, 5);
    outtextxy(x+2,y+2,"To the Next Level... ");
    setcolor(4);
    circle(x,y,i);
    circle(x,y,c);
    c--;
    delay(10);
    cleardevice();
  }
  delay(100);
  }
}
void cong()
{
   int i,e,c=150;
 setbkcolor(0);
    for(e=0;e<4;e++)
 {
  for(i=50;i<80;i++)
  {
    setcolor(14);
    settextstyle(3, HORIZ_DIR, 5);
    outtextxy(200,150,"EXCELLENT!!!");
    setcolor(2);
    settextstyle(3, HORIZ_DIR, 5);
    outtextxy(50,250,"You Completed All Levels");
    setcolor(4);
    circle(50,20,i);
    circle(50,20,c);
    setcolor(5);
    circle(300,200,i);
    circle(300,200,c);
    setcolor(6);
    circle(50,400,i);
    circle(50,400,c);
    setcolor(9);
    circle(550,20,i);
    circle(550,20,c);
    setcolor(10);
    circle(550,400,i);
    circle(550,400,c);
    c--;
    delay(10);
    cleardevice();
  }
  delay(100);
  }
    getch();
}
