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
	// 빙고판 변수
	int size;
	int **mapForUser;
	int **mapForCom;

	// 리플레이 변수
	int **repForUser;
	int **repForCom;
	int orderForReplay[81];
	int orderCount = 0;

	// 커서 변수
	int cursorX = 0;
	int cursorY = 0;
	int ch;

	// 커서 범위 제한
	int maxX;
	int maxY;
	int minX;
	int minY;

	// 컴퓨터 알고리즘
	int horizontal[9] = {0, };
	int vertical[9] = {0, };
	int diagnal[2] = {0, };

public:
	~MHMoonGame();

	// 윈도우 API 함수
	void setCursorView(bool visible);
	void gotoxy(int x, int y);
	void textColor(int color);

	// 게임 실행
	void play();

	// 메뉴
	int showMenu();
	int inGameMenu();

	// 플레이어 및 컴퓨터 선택
	void showMap();
	int inGameCursor();
	int playerPlay(int x, int y);

	void findBestPlay(int &outX, int &outY);
	void computerTurn();

	// 맵 초기화
	void createMap();
	void memoryDelete();
	void swap(int &x, int &y);

	// 승리 판정 및 리플레이
	int decision();
	void replay();

	// 저장하기, 불러오기
	void loadGame();
	void saveGame();
};