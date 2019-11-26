#ifndef cfgptree
#define cfgptree

#include<graphics.h>
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include"display1.h"
#include"display2.h"
#include"parstree.h"


long countz;



class context_free_grammar
{
public:
context_free_grammar()
	    {
		
	    }

~context_free_grammar(){}

void first();

char access[100],access2[100],*h ;
int x,c;
char str[1000],revstr[1000],*myword[10],*ptr;
long num,j,count,a,counta,i,z;

};

void context_free_grammar::first()
{
int gd=DETECT, gm;

initgraph(&gd,&gm,"C:\\turboc3\\bgi");

clrscr();

display_1 ddl;
display_2 ddm;

ddl.display_1_process();
z=0; countz=0;
gotoxy(32,8);
gets(str);

if (strlen(str)==0)
	{
	gotoxy(32,8);
	printf("<Empty String>\n");
	}

else
{
printf("\n");
a=0;
counta=0;
ptr=strtok(str," ");
while (ptr!=NULL)
	{
	myword[a]=ptr;
	a++; counta++;
	ptr=strtok(NULL," ");
	}

for (i=0;i<counta;i++)
{

strcpy(revstr,myword[i]);
strrev(revstr);
sscanf(myword[i],"%lX",&num);
	
if (strcmp(myword[i],revstr)==0)
	{
	printf("     %lX is Palindrome and it's conversion is %ld",num,num);
	count=0;
	for (j=2;j<num;j++)
		{
		if (num%j==0)
			{
			count++;
			}
		}
	if (count==0)
		{
		printf(" and %ld is prime",num);
		palprime[z]=myword[i];	
		z++; countz++;		
		}
	else
		{
		printf(" and %ld is not prime",num);
		}
	
	printf(".");
	}

else
	{
	printf("     %lX is not a Palindrome.",num);
	}

	printf("\n");
}

}



if (countz==0)
	{
	printf("\n");
	printf("     There are no Palindromic Prime you inputted. ");
	getch();
	}

else
	{
	printf("\n");
	printf("     Therefore the Palindromic Prime are: ");
	parse_tree pt;
	o=0;
	for (i=0;i<countz;i++)
		{
		printf("%s ",strupr(palprime[i]));
		}
	setcolor(BLUE);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR,4);
	outtextxy(70,430,"   Press any key to continue    ");
	getch();
	for (i=0;i<countz;i++)
		{
		pt.parse_tree_process();
		o++;
		}
	}




ddm.display_2_process();
getchar();
closegraph();

return;
}


#endif