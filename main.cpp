#include"chess.h"

int main()
{
	initgraph(height, width);
	//���ô��ڱ�������
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "������");
	initgame();
	mousebox();
	
	closegraph();
	return 0;
}