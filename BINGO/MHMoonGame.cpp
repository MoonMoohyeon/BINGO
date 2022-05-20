#include "MHMoonGame.h"

void  MHMoonGame::setCursorView(bool visible) {
	CONSOLE_CURSOR_INFO cursor = { 1, visible };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
void  MHMoonGame::gotoxy(int x, int y) {
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void MHMoonGame::textColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int MHMoonGame::showMenu()
{
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

	/*
		1. 반환값이 명확히 떨어지는 값이 아니라 cursor의 Y좌표에서 10을 뺀 값인 형태는 좋지 않음. 상수를 선언하여 해결
		2. 루프 한 번당 입력을 두 번(getch가 두 번씩 호출됨) 받는 동작이 잘 이해가 되지 않음. :
			해결 : https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2012/078sfkak(v=vs.110)
		3. switch case문의 각 case는 항상 break가 되어야 함. 예를 들어 case UP에서 cursor Y가 10 이하라면 break가 실행되지 않고 그대로 case DOWN이 실행됨
	*/

	while (1)
	{
		gotoxy(cursorX, cursorY);
		ch = _getch();

		if (ch == ENTER)
		{
			return cursorY - CURSOR_Y_MIN;		// 현재 Y 좌표에서 Y 좌표 최솟값을 뺀다. 10이라는 리터럴 상수 사용 지양.
			break;
		}

		if (ch == 0xE0)		// msdn에 0xE0으로 적혀 있으므로 224에서 0xE0으로 수정. 이런 의미를 알 수 없는 값엔 주석을 달아주는 것이 좋음.
		{
			ch = _getch();
			switch (ch)
			{
			case UP:
				if (cursorY > CURSOR_Y_MIN)		// 리터럴 상수 사용 지양.
				{
					cursorY--;
				}
				break;			// break는 if 조건과 상관 없이 항상 실행되어야 함.
			case DOWN:
				if (cursorY < CURSOR_Y_MAX)		// 리터럴 상수 사용 지양.
				{
					cursorY++;
				}
				break;
			}
		}
	}
}
int MHMoonGame::createMap()
{
	int _size = -1;
	int max;

	system("cls");

	do
	{
		cout << "          생성할 빙고판의 크기를 입력하세요. (3 ~ 9) : ";
		cin >> _size;

		if (3 <= _size && _size <= 9) {
			size = _size;
			break;
		}

		system("cls");
		cout << "\n\n\n\n\n\n\n\n\n\n";
		cout << "          입력 값이 정확하지 않습니다.";
	} while (true);

	minX = 4;
	minY = 5;
	maxY = minY + 2 * (size - 1);
	maxX = minX + 5 * (size - 1);
	max = size * size;


	mapForUser = new int* [size];
	for (int i = 0; i < size; i++)
		mapForUser[i] = new int[size];

	mapForCom = new int* [size];
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
	return size;


}
void MHMoonGame::play()
{
	/*
		cout과 printf 혼용하지 말 것.
		cout으로 통일하길.
		iomanip 헤더파일의 기능을 사용하여 출력 형식을 맞추기에 용이하다.
	*/

	int sel = showMenu();
	switch (sel)
	{
	case 0:
		createMap();
		while (true)
		{
			inGameCursor();	// 매 게임 루프에서 숫자 선택 함수 호출

			int result = decision();	// 변수 이름으로 의미를 알기 힘든 n보다는 result가 더 나음
			if (result == 0) // 조건에서 !n보다는 n == 0으로 바꾸는 것이 더 가독성이 좋음
			{
				system("cls");
				printf("\n\n\n\n\n\n\n\n\n\n               컴퓨터 승리!\n\n\n\n\n");
				break;
			}
			else if (result == 1)
			{
				system("cls");
				printf("\n\n\n\n\n\n\n\n\n\n               유저 승리!\n\n\n\n\n");
				break;
			}
		}
		break;
	case 1:
		//Todo : Load Save File and Continue Game
		break;
	case 2:
		return; // play 함수가 return되면 어차피 main함수가 종료되고 프로그램이 끝나는데 굳이 exit를? 그리고 exit를 하면 아래 break는 실행되지 않는다.
	}
}

void MHMoonGame::showMap()
{
	printf("\n\n\n");
	printf("User\n\n");
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (mapForUser[i][j] == 0) printf("    O");		// == 0으로 하는 것이 더 가독성이 좋음
			else if (mapForUser[i][j] == -1) printf("    X");
			else printf("%5d", mapForUser[i][j]);
		}
		printf("\n\n");
	}

	printf("\n");

	printf("Computer\n\n");
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (mapForCom[i][j] == 0) printf("    O");		// == 0으로 하는 것이 더 가독성이 좋음
			else if (mapForCom[i][j] == -1) printf("    X");
			else printf("%5d", mapForCom[i][j]);
		}
		printf("\n\n");
	}
}
void MHMoonGame::inGameCursor()
{
	system("cls");
	showMap();
	cursorX = 4;
	cursorY = 5;

	while (1)
	{
		gotoxy(cursorX, cursorY);
		ch = _getch();
		if (ch == ENTER)
		{
			changeMap(cursorX, cursorY);
			break;
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
				break;		// showMenu와 같은 이유로 break는 if문 바깥에 있어야 함
			case DOWN:
				if (cursorY < maxY)
				{
					cursorY += 2;
				}
				break;		// showMenu와 같은 이유로 break는 if문 바깥에 있어야 함
			case LEFT:
				if (cursorX > minX)
				{
					cursorX -= 5;
				}
				break;		// showMenu와 같은 이유로 break는 if문 바깥에 있어야 함
			case RIGHT:
				if (cursorX < maxX)
				{
					cursorX += 5;
				}
				break;		// showMenu와 같은 이유로 break는 if문 바깥에 있어야 함
			}
		}
	}
}
void MHMoonGame::changeMap(int x, int y)
{
	int arrx = 0, arry = 0;
	int n = 0;

	// 너무 무식한 방법
	// for (n = 0; n < 10; n++)
	// {
	// 	if (x == 4 + n * 5) arrx = n;
	// 	if (y == 5 + n * 2) arry = n;
	// }

	// 개선된 코드
	arrx = (x - 4) / 5;
	arry = (y - 5) / 2;


	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (mapForCom[i][j] == mapForUser[arry][arrx])
			{
				mapForCom[i][j] = 0;
				break; // 각 숫자는 오직 한 개이므로 break를 하는 편이 나음
			}

		}
	}
	mapForUser[arry][arrx] = 0;
}
void MHMoonGame::swap(int& x, int& y)
{
	int temp = x;
	x = y;
	y = temp;
}
int MHMoonGame::decision()
{
	int i, j;
	int rUser = 0;
	int cUser = 0;
	int clUser = 0;
	int crUser = 0;
	int check = 0;
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
		if (rUser == size)
		{
			return 1;
		}
		if (cUser == size)
		{
			return 1;
		}
		if (mapForUser[i][i] == 0 || mapForUser[i][i] == -1)
		{
			clUser++;
		}
		if (mapForUser[size - 1 - i][i] == 0 || mapForUser[size - 1 - i][i] == -1)
		{
			crUser++;
		}
	}
	if (clUser == size)
	{
		return 1;
	}

	if (crUser == size)
	{
		return 1;
	}

	int rCom = 0;
	int cCom = 0;
	int clCom = 0;
	int crCom = 0;
	check = 0;
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
		if (rCom == size)
		{
			return 0;
		}
		if (cCom == size)
		{
			return 0;
		}
		if (mapForCom[i][i] == 0 || mapForCom[i][i] == -1)
		{
			clCom++;
		}
		if (mapForCom[size - 1 - i][i] == 0 || mapForCom[size - 1 - i][i] == -1)
		{
			crCom++;
		}
	}
	if (clCom == size)
	{
		return 0;
	}

	if (crCom == size)
	{
		return 0;
	}

	return 2;
}
void MHMoonGame::replay()
{

}

void MHMoonGame::saveGame()
{
}