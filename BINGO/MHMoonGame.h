#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ENTER 13

using namespace std;

class MHMoonGame
{
private:
	int** mapForUser;
	int** mapForCom;
	int cursorX = 0;
	int cursorY = 0;
	int ch;

	int size; //Gameboard의 속성이므로 멤버변수로 만든다.
	int maxX;
	int maxY;
	int minX;
	int minY;

public:
	void setCursorView(bool visible);
	void gotoxy(int x, int y);
	void textColor(int color);
	void play();
	void inGameCursor();
	int showMenu();
	int createMap();
	void showMap();
	void changeMap(int x, int y);
	void swap(int& x, int& y);
	int decision();
	void replay();
	void saveGame();
};