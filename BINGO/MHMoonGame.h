#pragma once
#include <iostream>
#include <fstream>
#include <cstdio>
#include <windows.h>
#include <conio.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27

using namespace std;

class MHMoonGame
{
private:
	int** mapForUser;
	int** mapForCom;

	int** repForUser;
	int** repForCom;
	int orderForReplay[81];
	int orderCount = 0;

	int cursorX = 0;
	int cursorY = 0;
	int ch;

	int size;
	int maxX;
	int maxY;
	int minX;
	int minY;

public:

	~MHMoonGame();

	void setCursorView(bool visible);
	void gotoxy(int x, int y);
	void textColor(int color);

	void play();

	int showMenu();
	int inGameMenu();

	void showMap();
	int inGameCursor();
	int playerTurn(int x, int y);
	void computerTurn();

	int createMap();
	void swap(int& x, int& y);

	int decision();
	void replay();
	void loadGame();
	void saveGame();
};