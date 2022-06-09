#include "MHMoonGame.h"

MHMoonGame::~MHMoonGame()
{
	memoryDelete();
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

		if (result == -1) // �޴����� ���� ���� ���� ��
		{
			return;
		}

		while (true) // ���� ���� �� �̾��ϱ� ���� ��
		{
			int result = inGameCursor(); // �� ���� �������� ���� ���� �Լ� ȣ��
			if (result == -1)
			{
				break;
			}

			system("cls");
			textColor(12);
			cout << "\n\n\n\n\n\n\n\n\n\n               ��ǻ�� ��!" << endl;
			textColor(15);
			cout << "\n\n               201910162 ������" << endl;
			Sleep(1000);
			// ��ǻ�� �� �Լ� ����
			computerTurn();

			result = decision();
			if (result == 0)
			{
				system("cls");
				textColor(12);
				cout << "\n\n\n\n\n\n\n\n\n\n               ��ǻ�� �¸�!";
				textColor(15);
				cout << "\n\n               201910162 ������" << endl;
				Sleep(3000);
				replay();
				break;
			}
			else if (result == 1)
			{
				system("cls");
				textColor(9);
				cout << "\n\n\n\n\n\n\n\n\n\n               ���� �¸�!";
				textColor(15);
				cout << "\n\n               201910162 ������" << endl;
				Sleep(3000);
				replay();
				break;
			}
			else if (result == 2)
			{
				system("cls");
				cout << "\n\n\n\n\n\n\n\n\n\n               ���º�...!";
				cout << "\n\n               201910162 ������" << endl;
				Sleep(1000);
			}
			else if (result == 3)
			{
				system("cls");
				cout << "\n\n\n\n\n\n\n\n\n\n               ���º� ����.";
				cout << "\n\n               201910162 ������" << endl;
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
		 << "             ����    ����    ���    ��    �����      ����    \n"
		 << "             ��   ��     ��      �� ��   ��    ��           ��    ��   \n"
		 << "             �� ��       ��      ��  ��  ��    ��  ����  ��      ��  \n"
		 << "             ��   ��     ��      ��   �� ��    ��      ��   ��    ��   \n"
		 << "             ����    ����    ��    ���     �����     ����    \n\n"
		 << "                                 �� �� �� ��\n"
		 << "                                 �� �� �� ��\n"
		 << "                                 �� �� �� ��\n\n"
		 << "                                 201910162 ������\n";
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

		if (ch == 0xE0) // Ȯ��Ű
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
		<< "                                 �� �� �� ��\n"
		<< "                                 �� �� �� ��\n"
		<< "                                 �޴��� ���ư���\n\n"
		<< "                                 201910162 ������\n";
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

	printf("Computer\n\n"); // �ּ� ó��
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

	cout << "201910162 ������" << endl;
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

		if (ch == ENTER)
		{
			int valid = playerTurn(cursorX, cursorY);
			if (valid == 1) // �̹� ���õ� ĭ�� ���� ���ϵ���
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
	}
	return 0;
}
int MHMoonGame::playerTurn(int x, int y)
{
	int arrX = 0, arrY = 0;
	int n = 0;

	arrX = (x - 4) / 5;
	arrY = (y - 5) / 2;
	orderForReplay[orderCount++] = mapForUser[arrY][arrX]; // ������ ���� ���÷��̿� �迭�� ����.
	while (true)
	{
		if (mapForUser[arrY][arrX] == 0) // �̹� ���õ� ��
			return -1;
		if (mapForUser[arrY][arrX] == -1)
			return -1;
		else
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					if (mapForCom[i][j] == mapForUser[arrY][arrX])
					{
						mapForCom[i][j] = 0;
						break;
					}
				}
			}

			mapForUser[arrY][arrX] = 0;


			// ��ǻ�� �˰��� ���
			horizontal[arrX]++;
			vertical[arrY]++;
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					if (mapForCom[i][i] == 0 || mapForCom[i][i] == -1)
					{
						diagnal[0]++;
					}

					if (mapForCom[i][size - i - 1] == 0 || mapForCom[i][size - i - 1] == -1)
					{
						diagnal[1]++;
					}
				}
			}

			return 1;
		}
	}
}

void MHMoonGame::findBestPlay(int &outX, int &outY)
{
	unsigned int maxValue = 0; // �ִ� ��ġ
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			unsigned int temp = 1; // ��ġ
			if (mapForCom[i][j] == 0 || mapForCom[i][j] == -1)
			{
				continue;
			}

			if (i == j)
			{
				temp += 1 << (diagnal[0] + 1);

				if (diagnal[0] == size - 1)
				{
					temp += 1 << (diagnal[0] + 1);
				}
			}

			if ((size - i - 1) == j)
			{
				temp += 1 << (diagnal[1] + 1);

				if (diagnal[1] == size - 1)
				{
					temp += 1 << (diagnal[1] + 1);
				}
			}

			if (horizontal[i] == size - 1)
			{
				temp += 1 << horizontal[i];
			}
			if (vertical[j] == size - 1)
			{
				temp += 1 << vertical[j];
			}

			temp += 1 << horizontal[i];
			temp += 1 << vertical[j];

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

	// �������� ���� �� ��� �������� ����
	if (orderCount >= size * size)
	{
		return;
	}

	findBestPlay(arrX, arrY); // arrX, arrY�� ���� ���� ��ǥ�� ���.

	horizontal[arrX]++;
	vertical[arrY]++;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (mapForCom[i][i] == 0 || mapForCom[i][i] == -1)
			{
				diagnal[0]++;
			}

			if (mapForCom[i][size - i - 1] == 0 || mapForCom[i][size - i - 1] == -1)
			{
				diagnal[1]++;
			}
		}
	}

	orderForReplay[orderCount++] = mapForCom[arrX][arrY]; // ������ ���� ���÷��̿� �迭�� ����.

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (mapForUser[i][j] == mapForCom[arrX][arrY])
			{
				mapForUser[i][j] = -1;
				break;
			}
		}
	}

	mapForCom[arrX][arrY] = -1;
}

void MHMoonGame::createMap()
{
	memoryDelete();
	srand(time(NULL));
	int _size = -1;
	orderCount = 0;

	do
	{
		system("cls");
		cout << "201910162 ������" << endl;
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
		cout << "          201910162 ������" << endl;
		Sleep(1000);
	} while (true);

	// Ŀ�� ���� ����
	minX = 4;
	minY = 5;
	maxY = minY + 2 * (size - 1);
	maxX = minX + 5 * (size - 1);

	mapForUser = new int *[size];
	for (int i = 0; i < size; i++)
		mapForUser[i] = new int[size];

	mapForCom = new int *[size];
	for (int i = 0; i < size; i++)
		mapForCom[i] = new int[size];

	// ������ ����
	int temp[81];
	int max = size * size;
	int j = 0;
	for (int i = 1; i <= max; i++)
		temp[j++] = i;

	// ���� ������
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

	// ��ǻ�� ������
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

	// ���÷��̸� ���� �ʱ� ���� ������
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
}

void MHMoonGame::memoryDelete()
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
	else if ((userBingoCount == comBingoCount) && (userBingoCount > 0) && (comBingoCount > 0)) // ���� ����, ���º�
	{
		return 2;
	}
	else if (userBingoCount > comBingoCount) // ���� ��
	{
		return 1;
	}
	else if (userBingoCount < comBingoCount) // ��ǻ�� ��
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
				if (k % 2 == 0) // ������ �������� ��ǻ���� �������� �Ǵ�
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
		cout << "201910162 ������" << endl;
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
	memoryDelete();
	ifstream load("savefile.txt");

	if (!load)
	{
		cerr << "���� ����! 201910162 ������" << endl;
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
		cerr << "���� �Է� ����! 201910162 ������" << endl;
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