#pragma once
#include <iostream>
#include <cstdio>
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

	// �߰��� ���÷��� ������
	int** repForUser;
	int** repForCom;
	int orderForReplay[81];
	int orderCount = 0;

	int cursorX = 0;
	int cursorY = 0;
	int ch;

	int size; //Gameboard�� �Ӽ��̹Ƿ� ��������� �����.
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
	void computerTurn();
	int showMenu();
	int createMap();
	void showMap();
	int changeMap(int x, int y);
	void swap(int& x, int& y);
	int decision();
	void replay();
	void saveGame();
};