#pragma  once  
#include<iostream>
#include <graphics.h>
#include <conio.h>
#include<cmath>
#include<ctime>
using namespace std;

int height = 860, width = 660, interval = 30;
void initgame();
void drawingboard();
void downchess(int x, int y);
void drawbox(int x, int y, int w);
void mousebox();
int iswin();
bool winer(int x);
void roundsmark(int x);
