#include <conio.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <windows.h> 
#include <time.h>

int i, j, height = 20, width = 20;
int preox, preoy; //for the position os obstacle 
int score=0,sleep_time=100;
int x, y, fruitx, fruity, flag, obX, obY;
int tailX[100], tailY[100];
int nTail=0;
bool print,gameover;
int delaytime = 100;

// Function to generate the fruit 
// within the boundary 
void setup()
{
	gameover = false;
	srand((unsigned int)time(NULL));	

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
	nTail = 0;
	preox = 0;
	preoy = 0;
	sleep_time = 100;
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
		for(j =1 ; j<= width+1 ; j++)
		{
			if (j == 1 || j== width +1) 
				printf("#");

			if (i == y && j == x) 
				printf("Q");
			
			else if (j == fruitx && i == fruity) 
				printf("*");

			//===
			else if (i == obY && j == obY && score >= 40)
			{
				preox = i;
				preoy = j;
				printf("=====");
				j += 4;
			}
			
			else {
					print = false;
					for (int k = 0; k < nTail; k++)
					{
						if (tailX[k] == j && tailY[k] == i)
						{
							printf("o");
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
		// Print the score after the 
		// game ends 
		printf("\n\n----------------------------\nscore = %d", score);
		printf("\nob:  %d, %d", obX, obY); //next obstacle
		printf("\npreo: %d, %d", preox, preoy); // next obstacle for now
		printf("\npress X to quit the game");
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
			gameover = true;
			break;
		}
	}
}

// Function for the logic behind 
// each movement 
void logic()
{
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
		printf("\n\nGame Over!!!\n");
		printf("You Hit The Wall!!\n");
		gameover = true;
	}

	// If hit the obstacle 
	if (x >= preox && x < (preox + 6) && (y == preoy)) {
		gameover = true;
		printf("\n\nGame Over!!!\n");
		printf("You Hit The obstacle!!\n");
	}

	// If hit the tail 
	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			printf("\n\nGame Over!!!\n");
			printf("You Hit The Tail!!\n");
			gameover = true;
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

	if (score >= 50) {
		sleep_time = 50;
		}
	else if (score >= 100) {
		sleep_time = 10 * rand() % 5;
	}
	if (score >= 40) { //obstacle
		obX = rand() % 15;
		obY = rand() % 15;
	}

}
}

void menu() {
	int choice;

	// 顯示遊戲菜單
	printf("Menu : \n");
	printf("1. Easy Mode \n");
	printf("2. Hard Mode \n");

	// 接收玩家的選擇
	printf( "Enter 1 for Easy / 2 for Hard : \n");
	scanf("%d", &choice);

	// 根據選擇設置遊戲速度
	if (choice == 1) {
		printf( "You choose Easy Mode. Speed Slow \n");
		delaytime = 50;
		// 在這裡添加設置慢速的代碼
	}
	else if (choice == 2) {
		printf("You choose Hard Mode. Speed Fast \n");
		// 在這裡添加設置快速的代碼
		delaytime = 100;
	}
	else {
		printf("ERROR!!! Please enter 1 or 2 \n");
	}

}

// Driver Code 
int main() {
	char playAgain;

	do {
		setup();
		menu();
		while (!gameover) {
			draw();
			input();
			logic();
			Sleep(sleep_time);
		}
		printf("\nDo you want to play again? Press 'X' to exit or any other key to play again: \n");
		playAgain = _getch();
	} while (playAgain != 'x' && playAgain != 'X');

	return 0;
}