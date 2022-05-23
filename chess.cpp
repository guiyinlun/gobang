#include"chess.h"
int chess[21][21] = { 0 };//颜色信息 0无 1黑 2白
void initgame()
{
	memset(chess, 0, 21 * 21 * sizeof(int));
	height = 860; 
	width = 660; 
	interval = 30;
	drawingboard();
}
//画棋盘
void drawingboard()
{
	setrop2(R2_COPYPEN);
	setbkcolor(RGB(177, 177, 177));
	cleardevice();
	setfillcolor(RGB(242, 212, 130));
	solidrectangle(0,0,660,660);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	for (int i = 1; i <= width / interval - 1; i++)
	{
		line(i * interval, interval, i * interval, width -interval);
		line(interval-1, i * interval, width-interval, i * interval);
	}
	settextstyle(25, 12, _T("方正舒体"));
	settextcolor(BLACK);
	outtextxy(700, 500, _T("左键下黑棋"));
	outtextxy(700, 530, _T("右键下白棋"));
	outtextxy(700, 560, _T("中键新游戏"));

	settextstyle(0, 0, _T("黑体"));
	settextcolor(BLACK);
	outtextxy(700, 610, _T("作者：甘"));
	outtextxy(700, 630, _T("工具：VS2017，EasyX"));

}

//下棋
void downchess(int x,int y)
{
	setrop2(R2_COPYPEN);
	if (chess[x - 1][y - 1] == 1)
		setfillcolor(BLACK);
	else if(chess[x-1][y-1]== 2)
		setfillcolor(WHITE);
	solidcircle(x*interval, y*interval, 11);
}
//画选定框
void drawbox(int x, int y, int w)
{
	setrop2(R2_NOTXORPEN);
	line(x * 30 - w, y * 30 - w, x * 30 - 5, y * 30 - w);
	line(x * 30 - w, y * 30 - w, x * 30 - w, y * 30 - 5);
	line(x * 30 + w, y * 30 - w, x * 30 + 5, y * 30 - w);
	line(x * 30 + w, y * 30 - w, x * 30 + w, y * 30 - 5);
	line(x * 30 - w, y * 30 + w, x * 30 - w, y * 30 + 5);
	line(x * 30 - w, y * 30 + w, x * 30 - 5, y * 30 + w);
	line(x * 30 + w, y * 30 + w, x * 30 + 5, y * 30 + w);
	line(x * 30 + w, y * 30 + w, x * 30 + w, y * 30 + 5);
}
void roundsmark(int x)//1黑 2白
{
	setrop2(R2_NOTXORPEN);
	settextstyle(40, 20, _T("方正舒体"));
	if (x == 1)
	{
		settextcolor(BLACK);
		outtextxy(740, 100, _T("黑"));
	}
	else if (x == 2)
	{
		settextcolor(WHITE);
		outtextxy(740, 100, _T("白"));


	}	
}
void mousebox()
{
	ExMessage m;		// 定义鼠标消息
	setlinecolor(BLACK);
	int tempx = 0, tempy =0, nowx=0, nowy=0,nowxr, nowyr, rounds=1;
	roundsmark(1);
	while (true)
	{
		// 获取一条鼠标消息
		m = getmessage();
		if (m.message == WM_MBUTTONDOWN)
		{
			setrop2(R2_COPYPEN);
			initgame();
			mousebox();
		}
		else if (m.message == WM_MOUSEMOVE)
		{
			if (m.x > interval / 2 + 1 && m.x < width- interval/2-1 && m.y>interval/2+1 && m.y < width - interval/2-1)
			{
				
				nowx = m.x / interval;
				nowxr = m.x % interval;
				nowy = m.y / interval;
				nowyr = m.y % interval;
				if (nowxr > interval/2)nowx++;
				if (nowyr > interval/2)nowy++;
				if ((nowx != tempx || nowy != tempy))
				{
					if (tempx != 0 && tempy != 0)
					drawbox(tempx, tempy, interval/2-1);
					tempx = nowx;
					tempy = nowy;
					//画框
					drawbox(tempx, tempy, interval/2-1);
				}
			}
		}
		else if (m.message == WM_LBUTTONDOWN)
		{
			
			if (chess[tempx - 1][tempy - 1] == 0&&rounds==1)
			{
				chess[tempx-1][tempy-1] = 1;
				downchess(tempx, tempy);
				if (winer(iswin()))
				{
					Sleep(5000);
					initgame();
					mousebox();
				}
				roundsmark(1);
				roundsmark(2);
				rounds = 2;
			}
			
			
		}
		else if (m.message == WM_RBUTTONDOWN && rounds == 2)
		{
			
			if (chess[tempx - 1][tempy - 1] == 0)
			{
				chess[tempx - 1][tempy - 1] = 2;
				downchess(tempx, tempy);
				if (winer(iswin())) {
					Sleep(5000);
					initgame();
					mousebox();
				}
				roundsmark(2);
				roundsmark(1);
				rounds = 1;
			}	
		}
		
	}
}

int iswin()
{
	int a, b, c, d,win=0;
	for (int i = 0; i <= 20; i++)
	{
		for (int j = 0; j <= 20; j++)
		{
			if (chess[i][j] == 0) continue;
			if (i <= 16)
			{
				a= chess[i + 1][j];
				b = chess[i + 2][j];
				c = chess[i + 3][j];
				d = chess[i + 4][j];
				if (chess[i][j]==a &&chess[i][j] == b && chess[i][j] == c && chess[i][j] == d) {
					win = chess[i][j];
					return win;
				}
			}
			if (j <= 16)
			{
				a = chess[i ][j+1];
				b = chess[i][j+2];
				c = chess[i][j+3];
				d = chess[i ][j+4];
				if (chess[i][j] == a && chess[i][j] == b && chess[i][j] == c && chess[i][j] == d) {
				win = chess[i][j];
				return win;
				}
			}
			if (i <= 16 && j <= 16)
			{
				a = chess[i+1][j + 1];
				b = chess[i+2][j + 2];
				c = chess[i+3][j + 3];
				d = chess[i+4][j + 4];
				if (chess[i][j] == a && chess[i][j] == b && chess[i][j] == c && chess[i][j] == d) {
					win = chess[i][j];
					return win;
				}
			}
			if (i >= 4 && j <= 16)
			{
				a = chess[i - 1][j + 1];
				b = chess[i - 2][j + 2];
				c = chess[i - 3][j + 3];
				d = chess[i - 4][j + 4];
				if (chess[i][j] == a && chess[i][j] == b && chess[i][j] == c && chess[i][j] == d) {
					win = chess[i][j];
					return win;
				}
			}
		}
	}
	return win;
}
bool winer(int x)
{
	if (x == 0) return false;
	else if (x == 1) {
		setfillcolor(BLACK);

	}
	else if (x == 2) {
		setfillcolor(WHITE);
	}
	solidcircle(760, 330, 50);
	settextcolor(LIGHTRED);
	settextstyle(40, 20, _T("Script MT Bold"));
	outtextxy(700, 200, _T("WIN"));
	setrop2(R2_COPYPEN);
	return true;
}
