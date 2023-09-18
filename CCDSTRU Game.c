#include <stdio.h>
#include <stdlib.h>

typedef char string[3]; //there is no string data type in C so we create our own string data type

void printBoard (char board[][4], int turn) { // prints the board and updates the board
	printf("----------------------------------------------");
	if (turn == 1) {
		printf("\nPlayer 1's Turn (CHA)\n");
	}
	else if (turn == 0) {
		printf("\nPlayer 2's Turn (ORD)\n");
	}
	printf("\n    A   B   C   D\n  _________________\n");
	printf("1 | %c | %c | %c | %c |\n2 | %c | %c | %c | %c |\n3 | %c | %c | %c | %c |\n4 | %c | %c | %c | %c |\n",
	board[0][0], board[0][1], board[0][2], board[0][3], board[1][0], board[1][1], board[1][2], board[1][3],
	board[2][0], board[2][1], board[2][2], board[2][3], board[3][0], board[3][1], board[3][2], board[3][3] );
	printf("  -----------------\n");
	
	if (turn == 2) {
		printf("Player 1 (CHA) WINS ! !\n\n");
	}
	else if (turn == 3) {
		printf("Player 2 (ORD) WINS ! ! \n\n");
	}
}

int chaWin (char board[][4]) { // win condition for Player 1 (Cha), return 1 for win, return 0 if not yet
	if (board[0][3] == 'O' && board[1][3] == 'O' && board[2][3] == 'O') {
		return 1;
	}
	else if (board[1][1] == 'O' && board[2][2] == 'O' && board[3][3] == 'O') {
		return 1;
	}
	else if (board[1][2] == 'O' && board[2][1] == 'O' && board[3][0] == 'O') {
		return 1;
	}
	else if (board[3][1] == 'O' && board[3][2] == 'O' && board[3][3] == 'O') {
		return 1;
	}
	else {
		return 0;
	}
}

int ordWin (char board[][4]) { // win condition for Player 2 (Ord), return 1 for win, return 0 if not yet
	int i, j;
	int acc = 0;
	
	if (board[0][3] == ' ') {
		acc++;
	}
	for (i = 1; i < 3; i++) {
		for (j = 1; j < 4; j++) {
			if (board[i][j] == ' ') {
				acc++;
			}
		}
	}
	for (j = 0; j < 4; j++) {
		if (board[3][j] == ' ') {
			acc++;
		}
	}
	if (acc == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

int checkInput (char input[]) { // checks if the input is valid and returns the index of the coordinates chosen by the user on the board array.
	char x = input[0];			// Example: (Input: D3) (Return: 23)  // Example: (Input: H5) (Return: -1) // Example: (Input: asdad) (Return: -1)
	char y = input[1];
	int z;
	if((input[2] == '\0') && ((x >= 'a' && x <= 'd') || (x >= 'A' && x <= 'D')) && (y >= '1' && y <= '4')) {
		z = ((int)(y) - 49) * 10;
		if (x == 'a' || x == 'A') {
			return z + 0;
		}
		if (x == 'b' || x == 'B') {
			return z + 1;
		}
		if (x == 'c' || x == 'C') {
			return z + 2;
		}
		if (x == 'd' || x == 'D') {
			return z + 3;
		}
	}
	printf("\nINVALID INPUT!\n");
	return -1;	
}

int main()
{
	char board[4][4];
	int i, j, cdn;
	string input;
	
	//System Initialization
	int turn = 1;
	int ord = 0;
	int cha = 0;
	
	
	//Board Initialization
	for (i = 0; i < 4; i++)	 {
		for (j = 0; j < 4; j++) {
			board[i][j] = ' ';
		}
	}  
	//Game Instructions
	printf("Coordinate format:\n	Letter and Number (Example: A1, B3, D3, C4).\n\n");
	printf("Game Restrictions:\n	1. Player 1 (Cha) cannot occupy the positions A1, A2, A3, B1, C1.\n	2. Player 2 (Ord) can only have 4 positions at maximum.\n\n");
	printf("Win Conditions for Player 1 (Cha):\n	Should get a 3-in-a-row in one the following coordinates in any order:\n	1. D1, D2, D3\n	2. B2, C3, D4\n	3. C2, B3, A4\n	4. B4, C4, D4\n\n");
	printf("Win Conditions for Player 2 (Ord):\n	Prevent Player 1 from getting the winning coordinates until Player 1 cannot occupy any positions anymore.\n\nGOOD LUCK ! ! !\n");
	
	// Next Player Move
	while (chaWin(board) == 0 && ordWin(board) == 0) {
		printBoard(board, turn);
		
		do {
		printf("\nInput Coordinates: ");
		scanf("%s", input);
		} while (checkInput(input) == -1);
		
		cdn = checkInput(input);
		i = cdn / 10;
		j = cdn % 10;
		
		if (turn && (cdn != 0 && cdn != 1 && cdn != 2 && cdn != 10 && cdn != 20) && board[i][j] == ' ') { // as seen in the specs
			system("cls");
			board[i][j] = 'O';
			cha++;
			turn = !turn;
		}
		if (!turn && board[i][j] == ' ' && ord < 4) { // as seen in the specs
			system("cls");
			board[i][j] = 'X';
			ord++;
			turn = !turn;
		}
		if (!turn && ord == 4 && board[i][j] == 'X') { // as seen in the specs
			system("cls");
			board[i][j] = ' ';
			ord--;
		}
		if (turn && (cdn == 0 || cdn == 1 || cdn == 2 || cdn == 10 || cdn == 20)) {
			system("cls");
			printf("Player 1 (Cha) cannot occupy this position! Try another position. \n");
		}
		if (!turn && ord == 4 && board[i][j] == ' ') {
			system("cls");
			printf("Player 2 (Ord) cannot have more than 4 positions! Please remove one of your positions.\nInput the coordinates of the 'X' that you want to remove. \n");
		}
		if (board[i][j] != ' ') {
			system("cls");
			printf("This position is already occupied. Please choose another position. \n");
		}
	}

	// Game Over
	if (chaWin(board) == 1) {
		printBoard(board, 2);
		printf("Pieces used: %d", cha);
	}
	else if (ordWin(board) == 1) {
		printBoard(board, 3);
	}
	return 0;
}
