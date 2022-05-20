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
			return cursorY - CURSOR_Y_MIN;		// ���� Y ��ǥ���� Y ��ǥ �ּڰ��� ����. 10�̶�� ���ͷ� ��� ��� ����.
			break;
		}

		if (ch == 0xE0)		// msdn�� 0xE0���� ���� �����Ƿ� 224���� 0xE0���� ����. �̷� �ǹ̸� �� �� ���� ���� �ּ��� �޾��ִ� ���� ����.
		{
			ch = _getch();
			switch (ch)
			{
			case UP:
				if (cursorY > CURSOR_Y_MIN)		// ���ͷ� ��� ��� ����.
				{
					cursorY--;
				}
				break;			// break�� if ���ǰ� ��� ���� �׻� ����Ǿ�� ��.
			case DOWN:
				if (cursorY < CURSOR_Y_MAX)		// ���ͷ� ��� ��� ����.
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
		cout << "          ������ �������� ũ�⸦ �Է��ϼ���. (3 ~ 9) : ";
		cin >> _size;

		if (3 <= _size && _size <= 9) {
			size = _size;
			break;
		}

		system("cls");
		cout << "\n\n\n\n\n\n\n\n\n\n";
		cout << "          �Է� ���� ��Ȯ���� �ʽ��ϴ�.";
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
		cout�� printf ȥ������ �� ��.
		cout���� �����ϱ�.
		iomanip ��������� ����� ����Ͽ� ��� ������ ���߱⿡ �����ϴ�.
	*/

	int sel = showMenu();
	switch (sel)
	{
	case 0:
		createMap();
		while (true)
		{
			inGameCursor();	// �� ���� �������� ���� ���� �Լ� ȣ��

			int result = decision();	// ���� �̸����� �ǹ̸� �˱� ���� n���ٴ� result�� �� ����
			if (result == 0) // ���ǿ��� !n���ٴ� n == 0���� �ٲٴ� ���� �� �������� ����
			{
				system("cls");
				printf("\n\n\n\n\n\n\n\n\n\n               ��ǻ�� �¸�!\n\n\n\n\n");
				break;
			}
			else if (result == 1)
			{
				system("cls");
				printf("\n\n\n\n\n\n\n\n\n\n               ���� �¸�!\n\n\n\n\n");
				break;
			}
		}
		break;
	case 1:
		//Todo : Load Save File and Continue Game
		break;
	case 2:
		return; // play �Լ��� return�Ǹ� ������ main�Լ��� ����ǰ� ���α׷��� �����µ� ���� exit��? �׸��� exit�� �ϸ� �Ʒ� break�� ������� �ʴ´�.
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
			if (mapForUser[i][j] == 0) printf("    O");		// == 0���� �ϴ� ���� �� �������� ����
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
			if (mapForCom[i][j] == 0) printf("    O");		// == 0���� �ϴ� ���� �� �������� ����
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
				break;		// showMenu�� ���� ������ break�� if�� �ٱ��� �־�� ��
			case DOWN:
				if (cursorY < maxY)
				{
					cursorY += 2;
				}
				break;		// showMenu�� ���� ������ break�� if�� �ٱ��� �־�� ��
			case LEFT:
				if (cursorX > minX)
				{
					cursorX -= 5;
				}
				break;		// showMenu�� ���� ������ break�� if�� �ٱ��� �־�� ��
			case RIGHT:
				if (cursorX < maxX)
				{
					cursorX += 5;
				}
				break;		// showMenu�� ���� ������ break�� if�� �ٱ��� �־�� ��
			}
		}
	}
}
void MHMoonGame::changeMap(int x, int y)
{
	int arrx = 0, arry = 0;
	int n = 0;

	// �ʹ� ������ ���
	// for (n = 0; n < 10; n++)
	// {
	// 	if (x == 4 + n * 5) arrx = n;
	// 	if (y == 5 + n * 2) arry = n;
	// }

	// ������ �ڵ�
	arrx = (x - 4) / 5;
	arry = (y - 5) / 2;


	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (mapForCom[i][j] == mapForUser[arry][arrx])
			{
				mapForCom[i][j] = 0;
				break; // �� ���ڴ� ���� �� ���̹Ƿ� break�� �ϴ� ���� ����
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