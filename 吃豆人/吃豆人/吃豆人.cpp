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
enum ���� {��=0,��=1,��=2,��=3,��ͣ=4,��ͣ=5,��ͣ=6,��ͣ=7};
enum ��{����=0,����=1};
int ��������=0;
struct �Զ���
{
	int ox,oy,x,y,r;		
	�� a��;
	int ����;	
};
struct ����
{
	int x,y,r;
};

//////////////////////////////////////////////////////
// ��������
//

void	OnUp(�Զ��� *a);								// �����ƶ�
void	OnLeft(�Զ��� *a);							// �����ƶ�
void	OnRight(�Զ��� *a);							// �����ƶ�
void	OnDown(�Զ��� *a);							// �����ƶ�
void	OnStopTop(�Զ��� *a);
int		GetCmd();							// ��ȡ�û����������
void	DispatchCmd(�Զ��� *a,int cmd);	// �����û����������
void	drawMap();
void	drawMonster();
void	hitRANGE(int x1,int y1,int r,�Զ��� *a);
void    check_Hit_Monsters(double x1,double y1,double x2,double y2);
//////////////////////////////////////////////////////

void ���Զ���(�Զ��� a)
{
	setfillcolor(BLACK);
	solidcircle (a.ox, a.oy, 2*a.r);
	setfillcolor(YELLOW);
	solidcircle (a.x, a.y, a.r);
	setfillcolor(BLACK);
	if(a.����==��)
		if(a.a��==����)
			solidpie (a.x-a.r,a.y-a.r, a.x+a.r, a.y+a.r, 2*PIE-PIE/5, PIE/5);
		else
			solidpie (a.x-a.r,a.y-a.r, a.x+a.r, a.y+a.r, 2*PIE-PIE/10, PIE/10);
	if(a.����==��)
		if(a.a��==����)
			solidpie (a.x-a.r,a.y-a.r, a.x+a.r, a.y+a.r,  PIE-PIE/5,PIE+PIE/5);
		else
			solidpie (a.x-a.r,a.y-a.r, a.x+a.r, a.y+a.r, PIE-PIE/10,PIE+PIE/10 );
	if(a.����==��)
		if(a.a��==����)			
			solidpie (a.x-a.r,a.y-a.r, a.x+a.r, a.y+a.r, PIE/2-PIE/5,PIE/2+PIE/5 );
		else
			solidpie (a.x-a.r,a.y-a.r, a.x+a.r, a.y+a.r, PIE/2-PIE/10, PIE/2+PIE/10);
	if(a.����==��)
		if(a.a��==����)
			solidpie (a.x-a.r,a.y-a.r, a.x+a.r, a.y+a.r,  3*PIE/2-PIE/5,3*PIE/2+PIE/5);
		else
			solidpie (a.x-a.r,a.y-a.r, a.x+a.r, a.y+a.r,3*PIE/2-PIE/10,3*PIE/2+PIE/10 );
}

void ������(���� &p����){
	int i,j;
	for(i=50;i<=590;i+=10)
	{	if(i==130||i==240||i==420||i==520)
		{	for(j=80;j<=410;j+=80)
			{	setfillcolor(RED);
				p����.x=i;
				p����.y=j;
				solidcircle(p����.x,p����.y,p����.r);
				
			}
		}
		if(i==60||i==590)
		{	for(j=80;j<=410;j+=160)
		{
				setfillcolor(RED);
				p����.x=i;
				p����.y=j;
				solidcircle(p����.x,p����.y,p����.r);
		}
		}
		if(i==330)
		{
			for(j=160;j<=320;j+=80)
			{
				setfillcolor(RED);
				p����.x=i;
				p����.y=j;
				solidcircle(p����.x,p����.y,p����.r);
			}
		}
	}
}

void �ƶ��Զ���(�Զ��� *a,���� p����)
{
	a->����=p����;
	if(p����==��){
		a->ox=a->x;a->x-=2;
	}

	if(p����==��){
		a->ox=a->x;a->x+=2;
	}
	if(p����==��){
		a->oy=a->y;a->y-=2;
	}
	if(p����==��){
		a->oy=a->y;a->y+=2;
	}
	if(p����==��ͣ){
			a->oy=a->y;a->y+=R;
			
	}
	if(p����==��ͣ){
			a->oy=a->y;a->y-=R;
			
	}
	if(p����==��ͣ){
			a->ox=a->x;a->x+=R;
			
	}
	if(p����==��ͣ){
			a->ox=a->x;a->x-=R;
			
	}
	if(a->x % 20==0)
		if(a->a��==����)
			a->a��=����;
		else
			a->a��=����;
	if(a->y % 20==0)
		if(a->a��==����)
			a->a��=����;
		else
			a->a��=����;
	
}


void main()
{	 
	
	�Զ��� a�Զ���;
	a�Զ���.x=a�Զ���.ox=20;
	a�Զ���.y=a�Զ���.oy=240;
	a�Զ���.r=R;
	a�Զ���.a��=����;	
	a�Զ���.����=��;
	���� a����;
	//a����.x=400;
	//a����.y=100;
	a����.r=5;
	initgraph(640, 480);
	int c;
	int sum=0;
	srand((unsigned)time(NULL));
	������(a����);
	while(true )	
	{
		
		c = GetCmd();
		//cleardevice();
		���Զ���(a�Զ���);
		drawMonster();
		BeginBatchDraw();
		drawMap();
		EndBatchDraw();
		DispatchCmd(&a�Զ���,c);
		hitRANGE(a�Զ���.ox,a�Զ���.oy,a�Զ���.r,&a�Զ���);
		// ��¼��������
			if((abs(a�Զ���.ox-60)<=3||abs(a�Զ���.ox-130)<=3||abs(a�Զ���.ox-240)<=3||abs(a�Զ���.ox-330)<=3||abs(a�Զ���.ox-420)<=3||abs(a�Զ���.ox-520)<=3||abs(a�Զ���.ox-590)<=3)&&(a�Զ���.oy%80==0))
			{
						sum++;
			}
		TCHAR buf[100];
		TCHAR gpsx[100];
		TCHAR gpsy[100];
		TCHAR mark[100];
		TCHAR text1[]=_T("score");
		_stprintf(buf, _T("%d"), ��������);
		_stprintf(gpsx,_T("%d"),a�Զ���.x);//��¼pac-man��ǰ����
		_stprintf(gpsy,_T("%d"),a�Զ���.y);
		_stprintf(mark,_T("%d"),5*sum);
		outtextxy(50,50, buf);
		outtextxy(100,50, gpsx);
		outtextxy(150,50, gpsy);
		outtextxy(320,50,mark);
		outtextxy(309,30,text1);
		check_Hit_Monsters(a�Զ���.x,a�Զ���.y,410,320);
		check_Hit_Monsters(a�Զ���.x,a�Զ���.y,190,110);
		check_Hit_Monsters(a�Զ���.x,a�Զ���.y,410,140);
		check_Hit_Monsters(a�Զ���.x,a�Զ���.y,150,320);
		Sleep(10);
	}
	getch();
	closegraph();
}


int GetCmd()
{
	int c = 0;

	if (GetAsyncKeyState(VK_LEFT)	& 0x8000)		c |= CMD_LEFT;//��λ��a=a|b,ֻҪa��b��һ��1�������Ϊ1��
	if (GetAsyncKeyState(VK_RIGHT)	& 0x8000)		c |= CMD_RIGHT;
	if (GetAsyncKeyState(VK_UP)		& 0x8000)		c |= CMD_UP;
	if (GetAsyncKeyState(VK_DOWN)	& 0x8000)   	c |= CMD_DOWN;	
	return c;
}
// �����û����������
void DispatchCmd(�Զ��� *a,int cmd)
{
	if (cmd & CMD_UP)			OnUp(a);
	if (cmd & CMD_DOWN)			OnDown(a);
	if (cmd & CMD_LEFT)			OnLeft(a);
	if (cmd & CMD_RIGHT)		OnRight(a);	
}

void OnUp(�Զ��� *a)
{
	��������++;
	�ƶ��Զ���(a,��);
}

// �����ƶ�
void OnLeft(�Զ��� *a)
{
	��������++;
	�ƶ��Զ���(a,��);

}


// �����ƶ�
void OnRight(�Զ��� *a)
{
	��������++;
	�ƶ��Զ���(a,��);
}


// �����ƶ�
void OnDown(�Զ��� *a)
{
	��������++;
	�ƶ��Զ���(a,��);
}
void OnStopTop(�Զ��� *a)
{	
	�ƶ��Զ���(a,��ͣ);
}
void OnStopBottom(�Զ��� *a)
{	
	�ƶ��Զ���(a,��ͣ);
}
void OnStopLeft(�Զ��� *a)
{	
	�ƶ��Զ���(a,��ͣ);
}
void OnStopRight(�Զ��� *a)
{	
	�ƶ��Զ���(a,��ͣ);
}
void drawMap()
{
	
	setlinecolor(LIGHTBLUE);
	fillroundrect(10,0,25,130,10,10);//���Ͽ�1
	fillroundrect (25,0,620,30,10,10);//�ϳ���
	fillroundrect (275,30,375,90,10,10);// �ɼ�����
	fillroundrect (10,120,90,220,10,10); 
	fillroundrect(10,370,25,480,10,10);//���¿�
	fillroundrect (25,450,620,480,10,10);//�³���
	fillroundrect (10,280,90,380,10,10);
	fillroundrect(620,0,635,130,10,10);
	fillroundrect (555,120,635,220,10,10);
	fillroundrect (275,190,375,210,10,10);
	fillroundrect (275,280,375,300,10,10);
	fillroundrect (275,390,375,450,10,10);
	fillroundrect(620,370,635,480,10,10);//���¿�
	fillroundrect (555,280,635,380,10,10);
	fillroundrect (180,180,200,320,10,10);//��߳���
	fillroundrect (180,370,205,395,10,10);
	fillroundrect (460,180,480,320,10,10);//�ұ߳���
	fillroundrect (460,100,485,125,10,10);
	fillroundrect (420,360,510,380,10,10);
	fillroundrect (420,380,440,400,10,10);
	
}
void hitRANGE(int x1,int y1,int r,�Զ��� *a)
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
	if((x1>=10&&x1<=100)&&(y1==110||y1==270))//��ͼ��ײ�ж���ʼ
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

		IMAGE monsters;//����ͼƬ
		loadimage(&monsters,_T("N:\\�½��ļ���\\�Զ���\\image\\monster4.jpg"),30,30,true);
		putimage(410,320,&monsters);
		loadimage(&monsters,_T("N:\\�½��ļ���\\�Զ���\\image\\monster4-1.jpg"),30,30,true);
		putimage(410,321,&monsters);
		loadimage(&monsters,_T("N:\\�½��ļ���\\�Զ���\\image\\monster1.jpg"),30,30,true);
		putimage(190,110,&monsters);
		loadimage(&monsters,_T("N:\\�½��ļ���\\�Զ���\\image\\monster1-1.jpg"),30,30,true);
		putimage(190,112,&monsters);
		loadimage(&monsters,_T("N:\\�½��ļ���\\�Զ���\\image\\monster2.jpg"),30,30,true);
		putimage(410,140,&monsters);
		loadimage(&monsters,_T("N:\\�½��ļ���\\�Զ���\\image\\monster2-1.jpg"),30,30,true);
		putimage(410,142,&monsters);
		loadimage(&monsters,_T("N:\\�½��ļ���\\�Զ���\\image\\monster3.jpg"),30,30,true);
		putimage(150,320,&monsters);
		loadimage(&monsters,_T("N:\\�½��ļ���\\�Զ���\\image\\monster3-1.jpg"),30,30,true);
		putimage(150,321,&monsters);
		
}
void  check_Hit_Monsters(double x1,double y1,double x2,double y2)
{
	double distance;
	distance=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	if(distance<=10+R)
	{						//���������ж�
		IMAGE gameover;
		loadimage(&gameover,_T("N:\\�½��ļ���\\�Զ���\\image\\1.jpg"),640,480,true);
		putimage(0,0,&gameover);
		Sleep(5000);
		exit(0);
	}

}