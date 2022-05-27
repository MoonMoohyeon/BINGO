#include "MHMoonGame.h"

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
	showMenu();
}

void MHMoonGame::showMenu()
{
	cout << "\n\n\n\n"
		 << "             ����    ����    ���    ��    �����      ����    \n"
		 << "             ��   ��     ��      �� ��   ��    ��           ��    ��   \n"
		 << "             �� ��       ��      ��  ��  ��    ��  ����  ��      ��  \n"
		 << "             ��   ��     ��      ��   �� ��    ��      ��   ��    ��   \n"
		 << "             ����    ����    ��    ���     �����     ����    \n\n"
		 << "                                 �� �� �� ��\n"
		 << "                                 �� �� �� ��\n"
		 << "                                 �� �� �� ��\n";
	const int CURSOR_X_MIN = 30;
	const int CURSOR_Y_MIN = 10;
	const int CURSOR_Y_MAX = 12;

	cursorX = CURSOR_X_MIN;
	cursorY = CURSOR_Y_MIN;

	/*
		1. ��ȯ���� ��Ȯ�� �������� ���� �ƴ϶� cursor�� Y��ǥ���� 10�� �� ���� ���´� ���� ����. ����� �����Ͽ� �ذ�
		2. ���� �� ���� �Է��� �� ��(getch�� �� ���� ȣ���) �޴� ������ �� ���ذ� ���� ����. :
			�ذ� : https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2012/078sfkak(v=vs.110)
		3. switch case���� �� case�� �׻� break�� �Ǿ�� ��. ���� ��� case UP���� cursor Y�� 10 ���϶�� break�� ������� �ʰ� �״�� case DOWN�� �����
	*/

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
				while (true)
				{
					inGameCursor(); // �� ���� �������� ���� ���� �Լ� ȣ��
					system("cls");
					cout << "\n\n\n\n\n\n\n\n\n\n               ��ǻ�� ��!" << endl;
					Sleep(1000);
					computerTurn();

					int result = decision();
					if (result == 0)
					{
						system("cls");
						printf("\n\n\n\n\n\n\n\n\n\n               ��ǻ�� �¸�!\n\n\n\n\n");
						replay();
						break;
					}
					else if (result == 1)
					{
						system("cls");
						printf("\n\n\n\n\n\n\n\n\n\n               ���� �¸�!\n\n\n\n\n");
						replay();
						break;
					}
					else if (result == 2)
					{
						system("cls");
						printf("\n\n\n\n\n\n\n\n\n\n               ���º�...!\n\n\n\n\n");
						Sleep(1000);
					}
				}
				break;
			case 1:
				// Todo : Load Save File and Continue Game
				break;
			case 2:
				exit(0);
			}
			break;
		}

		if (ch == 0xE0) // msdn�� 0xE0���� ���� �����Ƿ� 224���� 0xE0���� ����. �̷� �ǹ̸� �� �� ���� ���� �ּ��� �޾��ִ� ���� ����.
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
}

void MHMoonGame::inGameMenu()
{
	cout << "\n\n\n\n\n\n\n\n\n\n"
		 << "                                 �� �� �� ��\n"
		 << "                                 �� �� �� ��\n"
		 << "                                 �޴��� ���ư���\n";
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
			if (sel == 0)
				break;
			else if (sel == 1)
			{
				savegame();
			}
			else if (sel == 2)
			{
				showMenu();
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
				printf("    O");
			else if (mapForUser[i][j] == -1)
				printf("    X");
			else
				printf("%5d", mapForUser[i][j]);
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
				printf("    O");
			else if (mapForCom[i][j] == -1)
				printf("    X");
			else
				printf("%5d", mapForCom[i][j]);
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
			if (playerTurn(cursorX, cursorY) == 0)
			{
				break;
			}
			else
			{
				// �̹� 0���� �ٲ� ĭ�� ���� ���ϰ� �ϰ� ������ ������...
			}
		}
		else if (ch == ESC)
		{
			inGameMenu();
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
}
void MHMoonGame::computerTurn()
{
	srand(time(NULL));
	int arrX, arrY;
	int temp;

	while (true)
	{
		void showMap();
		arrX = rand() % (size);
		arrY = rand() % (size);
		if (mapForCom[arrX][arrY] != 0)
		{
			break;
		}
	}
	orderForReplay[orderCount++] = mapForCom[arrX][arrY]; // ������ ���� ���÷��̿� �迭�� ����.

	mapForCom[arrX][arrY] = 0;
	mapForUser[arrX][arrY] = 0;
}
int MHMoonGame::playerTurn(int x, int y)
{
	int arrx = 0, arry = 0;
	int n = 0;

	// ������ �ڵ�
	arrx = (x - 4) / 5;
	arry = (y - 5) / 2;

	if (mapForUser[arry][arrx] == 0) // �̹� 0���� �ٲ� ĭ�� ���� ���ϰ� �ϰ� ������ ������...
	{
		cout << "�̹� ���õ� ĭ�Դϴ�." << endl;
		Sleep(1000);
		return -1;
	}
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
		orderForReplay[orderCount++] = mapForUser[arry][arrx]; // ������ ���� ���÷��̿� �迭�� ����.

		mapForUser[arry][arrx] = 0;
	}
	return 0;
}
int MHMoonGame::createMap()
{
	int _size = -1;
	int max;
	orderCount = 0;

	do
	{
		system("cls");
		cout << "\n\n\n\n\n\n\n\n\n\n          ������ �������� ũ�⸦ �Է��ϼ���. (3 ~ 9) : ";
		cin >> _size;

		if (3 <= _size && _size <= 9)
		{
			size = _size;
			break;
		}

		system("cls");
		cout << "\n\n\n\n\n\n\n\n\n\n";
		cout << "          �Է� ���� ��Ȯ���� �ʽ��ϴ�.";
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

	// �����Ҵ�...?
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
	int rUser = 0;
	int cUser = 0;
	int clUser = 0;
	int crUser = 0;
	int check = 0;

	int drawCount;
	int userWin = 0;
	int comWin = 0;
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
			userWin = 1;
		}
		if (cUser == size)
		{
			userWin = 1;
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
		userWin = 1;
	}

	if (crUser == size)
	{
		userWin = 1;
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
			comWin = 1;
		}
		if (cCom == size)
		{
			comWin = 1;
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
		comWin = 1;
	}

	if (crCom == size)
	{
		comWin = 1;
	}

	if (userWin == 1 && comWin == 1) // ���� ����, ���º�
	{
		// ==> ���� ����!!!!! �� �� ���º� �߸� ������ ���ºεǴ� ����, ���� �ʿ� drawCount ���� ���� ����
		return 2;
	}
	else if (userWin == 1 && comWin != 1) // ���� ��
	{
		return 1;
	}
	else if (userWin != 1 && comWin == 1) // ��ǻ�� ��
	{
		return 0;
	}
	else
	{
		return 3; // ���� ����
	}
}
void MHMoonGame::replay()
{
	// ���÷��� ����ٰ� �������. ó������ �ٽ� �������� �� ���Ƽ� ������.
	int p = 0;
	for (int k = orderCount; k > 0; k--)
	{
		system("cls");
		printf("\n\n\n");
		printf("User\n\n");
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (repForUser[i][j] == 0)
					printf("    O");
				else if (repForUser[i][j] == -1)
					printf("    X");
				else
					printf("%5d", repForUser[i][j]);
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
					printf("    O");
				else if (repForCom[i][j] == -1)
					printf("    X");
				else
					printf("%5d", repForCom[i][j]);
			}
			printf("\n\n");
		}

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (repForUser[i][j] == orderForReplay[p])
				{
					repForUser[i][j] = 0;
				}
			}
		}

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (mapForCom[i][j] == orderForReplay[p])
				{
					mapForCom[i][j] = 0;
					p++;
				}
			}
		}
		Sleep(1000);
	}
}

void MHMoonGame::saveGame()
{
	ofstream save("savefile.txt");
	if (!save)
	{
		cerr << "���� �Է� ����!" << endl;
		exit(-1);
	}
	else
	{
		save << size << endl;
		for (int i = 0; i < size; i++)
		{
			for (int j = j; j < size; j++)
			{
				save << mapForUser[i][j];
			}
			save << endl;
		}

		for (int i = 0; i < size; i++)
		{
			for (int j = j; j < size; j++)
			{
				save << mapForComs[i][j];
			}
			save << endl;
		}
	}
}