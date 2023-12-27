// C program to build the complete 
// snake game 
#include <conio.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <windows.h> 
#include <time.h>
#include <iostream>
int i, j, height = 20, width = 20;
int gameover, score;
int x, y, fruitx, fruity, flag;
int tailX[100], tailY[100];
int nTail;
bool print;
int delaytime = 100;
// Function to generate the fruit 
// within the boundary 
void setup()
{
	gameover = 0;
	srand(time(NULL));

	// Stores height and width 
	x = height / 2;
	y = width / 2;
label1:
	fruitx = rand() % 20;
	if (fruitx == 0)
		goto label1;
label2:
	fruity = rand() % 20;
	if (fruity == 0)
		goto label2;
	score = 0;
}

// Function to draw the boundaries 
void draw()
{
	system("cls");//clear previous movement
	for (i = 0; i < width + 2; i++) {
		printf("#");
	}
	printf("\n");
	for (i = 1; i <= height; i++) {
		for(j =1;j<=width+1;j++){
			if (j == 1 || j== width +1) {
				printf("#");
			}
			if (i == y && j == x) {
				printf("0");
			}
			else if (j == fruitx && i == fruity) {
				printf("*");
			}
			else {
					print = false;
					for (int k = 0; k < nTail; k++)
					{
						if (tailX[k] == j && tailY[k] == i)
						{
							printf("0");
							print = true;
						}
					}
					if (!print)
						printf(" ");
				}
			}
			printf("\n");
		}
		for (i = 0; i < width + 2; i++) {
			printf("#");
		}
		printf("\n");


	// Print the score after the 
	// game ends 
	printf("\n\n----------------------------\nscore = %d", score);
	printf("\n");
	printf("press X to quit the game");
}

// Function to take the input 
void input()
{
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			flag = 1;
			break;
		case 's':
			flag = 2;
			break;
		case 'd':
			flag = 3;
			break;
		case 'w':
			flag = 4;
			break;
		case 'x':
			gameover = 1;
			break;
		}
	}
}

// Function for the logic behind 
// each movement 
void logic()
{
	Sleep(delaytime); 

	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	
	switch (flag) {
	case 1:
		x--;
		break;
	case 2:
		y++;
		break;
	case 3:
		x++;
		break;
	case 4:
		y--;
		break;
	default:
		break;
	}

	// If the game is over 
	if (x < 0 || x > height || y < 0 || y > width) {
		gameover = 1;
		printf("\n\nGame Over!!!\n");
		printf("You Hit The Wall!!\n");
	}

	// If hit the tail 
	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			printf("\n\nGame Over!!!\n");
			printf("You Hit The Tail!!\n");
		}
	}

	// If snake reaches the fruit 
	// then update the score 
	if (x == fruitx && y == fruity) {
	label3:
		fruitx = rand() % 20;
		if (fruitx == 0)
			goto label3;

		// After eating the above fruit 
		// generate new fruit 
	label4:
		fruity = rand() % 20;
		if (fruity == 0)
			goto label4;
		score += 10;
		nTail++;
	}
}


void menu() {
	int choice;

	// ��ܹC�����
	std::cout << "�C�����:" << std::endl;
	std::cout << "1. ²��Ҧ�" << std::endl;
	std::cout << "2. �x���Ҧ�" << std::endl;

	// �������a�����
	std::cout << "�п�����ס]1��2�^: ";
	std::cin >> choice;

	// �ھڿ�ܳ]�m�C���t��
	if (choice == 1) {
		std::cout << "�A��ܤF²��Ҧ��C�C���t�׳]�m���C�t�C" << std::endl;
		delaytime = 50;
		// �b�o�̲K�[�]�m�C�t���N�X
	}
	else if (choice == 2) {
		std::cout << "�A��ܤF�x���Ҧ��C�C���t�׳]�m���ֳt�C" << std::endl;
		// �b�o�̲K�[�]�m�ֳt���N�X
		delaytime = 100;
	}
	else {
		std::cout << "�L�Ī���ܡC�п�J1��2�C" << std::endl;
	}

}

// Driver Code 
int main()
{
	// Generate boundary 
	setup();
	menu();
	// Until the game is over 
	while (!gameover) {

		// Function Call 
		draw();
		input();
		logic();
	}
}
