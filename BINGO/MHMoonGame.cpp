#include "MHMoonGame.h"

MHMoonGame::~MHMoonGame()
{
	for (int i = 0; i < size; i++)
	{
		delete[] mapForUser[i];
		delete[] mapForCom[i];

		delete[] repForUser[i];
		delete[] repForCom[i];
	}

	delete[] mapForUser;
	delete[] mapForCom;
	delete[] repForUser;
	delete[] repForCom;
}

void MHMoonGame::setCursorView(bool visible)
{
	CONSOLE_CURSOR_INFO cursor = {1, visible};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
void MHMoonGame::gotoxy(int x, int y)
{
	COORD Pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void MHMoonGame::textColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void MHMoonGame::play()
{
	while (true)
	{
		int result = showMenu();

		if (result == -1)
		{
			return;
		}

		while (true)
		{
			int result = inGameCursor(); // 매 게임 루프에서 숫자 선택 함수 호출
			if (result == -1)
			{
				break;
			}

			system("cls");
			textColor(12);
			cout << "\n\n\n\n\n\n\n\n\n\n               컴퓨터 턴!" << endl;
			textColor(15);
			Sleep(1000);
			computerTurn();

			result = decision();
			if (result == 0)
			{
				system("cls");
				textColor(12);
				printf("\n\n\n\n\n\n\n\n\n\n               컴퓨터 승리!\n\n\n\n\n");
				textColor(15);
				Sleep(3000);
				replay();
				break;
			}
			else if (result == 1)
			{
				system("cls");
				textColor(9);
				printf("\n\n\n\n\n\n\n\n\n\n               유저 승리!\n\n\n\n\n");
				textColor(15);
				Sleep(3000);
				replay();
				break;
			}
			else if (result == 2)
			{
				system("cls");
				printf("\n\n\n\n\n\n\n\n\n\n               무승부...!\n\n\n\n\n");
				Sleep(1000);
			}
			else if (result == 3)
			{
				system("cls");
				printf("\n\n\n\n\n\n\n\n\n\n               무승부 종료.\n\n\n\n\n");
				Sleep(3000);
				replay();
				break;
			}
		}
	}
}

int MHMoonGame::showMenu()
{
	system("cls");
	cout << "\n\n\n\n"
		 << "             ■■■    ■■■    ■■    ■    ■■■■      ■■■    \n"
		 << "             ■   ■     ■      ■ ■   ■    ■           ■    ■   \n"
		 << "             ■ ■       ■      ■  ■  ■    ■  ■■■  ■      ■  \n"
		 << "             ■   ■     ■      ■   ■ ■    ■      ■   ■    ■   \n"
		 << "             ■■■    ■■■    ■    ■■     ■■■■     ■■■    \n\n"
		 << "                                 게 임 시 작\n"
		 << "                                 이 어 하 기\n"
		 << "                                 게 임 종 료\n";
	const int CURSOR_X_MIN = 30;
	const int CURSOR_Y_MIN = 10;
	const int CURSOR_Y_MAX = 12;

	cursorX = CURSOR_X_MIN;
	cursorY = CURSOR_Y_MIN;

	while (1)
	{
		gotoxy(cursorX, cursorY);
		ch = _getch();

		if (ch == ENTER)
		{
			int sel = cursorY - CURSOR_Y_MIN;
			switch (sel)
			{
			case 0:
				createMap();
				break;
			case 1:
				loadGame();
				break;
			case 2:
				return -1;
			}
			break;
		}

		if (ch == 0xE0) // msdn에 0xE0으로 적혀 있으므로 224에서 0xE0으로 수정. 이런 의미를 알 수 없는 값엔 주석을 달아주는 것이 좋음.
		{
			ch = _getch();
			switch (ch)
			{
			case UP:
				if (cursorY > CURSOR_Y_MIN)
				{
					cursorY--;
				}
				break;
			case DOWN:
				if (cursorY < CURSOR_Y_MAX)
				{
					cursorY++;
				}
				break;
			}
		}
	}

	return 0;
}

int MHMoonGame::inGameMenu()
{
	system("cls");
	cout << "\n\n\n\n\n\n\n\n\n\n"
		 << "                                 게 임 재 개\n"
		 << "                                 저 장 하 기\n"
		 << "                                 메뉴로 돌아가기\n";
	const int CURSOR_X_MIN = 30;
	const int CURSOR_Y_MIN = 10;
	const int CURSOR_Y_MAX = 12;

	cursorX = CURSOR_X_MIN;
	cursorY = CURSOR_Y_MIN;

	while (1)
	{
		gotoxy(cursorX, cursorY);
		ch = _getch();
		int sel;
		if (ch == ENTER)
		{
			sel = cursorY - CURSOR_Y_MIN;
			if (sel == 0)
				break;
			else if (sel == 1)
			{
				saveGame();
			}
			else if (sel == 2)
			{
				return -1;
			}
			break;
		}

		if (ch == 0xE0)
		{
			ch = _getch();
			switch (ch)
			{
			case UP:
				if (cursorY > CURSOR_Y_MIN)
				{
					cursorY--;
				}
				break;
			case DOWN:
				if (cursorY < CURSOR_Y_MAX)
				{
					cursorY++;
				}
				break;
			}
		}
	}
	return 0;
}

void MHMoonGame::showMap()
{
	printf("\n\n\n");
	printf("User\n\n");
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (mapForUser[i][j] == 0)
			{
				textColor(9);
				printf("    O");
				textColor(15);
			}
			else if (mapForUser[i][j] == -1)
			{
				textColor(12);
				printf("    X");
				textColor(15);
			}
			else
			{
				printf("%5d", mapForUser[i][j]);
			}
		}
		printf("\n\n");
	}

	printf("\n");

	printf("Computer\n\n");
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (mapForCom[i][j] == 0)
			{
				textColor(9);
				printf("    O");
				textColor(15);
			}
			else if (mapForCom[i][j] == -1)
			{
				textColor(12);
				printf("    X");
				textColor(15);
			}
			else
			{
				printf("%5d", mapForCom[i][j]);
			}
		}
		printf("\n\n");
	}
}

int MHMoonGame::inGameCursor()
{
	cursorX = 4;
	cursorY = 5;

	while (1)
	{
		system("cls");
		showMap();
		gotoxy(cursorX, cursorY);
		ch = _getch();
		if (ch == ENTER)
		{
			int valid = playerTurn(cursorX, cursorY);
			if (valid == 1)
				break;
		}
		else if (ch == ESC)
		{
			int result = inGameMenu();

			if (result == -1)
			{
				return -1;
			}

			cursorX = 4;
			cursorY = 5;
		}
		if (ch == 0xE0)
		{
			ch = _getch();
			switch (ch)
			{
			case UP:
				if (cursorY > minY)
				{
					cursorY -= 2;
				}
				break;
			case DOWN:
				if (cursorY < maxY)
				{
					cursorY += 2;
				}
				break;
			case LEFT:
				if (cursorX > minX)
				{
					cursorX -= 5;
				}
				break;
			case RIGHT:
				if (cursorX < maxX)
				{
					cursorX += 5;
				}
				break;
			}
		}
	}
	return 0;
}
int MHMoonGame::playerTurn(int x, int y)
{
	int arrx = 0, arry = 0;
	int n = 0;

	// 개선된 코드
	arrx = (x - 4) / 5;
	arry = (y - 5) / 2;
	orderForReplay[orderCount++] = mapForUser[arry][arrx]; // 선택한 수를 리플레이용 배열에 담음.
	while (true)
	{
		if (mapForUser[arry][arrx] == 0)
			return -1;
		if (mapForUser[arry][arrx] == -1)
			return -1;
		else
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					if (mapForCom[i][j] == mapForUser[arry][arrx])
					{
						mapForCom[i][j] = 0;
						break;
					}
				}
			}
			mapForUser[arry][arrx] = 0;
			return 1;
		}
	}
}

void MHMoonGame::findBestPlay(int &outX, int &outY)
{
	int horizontal[9] = {
		0,
	};
	int vertical[9] = {
		0,
	};
	int diagnal[2] = {
		0,
	};

	// outX = 0;
	// outY = 0;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (mapForCom[i][j] == 0 || mapForCom[i][j] == -1)
			{
				horizontal[i]++;
			}
			if (mapForCom[j][i] == 0 || mapForCom[j][i] == -1)
			{
				vertical[i]++;
			}
		}

		if (mapForCom[i][i] == 0 || mapForCom[i][i] == -1)
		{
			diagnal[0]++;
		}

		if (mapForCom[i][size - i - 1] == 0 || mapForCom[i][size - i - 1] == -1)
		{
			diagnal[1]++;
		}
	}

	unsigned int maxValue = 0;

	for (int i = 0; i < size; i++)
	{
		unsigned int temp = 1;
		for (int j = 0; j < size; j++)
		{
			if (mapForCom[i][j] == 0 || mapForCom[i][j] == -1)
			{
				continue;
			}

			if (i == j)
			{
				temp <<= (diagnal[0] + 1);
			}

			if ((size - i - 1) == j)
			{
				temp <<= (diagnal[1] + 1);
			}

			temp <<= horizontal[i];
			temp <<= vertical[j];

			if (maxValue < temp)
			{
				outX = i;
				outY = j;
				maxValue = temp;
			}
		}
	}
}

void MHMoonGame::computerTurn()
{
	int arrX, arrY;

	if (orderCount >= size * size)
	{
		return;
	}

	findBestPlay(arrX, arrY); // arrX, arrY에 최적 수의 좌표가 담김.

	orderForReplay[orderCount++] = mapForCom[arrX][arrY]; // 선택한 수를 리플레이용 배열에 담음.

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (mapForUser[i][j] == mapForCom[arrX][arrY])
			{
				mapForUser[i][j] = -1;
				goto found;
			}
		}
	}
found:

	mapForCom[arrX][arrY] = -1;
}

int MHMoonGame::createMap()
{
	srand(time(NULL));
	int _size = -1;
	int max;
	orderCount = 0;

	do
	{
		system("cls");
		cout << "\n\n\n\n\n\n\n\n\n\n          생성할 빙고판의 크기를 입력하세요. (3 ~ 9) : ";
		cin >> _size;

		if (3 <= _size && _size <= 9)
		{
			size = _size;
			break;
		}

		system("cls");
		cout << "\n\n\n\n\n\n\n\n\n\n";
		cout << "          입력 값이 정확하지 않습니다.";
		Sleep(1000);
	} while (true);

	minX = 4;
	minY = 5;
	maxY = minY + 2 * (size - 1);
	maxX = minX + 5 * (size - 1);
	max = size * size;

	mapForUser = new int *[size];
	for (int i = 0; i < size; i++)
		mapForUser[i] = new int[size];

	mapForCom = new int *[size];
	for (int i = 0; i < size; i++)
		mapForCom[i] = new int[size];

	int temp[81];
	int j = 0;
	for (int i = 1; i <= max; i++)
		temp[j++] = i;

	for (int i = 0; i < max; i++)
		swap(temp[(rand() % max - 1) + 1], temp[(rand() % max - 1) + 1]);

	int n = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			mapForUser[i][j] = temp[n];
			n++;
		}
	}

	for (int i = 0; i < max; i++)
		swap(temp[(rand() % max - 1) + 1], temp[(rand() % max - 1) + 1]);

	n = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			mapForCom[i][j] = temp[n];
			n++;
		}
	}

	repForUser = new int *[size];
	for (int i = 0; i < size; i++)
		repForUser[i] = new int[size];

	repForCom = new int *[size];
	for (int i = 0; i < size; i++)
		repForCom[i] = new int[size];

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			repForUser[i][j] = mapForUser[i][j];
			repForCom[i][j] = mapForCom[i][j];
		}
	}

	return size;
}

void MHMoonGame::swap(int &x, int &y)
{
	int temp = x;
	x = y;
	y = temp;
}
int MHMoonGame::decision()
{
	int i, j;

	int userBingoCount = 0;
	int comBingoCount = 0;

	int rUser = 0;
	int cUser = 0;
	int clUser = 0;
	int crUser = 0;

	for (i = 0; i < size; i++)
	{
		rUser = 0;
		cUser = 0;

		for (j = 0; j < size; j++)
		{
			if (mapForUser[i][j] == 0 || mapForUser[i][j] == -1)
			{
				rUser++;
			}
			if (mapForUser[j][i] == 0 || mapForUser[j][i] == -1)
			{
				cUser++;
			}
		}
		if (mapForUser[i][i] == 0 || mapForUser[i][i] == -1)
		{
			clUser++;
		}
		if (mapForUser[size - 1 - i][i] == 0 || mapForUser[size - 1 - i][i] == -1)
		{
			crUser++;
		}

		if (rUser == size)
		{
			userBingoCount++;
		}
		if (cUser == size)
		{
			userBingoCount++;
		}
	}

	if (clUser == size)
	{
		userBingoCount++;
	}

	if (crUser == size)
	{
		userBingoCount++;
	}

	int rCom = 0;
	int cCom = 0;
	int clCom = 0;
	int crCom = 0;

	for (i = 0; i < size; i++)
	{
		rCom = 0;
		cCom = 0;

		for (j = 0; j < size; j++)
		{
			if (mapForCom[i][j] == 0 || mapForCom[i][j] == -1)
			{
				rCom++;
			}
			if (mapForCom[j][i] == 0 || mapForCom[j][i] == -1)
			{
				cCom++;
			}
		}
		if (mapForCom[i][i] == 0 || mapForCom[i][i] == -1)
		{
			clCom++;
		}
		if (mapForCom[size - 1 - i][i] == 0 || mapForCom[size - 1 - i][i] == -1)
		{
			crCom++;
		}

		if (rCom == size)
		{
			comBingoCount++;
		}
		if (cCom == size)
		{
			comBingoCount++;
		}
	}

	if (clCom == size)
	{
		comBingoCount++;
	}

	if (crCom == size)
	{
		comBingoCount++;
	}

	if (orderCount >= size * size)
	{
		return 3;
	}
	else if ((userBingoCount == comBingoCount) && (userBingoCount > 0) && (comBingoCount > 0)) // 동시 빙고, 무승부
	{
		return 2;
	}
	else if (userBingoCount > comBingoCount) // 유저 승
	{
		return 1;
	}
	else if (userBingoCount < comBingoCount) // 컴퓨터 승
	{
		return 0;
	}
	else
	{
		return -1;
	}
}
void MHMoonGame::replay()
{
	for (int k = 0; k < orderCount; k++)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (k % 2 == 0)
				{
					if (repForUser[i][j] == orderForReplay[k])
					{
						repForUser[i][j] = 0;
					}
					if (repForCom[i][j] == orderForReplay[k])
					{
						repForCom[i][j] = 0;
					}
				}
				else if (k % 2 != 0)
				{
					if (repForUser[i][j] == orderForReplay[k])
					{
						repForUser[i][j] = -1;
					}
					if (repForCom[i][j] == orderForReplay[k])
					{
						repForCom[i][j] = -1;
					}
				}
			}
		}

		system("cls");
		printf("\n\n\n");
		printf("User\n\n");
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (repForUser[i][j] == 0)
				{
					textColor(9);
					printf("    O");
					textColor(15);
				}
				else if (repForUser[i][j] == -1)
				{
					textColor(12);
					printf("    X");
					textColor(15);
				}
				else
				{
					printf("%5d", repForUser[i][j]);
				}
			}
			printf("\n\n");
		}

		printf("\n");

		printf("Computer\n\n");
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (repForCom[i][j] == 0)
				{
					textColor(9);
					printf("    O");
					textColor(15);
				}
				else if (repForCom[i][j] == -1)
				{
					textColor(12);
					printf("    X");
					textColor(15);
				}
				else
				{
					printf("%5d", repForCom[i][j]);
				}
			}
			printf("\n\n");
		}

		Sleep(1000);
	}
	Sleep(3000);
}

void MHMoonGame::loadGame()
{
	ifstream load("savefile.txt");

	if (!load)
	{
		cerr << "파일 오류!" << endl;
		return;
	}
	else
	{
		load >> size;

		minX = 4;
		minY = 5;
		maxY = minY + 2 * (size - 1);
		maxX = minX + 5 * (size - 1);

		mapForUser = new int *[size];
		mapForCom = new int *[size];
		repForUser = new int *[size];
		repForCom = new int *[size];

		for (int i = 0; i < size; i++)
		{
			mapForUser[i] = new int[size];

			for (int j = 0; j < size; j++)
			{
				load >> mapForUser[i][j];
			}
		}

		for (int i = 0; i < size; i++)
		{
			mapForCom[i] = new int[size];

			for (int j = 0; j < size; j++)
			{
				load >> mapForCom[i][j];
			}
		}

		for (int i = 0; i < size; i++)
		{
			repForUser[i] = new int[size];

			for (int j = 0; j < size; j++)
			{
				load >> repForUser[i][j];
			}
		}

		for (int i = 0; i < size; i++)
		{
			repForCom[i] = new int[size];

			for (int j = 0; j < size; j++)
			{
				load >> repForCom[i][j];
			}
		}

		load >> orderCount;

		for (int i = 0; i < orderCount; i++)
		{
			load >> orderForReplay[i];
		}
	}
}

void MHMoonGame::saveGame()
{
	ofstream save("savefile.txt");
	if (!save)
	{
		cerr << "파일 입력 오류!" << endl;
		return;
	}
	else
	{
		save << size << endl;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				save << mapForUser[i][j] << " ";
			}
			save << endl;
		}

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				save << mapForCom[i][j] << " ";
			}
			save << endl;
		}

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				save << repForUser[i][j] << " ";
			}
			save << endl;
		}

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				save << repForCom[i][j] << " ";
			}
			save << endl;
		}

		save << orderCount << endl;
		for (int i = 0; i < orderCount; i++)
		{
			save << orderForReplay[i] << " ";
		}
		save << endl;
	}
}