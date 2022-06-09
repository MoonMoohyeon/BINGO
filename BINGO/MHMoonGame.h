#pragma once
#include <conio.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <windows.h>

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
	// ������ ����
	int size;
	int **mapForUser;
	int **mapForCom;

	// ���÷��� ����
	int **repForUser;
	int **repForCom;
	int orderForReplay[81];
	int orderCount = 0;

	// Ŀ�� ����
	int cursorX = 0;
	int cursorY = 0;
	int ch;

	// Ŀ�� ���� ����
	int maxX;
	int maxY;
	int minX;
	int minY;

	// ��ǻ�� �˰���
	int horizontal[9] = {0, };
	int vertical[9] = {0, };
	int diagnal[2] = {0, };

public:
	~MHMoonGame();

	// ������ API �Լ�
	void setCursorView(bool visible);
	void gotoxy(int x, int y);
	void textColor(int color);

	// ���� ����
	void play();

	// �޴�
	int showMenu();
	int inGameMenu();

	// �÷��̾� �� ��ǻ�� ����
	void showMap();
	int inGameCursor();
	int playerPlay(int x, int y);

	void findBestPlay(int &outX, int &outY);
	void computerTurn();

	// �� �ʱ�ȭ
	void createMap();
	void memoryDelete();
	void swap(int &x, int &y);

	// �¸� ���� �� ���÷���
	int decision();
	void replay();

	// �����ϱ�, �ҷ�����
	void loadGame();
	void saveGame();
};