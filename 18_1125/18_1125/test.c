#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

#define COLS 12
#define ROWS 12
#define COL 10
#define ROW 10
#define MINES 10

void init_mines(char mine[ROWS][COLS], char show[ROWS][COLS], int rows, int cols, int row, int col)
{
	int i, x, y;
	memset(mine, '0', rows*cols*sizeof(char));
	memset(show, '.', rows*cols*sizeof(char));
	for (i = 0; i < MINES; i++)
	{
		while (1)
		{
			x = rand() % row + 1;
			y = rand() % col + 1;
			if (mine[x][y] == '0')
			{
				mine[x][y] = '1';
				break;
			}
		}
	}
}

void display(char mine[ROWS][COLS], int row, int col)
{
	int i, j;
	for (i = 1; i <= row; i++)
	{
		printf("%4d", i);
	}
	printf("\n");
	for (i = 1; i <= col; i++)
	{
		printf("%2d", i);
		for (j = 1; j <= col; j++)
		{
			printf(" %c  ", mine[i][j]);
		}
		printf("\n");
	}
}

static char checkmine(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y)
{
	int m, n;
	char mine_count = '0';
	for (m = x - 1; m <= x + 1; m++)
	{
		for (n = y - 1; n <= y + 1; n++)
		{
			if (mine[m][n] == '1')
				mine_count++;
		}
	}
	return mine_count;
}

int checkwin(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col, int x, int y)
{
	int count = 0;
	if (mine[x][y] == '0')
		show[x][y] = checkmine(mine, show, x, y);
	else return '*';
	for (x = 1; x <= row; x++)
	{
		for (y = 1; y <= col; y++)
		{
			if (show[x][y] == '.')
				count++;
		}
	}
	if (count == MINES)
		return 'w';
	return 0;
}
void menu()
{
	printf("*********  Welcom  to  Mines  *********\n");
	printf("***************************************\n");
	printf("*      1.play             0.exit      *\n");
	printf("***************************************\n");
}
void game()
{
	char mines[ROWS][COLS], show_area[ROWS][COLS], ret;
	int x, y;
	init_mines(mines, show_area, ROWS, COLS, ROW, COL);
	display(mines, ROW, COL);
	display(show_area, ROW, COL);
	while (1)
	{
		printf("Input x and y(like x y):");
		scanf("%d %d", &x, &y);
		if (x >= 1 && x <= ROW && y >= 1 && y <= COL)
		{
			ret = checkwin(mines, show_area, ROW, COL, x, y);
			if (ret == 'w')
			{
				display(mines, ROW, COL);
				printf("Congratulations£¡You win!\n");
				break;
			}
			else if (ret == '*')
			{
				display(mines, ROW, COL);
				printf("You lose!Good luck next time!\n");
				break;
			}
			else
			{
				display(show_area, ROW, COL);
				printf("\n");
			}
		}
		else printf("Input error!Please try again.\n");
	}
}
int main()
{
	int choice;
	srand((unsigned int)time(NULL));
	do
	{
		menu();
		printf("Input your choice:");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			game();
			break;
		case 0:
			break;
		default:
			printf(" Input error!Please try again.\n");
			break;
		}
	} while (choice);
	return 0;
}