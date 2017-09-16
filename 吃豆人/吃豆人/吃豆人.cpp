#include "StdAfx.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <time.h>
#include <math.h>
#include<easyx.h>
#define WIDTH  640
#define HIEGHT 480
#define PIE 3.14
#define R 10
#pragma warning(disable:4996)
enum CMD { CMD_QUIT = 1, CMD_UP = 2, CMD_DOWN = 4, CMD_LEFT = 8, CMD_RIGHT = 16, CMD_MARKRED = 32, CMD_MARKGREEN = 64, CMD_MARKYELLOW = 128, CMD_CLEARMARK = 256 };
enum 方向 {上=0,右=1,下=2,左=3,上停=4,下停=5,左停=6,右停=7};
enum 嘴{张嘴=0,闭嘴=1};
int 按键次数=0;
struct 吃豆人
{
	int ox,oy,x,y,r;		
	嘴 a嘴;
	int 方向;	
};
struct 豆子
{
	int x,y,r;
};

//////////////////////////////////////////////////////
// 函数声明
//

void	OnUp(吃豆人 *a);								// 向上移动
void	OnLeft(吃豆人 *a);							// 向左移动
void	OnRight(吃豆人 *a);							// 向右移动
void	OnDown(吃豆人 *a);							// 向下移动
void	OnStopTop(吃豆人 *a);
int		GetCmd();							// 获取用户输入的命令
void	DispatchCmd(吃豆人 *a,int cmd);	// 处理用户输入的命令
void	drawMap();
void	drawMonster();
void	hitRANGE(int x1,int y1,int r,吃豆人 *a);
void    check_Hit_Monsters(double x1,double y1,double x2,double y2);
//////////////////////////////////////////////////////

void 画吃豆人(吃豆人 a)
{
	setfillcolor(BLACK);
	solidcircle (a.ox, a.oy, 2*a.r);
	setfillcolor(YELLOW);
	solidcircle (a.x, a.y, a.r);
	setfillcolor(BLACK);
	if(a.方向==右)
		if(a.a嘴==张嘴)
			solidpie (a.x-a.r,a.y-a.r, a.x+a.r, a.y+a.r, 2*PIE-PIE/5, PIE/5);
		else
			solidpie (a.x-a.r,a.y-a.r, a.x+a.r, a.y+a.r, 2*PIE-PIE/10, PIE/10);
	if(a.方向==左)
		if(a.a嘴==张嘴)
			solidpie (a.x-a.r,a.y-a.r, a.x+a.r, a.y+a.r,  PIE-PIE/5,PIE+PIE/5);
		else
			solidpie (a.x-a.r,a.y-a.r, a.x+a.r, a.y+a.r, PIE-PIE/10,PIE+PIE/10 );
	if(a.方向==上)
		if(a.a嘴==张嘴)			
			solidpie (a.x-a.r,a.y-a.r, a.x+a.r, a.y+a.r, PIE/2-PIE/5,PIE/2+PIE/5 );
		else
			solidpie (a.x-a.r,a.y-a.r, a.x+a.r, a.y+a.r, PIE/2-PIE/10, PIE/2+PIE/10);
	if(a.方向==下)
		if(a.a嘴==张嘴)
			solidpie (a.x-a.r,a.y-a.r, a.x+a.r, a.y+a.r,  3*PIE/2-PIE/5,3*PIE/2+PIE/5);
		else
			solidpie (a.x-a.r,a.y-a.r, a.x+a.r, a.y+a.r,3*PIE/2-PIE/10,3*PIE/2+PIE/10 );
}

void 画豆子(豆子 &p豆子){
	int i,j;
	for(i=50;i<=590;i+=10)
	{	if(i==130||i==240||i==420||i==520)
		{	for(j=80;j<=410;j+=80)
			{	setfillcolor(RED);
				p豆子.x=i;
				p豆子.y=j;
				solidcircle(p豆子.x,p豆子.y,p豆子.r);
				
			}
		}
		if(i==60||i==590)
		{	for(j=80;j<=410;j+=160)
		{
				setfillcolor(RED);
				p豆子.x=i;
				p豆子.y=j;
				solidcircle(p豆子.x,p豆子.y,p豆子.r);
		}
		}
		if(i==330)
		{
			for(j=160;j<=320;j+=80)
			{
				setfillcolor(RED);
				p豆子.x=i;
				p豆子.y=j;
				solidcircle(p豆子.x,p豆子.y,p豆子.r);
			}
		}
	}
}

void 移动吃豆人(吃豆人 *a,方向 p方向)
{
	a->方向=p方向;
	if(p方向==左){
		a->ox=a->x;a->x-=2;
	}

	if(p方向==右){
		a->ox=a->x;a->x+=2;
	}
	if(p方向==上){
		a->oy=a->y;a->y-=2;
	}
	if(p方向==下){
		a->oy=a->y;a->y+=2;
	}
	if(p方向==上停){
			a->oy=a->y;a->y+=R;
			
	}
	if(p方向==下停){
			a->oy=a->y;a->y-=R;
			
	}
	if(p方向==左停){
			a->ox=a->x;a->x+=R;
			
	}
	if(p方向==右停){
			a->ox=a->x;a->x-=R;
			
	}
	if(a->x % 20==0)
		if(a->a嘴==张嘴)
			a->a嘴=闭嘴;
		else
			a->a嘴=张嘴;
	if(a->y % 20==0)
		if(a->a嘴==张嘴)
			a->a嘴=闭嘴;
		else
			a->a嘴=张嘴;
	
}


void main()
{	 
	
	吃豆人 a吃豆人;
	a吃豆人.x=a吃豆人.ox=20;
	a吃豆人.y=a吃豆人.oy=240;
	a吃豆人.r=R;
	a吃豆人.a嘴=张嘴;	
	a吃豆人.方向=右;
	豆子 a豆子;
	//a豆子.x=400;
	//a豆子.y=100;
	a豆子.r=5;
	initgraph(640, 480);
	int c;
	int sum=0;
	srand((unsigned)time(NULL));
	画豆子(a豆子);
	while(true )	
	{
		
		c = GetCmd();
		//cleardevice();
		画吃豆人(a吃豆人);
		drawMonster();
		BeginBatchDraw();
		drawMap();
		EndBatchDraw();
		DispatchCmd(&a吃豆人,c);
		hitRANGE(a吃豆人.ox,a吃豆人.oy,a吃豆人.r,&a吃豆人);
		// 记录按键次数
			if((abs(a吃豆人.ox-60)<=3||abs(a吃豆人.ox-130)<=3||abs(a吃豆人.ox-240)<=3||abs(a吃豆人.ox-330)<=3||abs(a吃豆人.ox-420)<=3||abs(a吃豆人.ox-520)<=3||abs(a吃豆人.ox-590)<=3)&&(a吃豆人.oy%80==0))
			{
						sum++;
			}
		TCHAR buf[100];
		TCHAR gpsx[100];
		TCHAR gpsy[100];
		TCHAR mark[100];
		TCHAR text1[]=_T("score");
		_stprintf(buf, _T("%d"), 按键次数);
		_stprintf(gpsx,_T("%d"),a吃豆人.x);//记录pac-man当前坐标
		_stprintf(gpsy,_T("%d"),a吃豆人.y);
		_stprintf(mark,_T("%d"),5*sum);
		outtextxy(50,50, buf);
		outtextxy(100,50, gpsx);
		outtextxy(150,50, gpsy);
		outtextxy(320,50,mark);
		outtextxy(309,30,text1);
		check_Hit_Monsters(a吃豆人.x,a吃豆人.y,410,320);
		check_Hit_Monsters(a吃豆人.x,a吃豆人.y,190,110);
		check_Hit_Monsters(a吃豆人.x,a吃豆人.y,410,140);
		check_Hit_Monsters(a吃豆人.x,a吃豆人.y,150,320);
		Sleep(10);
	}
	getch();
	closegraph();
}


int GetCmd()
{
	int c = 0;

	if (GetAsyncKeyState(VK_LEFT)	& 0x8000)		c |= CMD_LEFT;//按位或（a=a|b,只要a，b有一个1，结果就为1）
	if (GetAsyncKeyState(VK_RIGHT)	& 0x8000)		c |= CMD_RIGHT;
	if (GetAsyncKeyState(VK_UP)		& 0x8000)		c |= CMD_UP;
	if (GetAsyncKeyState(VK_DOWN)	& 0x8000)   	c |= CMD_DOWN;	
	return c;
}
// 处理用户输入的命令
void DispatchCmd(吃豆人 *a,int cmd)
{
	if (cmd & CMD_UP)			OnUp(a);
	if (cmd & CMD_DOWN)			OnDown(a);
	if (cmd & CMD_LEFT)			OnLeft(a);
	if (cmd & CMD_RIGHT)		OnRight(a);	
}

void OnUp(吃豆人 *a)
{
	按键次数++;
	移动吃豆人(a,上);
}

// 向左移动
void OnLeft(吃豆人 *a)
{
	按键次数++;
	移动吃豆人(a,左);

}


// 向右移动
void OnRight(吃豆人 *a)
{
	按键次数++;
	移动吃豆人(a,右);
}


// 向下移动
void OnDown(吃豆人 *a)
{
	按键次数++;
	移动吃豆人(a,下);
}
void OnStopTop(吃豆人 *a)
{	
	移动吃豆人(a,上停);
}
void OnStopBottom(吃豆人 *a)
{	
	移动吃豆人(a,下停);
}
void OnStopLeft(吃豆人 *a)
{	
	移动吃豆人(a,左停);
}
void OnStopRight(吃豆人 *a)
{	
	移动吃豆人(a,右停);
}
void drawMap()
{
	
	setlinecolor(LIGHTBLUE);
	fillroundrect(10,0,25,130,10,10);//左上块1
	fillroundrect (25,0,620,30,10,10);//上长条
	fillroundrect (275,30,375,90,10,10);// 成绩区域
	fillroundrect (10,120,90,220,10,10); 
	fillroundrect(10,370,25,480,10,10);//左下块
	fillroundrect (25,450,620,480,10,10);//下长条
	fillroundrect (10,280,90,380,10,10);
	fillroundrect(620,0,635,130,10,10);
	fillroundrect (555,120,635,220,10,10);
	fillroundrect (275,190,375,210,10,10);
	fillroundrect (275,280,375,300,10,10);
	fillroundrect (275,390,375,450,10,10);
	fillroundrect(620,370,635,480,10,10);//右下块
	fillroundrect (555,280,635,380,10,10);
	fillroundrect (180,180,200,320,10,10);//左边长竖
	fillroundrect (180,370,205,395,10,10);
	fillroundrect (460,180,480,320,10,10);//右边长竖
	fillroundrect (460,100,485,125,10,10);
	fillroundrect (420,360,510,380,10,10);
	fillroundrect (420,380,440,400,10,10);
	
}
void hitRANGE(int x1,int y1,int r,吃豆人 *a)
{	
	if(x1-r-1<=0)
	{	
		OnStopLeft(a);}
	if(x1+r+1>=WIDTH)
	{
		OnStopRight(a);}
	if(y1-r-1<=30)
	{	
		OnStopTop(a);}
	if(y1+r+1>=HIEGHT)
	{	
		OnStopBottom(a);}
	if((x1>=10&&x1<=100)&&(y1==110||y1==270))//地图碰撞判定开始
	{
		OnStopBottom(a);
	}
	if((x1>=10&&x1<=100)&&(y1==230||y1==390))
	{
		OnStopTop(a);
	}
	if(x1==100&&((y1>=110&&y1<=225)||(y1>=270&&y1<=390)))
	{
		OnStopLeft(a);
	}
	if(x1==36&&((y1>=12&&y1<=110)||(y1>=390&&y1<=470)))
	{
		OnStopLeft(a);
	
	}
	if(y1==160&&((x1>=170&&x1<=210)||(x1>=450&&x1<=500))||((x1>270&&x1<380)&&(y1==180||y1==270||y1==380))||((x1>170&&x1<220)&&(y1==360))
		||((x1>450&&x1<495)&&(y1==90))||((x1>410&&x1<520)&&(y1==350))||((x1>550&&x1<640)&&(y1==110||y1==270)))
	{
		OnStopBottom(a);
	}
	if(y1==330&&((x1>=170&&x1<=210)||(x1>=450&&x1<=500))||((x1>270&&x1<380)&&(y1==220||y1==310||y1==100))||((x1>170&&x1<220)&&(y1==410))
		||((x1>450&&x1<500)&&(y1==140))||((x1>410&&x1<520)&&(y1==390))||((x1>410&&x1<450)&&(y1==410))||((x1>550&&x1<640)&&(y1==230||y1==390)))
	{
		OnStopTop(a);
	}
	if(((x1==170||x1==450)&&(y1>=170&&y1<=330))||((y1>360&&y1<410)&&(x1==170))||(((y1>40&&y1<100)||(y1>180&&y1<220)||(y1>270&&y1<310)||(y1>380&&y1<440))&&(x1==260))
		||((y1>90&&y1<135)&&(x1==450))||((y1>350&&y1<390)&&(x1==410))||((y1>390&&y1<410)&&(x1==410))||(((y1>110&&y1<230)||(y1>270&&y1<390))&&(x1==540))
		||((y1>42&&y1<110)||(y1>390&&y1<440))&&(x1==610))
	{
		OnStopRight(a);
	}
	if(((x1==210||x1==500)&&(y1>=170&&y1<=330))||((y1>360&&y1<410)&&(x1==220))||(((y1>180&&y1<220)||(y1>270&&y1<310)||(y1>380&&y1<440))&&(x1==385))
		||(((y1>40&&y1<100)||(y1>180&&y1<220)||(y1>270&&y1<310)||(y1>380&&y1<440))&&(x1==386))||((y1>90&&y1<134)&&(x1==500))||((y1>350&&y1<390)&&(x1==520))||
		((y1>390&&y1<410)&&(x1==450)))
	{
		OnStopLeft(a);
	}
	if(y1+r>=450&&(x1>=25&&x1<=620))
	{
		OnStopBottom(a);
	}
}
void drawMonster()
{

		IMAGE monsters;//引用图片
		loadimage(&monsters,_T("N:\\新建文件夹\\吃豆人\\image\\monster4.jpg"),30,30,true);
		putimage(410,320,&monsters);
		loadimage(&monsters,_T("N:\\新建文件夹\\吃豆人\\image\\monster4-1.jpg"),30,30,true);
		putimage(410,321,&monsters);
		loadimage(&monsters,_T("N:\\新建文件夹\\吃豆人\\image\\monster1.jpg"),30,30,true);
		putimage(190,110,&monsters);
		loadimage(&monsters,_T("N:\\新建文件夹\\吃豆人\\image\\monster1-1.jpg"),30,30,true);
		putimage(190,112,&monsters);
		loadimage(&monsters,_T("N:\\新建文件夹\\吃豆人\\image\\monster2.jpg"),30,30,true);
		putimage(410,140,&monsters);
		loadimage(&monsters,_T("N:\\新建文件夹\\吃豆人\\image\\monster2-1.jpg"),30,30,true);
		putimage(410,142,&monsters);
		loadimage(&monsters,_T("N:\\新建文件夹\\吃豆人\\image\\monster3.jpg"),30,30,true);
		putimage(150,320,&monsters);
		loadimage(&monsters,_T("N:\\新建文件夹\\吃豆人\\image\\monster3-1.jpg"),30,30,true);
		putimage(150,321,&monsters);
		
}
void  check_Hit_Monsters(double x1,double y1,double x2,double y2)
{
	double distance;
	distance=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	if(distance<=10+R)
	{						//怪兽相遇判定
		IMAGE gameover;
		loadimage(&gameover,_T("N:\\新建文件夹\\吃豆人\\image\\1.jpg"),640,480,true);
		putimage(0,0,&gameover);
		Sleep(5000);
		exit(0);
	}

}