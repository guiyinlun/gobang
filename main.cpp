#include"chess.h"

int main()
{
	initgraph(height, width);
	//设置窗口标题文字
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "五子棋");
	initgame();
	mousebox();
	
	closegraph();
	return 0;
}