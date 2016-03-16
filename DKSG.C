#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <process.h>
#include <graphics.h>
int rx, ry, lx, ly, nx, ny, l, fl, del=20, i;
char dn = 'd', dl = 'd', ch = NULL;
char scr[10];
void food();
void snakewin();
void askagain();
void gameover();
void clrsnwin();
void checkdead();
void homescr();
void scorewin();
void clrscwin();
void makesnake();
void udscore();
void desnake();
void udpos();
void main()
{
	int gd = DETECT, gm;
	initgraph(&gd, &gm, "C:\\TC\\BGI");
	clrscr();
	cleardevice();
	homescr();
	clrscr();
	cleardevice();
	snakewin();
	scorewin();
	makesnake(0,0);
	lx = 31;
	ly = getmaxy()/2+2;
	nx = lx;
	ny = ly;
	randomize();
	food();
	l = 1;
	while(1)
	{
		udscore();
		delay(del);
		udpos();
		checkdead();
		desnake(lx,ly);
		makesnake(nx,ny);
		lx = nx;
		ly = ny;
		if(dn==' ' || dn==27) // 27 = Escape key
			goto m;
		food();
	}
m:	closegraph();
}
void udpos()
{
	fl = 0;
	if(kbhit())
	{
		dn = getch();
		if(dn!=dl)
		{
			if((dl!='w') && (dn=='s'||dn=='S'))
			{	ny = ly+10; fl = 1;	}
			else if((dl!='s') && (dn=='w'||dn=='W'))
			{	ny = ly-10; fl = 1;	}
			else if((dl!='a') && (dn=='d'||dn=='D'))
			{	nx = lx+10; fl = 1;	}
			else if((dl!='d') && (dn=='a'||dn=='A'))
			{	nx = lx-10; fl = 1;	}
			else if(dl=='a' && (dn=='d'||dn=='D'))
			{	nx = lx-10; fl = 1;	}
			else if(dl=='d' && (dn=='a'||dn=='A'))
			{	nx = lx+10; fl = 1;	}
			else if(dl=='w' && (dl=='s'||dn=='S'))
			{	ny = ly-10; fl = 1; }
			else if(dl=='s' && (dl=='w'||dn=='W'))
			{	ny = ly+10; fl = 1; }
		}
	}
	if(fl==0)
	{
		if(dl=='d'||dl=='D')
		{	nx = lx+10; fl = 1; }
		else if(dl=='a'||dl=='A')
		{	nx = lx-10; fl = 1; }
		else if(dl=='w'||dl=='W')
		{	ny = ly-10; fl = 1; }
		else if(dl=='s'||dl=='S')
		{	ny = ly+10; fl = 1; }
	}
	dl = dn;
}

void homescr()
{
	{
		setcolor(6);
		setfillstyle(7,6);
		bar(220,10,408,30);
		bar(220,10,240,330);
		bar(220,310,408,330);
		bar(388,10,408,330);
	}
	{
		setcolor(10);
		settextstyle(4,0,8);
		outtextxy(265,45,"hU");
		outtextxy(265,115,"NG");
		outtextxy(265,185,"RY");
	}
	{
		setcolor(14);
		settextstyle(3,0,3);
		outtextxy(220,340,"Choose Difficulty :");
	}
	{
		setcolor(12);
		settextstyle(0,0,1);
		outtextxy(190,385,"1. Easy Peasy");
		outtextxy(190,400,"2. I can handle myself");
		outtextxy(190,415,"3. Hungry? What kind of name is that?");
		outtextxy(190,430,"4. Bring It On.!");
	}
	ch = getch();
	switch(ch)
	{
		case '1' : del = 60;
				   break;
		case '2' : del = 50;
				   break;
		case '3' : del = 30;
				   break;
		case '4' : del = 20;
				   break;
		default: del = 40;
	}
}
void makesnake(int x, int y)
{
	{
		setcolor(10);
		setfillstyle(1,10);
		if(x==0||y==0)
			bar(31,getmaxy()/2+2,39,getmaxy()/2+10);
		else
			bar(x,y,x+8,y+8);
	}
}
void desnake(int x, int y)
{
	{
		setcolor(getbkcolor());
		setfillstyle(0,getbkcolor());
		bar(x-1,y-1,x+9,y+9);
	}
}
void food()
{
	if(getpixel(rx+1,ry+1) == 15)
		return;
	if(l!=0)
	{
		sound(1000);
		delay(3);
		sound(1500);
		delay(3);
		sound(2000);
		delay(3);
	}
	rx = random(41);
	ry = random(41);
	rx = 10*rx + 31;
	ry = 10*ry + 31;
	{
		setcolor(15);
		setfillstyle(1,15);
		bar(rx,ry,rx+8,ry+8);
	}
	l++;
	nosound();
}
void checkdead()
{
	if(nx<30 || nx>=449)
		gameover();
	if(ny<30 || ny>=449)
		gameover();
	if(getpixel(nx+2,ny+2)==10)
		gameover();
	return;
}
void gameover()
{
	int flash=1;
	int flsd;
	int rcol;
	sound(100);
	delay(500);
	nosound();
	delay(400);
	while(flash<=2)
	{
		clrsnwin();
		sound(50);
		delay(200);
		{
			setcolor(15);
			setfillstyle(1,15);
			bar(rx,ry,rx+8,ry+8);
		}
		makesnake(lx,ly);
		nosound();
		delay(300);
		flash++;
	}
	flash = 1;
	while(flash<=3)
	{
		cleardevice();
		delay(40);
		rcol = random(5) + 9;
		{
			setcolor(rcol);
			settextstyle(4,0,4);
			outtextxy(200,200,"GAME");
		}
		rcol = random(5) + 9;
		{
			setcolor(rcol);
			settextstyle(4,0,4);
			outtextxy(320,200,"OVER.!");
		}
		for(flsd=180;flsd>=70;flsd-=2)
		{
			sound(flsd);
			delay(5);
		}
		delay(250);
		nosound();
		flash++;
	}
	askagain();
	return;
}
void askagain()
{
u:	{
		clrscr();
		cleardevice();
		setcolor(10);
		settextstyle(3,0,6);
		outtextxy(getmaxx()/4-50,getmaxy()/4,"Play Again? y/n");
	}
	ch = getch();
	if(ch=='n' || ch=='N')
		exit(0);
	else if(ch=='y' || ch=='Y')
	{
		nx = lx = 31;
		ny = ly = getmaxy()/2+2;
		dn = dl = 'd';
		l = 0;
		cleardevice();
		snakewin();
		scorewin();
		return;
	}
	else
	{
		cleardevice();
		setcolor(12);
		settextstyle(3,0,2);
		outtextxy(getmaxx()/4,getmaxy()/4-30,"Invalid choice...");
		goto u;
	}
}
void udscore()
{
	{
		setcolor(getbkcolor());
		setfillstyle(0,getbkcolor());
		bar(520,245,580,275);
	}
	{
		setcolor(15);
		settextstyle(1,0,1);
		itoa(l-1,scr,10);
		outtextxy(537,250,scr);
	}
}
void snakewin()
{
	{
		setcolor(15);
		setfillstyle(SOLID_FILL,15);
		bar(20,20,29,460);
		bar(20,451,460,460);
		bar(20,20,460,29);
		bar(451,20,460,460);
	}
}
void clrsnwin()
{
	{
		setcolor(0);
		setfillstyle(0,0);
		bar(30,30,450,450);
	}
}
void scorewin()
{
	{
		setcolor(15);
		setfillstyle(SOLID_FILL,15);
		bar(470,120,620,129);
		bar(470,120,479,360);
		bar(611,120,620,360);
		bar(470,351,620,360);
	}
	{
		setcolor(15);
		settextstyle(4,0,3);
		outtextxy(515,170,"Score");
	}
	{
		setcolor(15);
		settextstyle(3,0,3);
		outtextxy(505,370,"Controls");
	}
	{
		setcolor(15);
		settextstyle(0,0,1);
		outtextxy(497,405,"w : move up");
		outtextxy(497,415,"a : move left");
		outtextxy(497,425,"s : move down");
		outtextxy(497,435,"d : move right");
		outtextxy(495,50,"Press ESC or");
		outtextxy(495,60,"SPACE to exit");
	}
}
void clrscwin()
{
	{
		setcolor(0);
		setfillstyle(0,0);
		bar(480,130,610,350);
	}
}