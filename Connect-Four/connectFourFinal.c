#include "connectFourFinal.h"

/*Initializing board*/
void init_board(Cell board[][MAX_COL], int rows, int cols) {
	int row_index = 0, col_index = 0;

	for (row_index = 0; row_index < rows; ++row_index)
	{
		for (col_index = 0; col_index < cols; ++col_index)
		{
			board[row_index][col_index].color = '\0';
			board[row_index][col_index].isOccupied = FALSE;
			board[row_index][col_index].place.row = row_index;
			board[row_index][col_index].place.col = col_index;
		}
	}
}

/*Printing board*/
void print_board(Cell board[][MAX_COL])
{
	int row_index = 0, col_index = 0;

	for (int i = 1; i <= MAX_COL; i++)
	{
		printf("%d ", i);
	}
	printf("\n");
	for (row_index = 0; row_index < MAX_ROW; row_index++)
	{
		for (col_index = 0; col_index < MAX_COL; col_index++)
		{
			if (board[row_index][col_index].color == '\0')
			{
				printf("~ ");
			}
			else
			{
				printf("%c ", board[row_index][col_index].color);
			}
		}
		printf("\n");
	}
	printf("\n");
}



/*THis function takes in the player as a char and the a two dimensional array of
structs as the board and has another function within it. It is essentially a full turn.
It returns changes to the board depending on what the player does on his or her turn.*/
void turn(Cell board[][MAX_COL], char player) {
	int chosen_col = 0, valid_input = 0, valid_scan = 0;
	char color[5];
	switch (player)
	{
	case 'R':
		strcpy(color, "Red");
		break;
	case 'B':
		strcpy(color, "Blue");
		break;
	}

	printf("%s player, please enter the number of the column you would like to\ndrop your next piece:\n", color);
	while (!valid_input)
	{
		char input = '\0';
		scanf(" %c", &input);

		if (input > 48 && input < 56)
		{
			chosen_col = atoi(&input);
		}
		if (chosen_col)
		{
			valid_scan = 1;
		}
		if (valid_scan)
		{
			if (chosen_col < 8 && chosen_col > 0)
			{
				if (validate_move(board, chosen_col - 1))
				{
					for (int i = 5; i >= 0; i--)
					{
						if (board[i][chosen_col - 1].isOccupied == FALSE)
						{
							board[i][chosen_col - 1].isOccupied = TRUE;
							board[i][chosen_col - 1].color = player;
							break;
						}
					}
					valid_input = 1;
				}
				else
				{
					printf("That column is full, please enter another column:\n");
					chosen_col = 0;
				}
			}
			else
			{
				printf("Please enter a valid column number (1 - 7):\n");

			}
		}
		else
		{
			printf("Please enter a digit (1 - 7 ):\n");
		}
	}
}

/*This function also takes in the board as a two dimensional array of structs as well as the
number of the column in which the player chose to place their piece. If the column isnt
full it returns a one, otherwise it returns a zero.*/
int validate_move(Cell board[][MAX_COL], int chosen_col) {
	for (int i = 0; i < 6; i++)
	{
		if (board[i][chosen_col].isOccupied == FALSE)
		{
			return 1;
		}
		i++;
	}
	return 0;
}

/*This function has other functions within it and it checks whether the player who just had a turn
has won or not. It takes in a board as a parameter, that being a two dimensional array of structs as well
as a Winner type pointer and a char pointer to the player. It returns a winner indirectly if there is one,
and changes the turn to the other player through the char pointer. Also, it has other more specific fuctions within it
to check whether the player won or not.*/
void check_for_win(Cell board[][MAX_COL], Winner *winner, char *player) {
	int row_index = 0, col_index = 0, win = 0;

	for (row_index = 0; row_index < MAX_ROW; ++row_index)
	{
		for (col_index = 0; col_index < MAX_COL; ++col_index)
		{
			if (check_diagonal(board, row_index, col_index))
				win = 1;
			if (check_vertical(board, row_index, col_index))
				win = 1;
			if (check_horizontal(board, row_index, col_index))
				win = 1;
			if (win)
			{
				switch (*player)
				{
				case 'R':
					*winner = RED;
					break;
				case 'B':
					*winner = BLUE;
					break;
				}
			}
		}
	}
	switch (*player)
	{
	case 'R':
		*player = 'B';
		break;
	case 'B':
		*player = 'R';
		break;
	}
}

/*This function checks whether the player won with a diagonal 4.
It takes in two ints as parameters (row and col), and a board in the form of
a two dimensional array of structs. If the player has won it returns a 1 otherwise it returns a 0.*/
int check_diagonal(Cell board[][MAX_COL], int row, int col) {


	if (board[row][col].color)
	{
		int i = 1;
		while (i < 5)
		{
			if (board[row][col].color == *(&board[row][col].color + sizeof(Cell) * 6 * i))
			{
				i++;
				if (i == 4)
					return 1;
			}
			else
				break;
		}

		i = 1;
		while (i < 5)
		{
			if (board[row][col].color == *(&board[row][col].color + sizeof(Cell) * 8 * i))
			{
				i++;
				if (i == 4)
					return 1;
			}
			else
				break;
		}
	}
	return 0;

}

/*This function checks whether the player won with a vertical 4.
It takes in two ints as parameters (row and col), and a board in the form of
a two dimensional array of structs. If the player has won it returns a 1 otherwise it returns a 0.*/
int check_vertical(Cell board[][MAX_COL], int row, int col) {
	if (board[row][col].color)
	{
		int i = 1;
		while (i < 5)
		{
			if (board[row][col].color == *(&board[row][col].color + sizeof(Cell) * 7 * i))
			{
				i++;
				if (i == 4)
					return 1;
			}
			else
				break;
		}
	}
	return 0;
}

/*This function checks whether the player won with a horizontal 4.
It takes in two ints as parameters (row and col), and a board in the form of
a two dimensional array of structs. If the player has won it returns a 1 otherwise it returns a 0.*/
int check_horizontal(Cell board[][MAX_COL], int row, int col) {

	if (board[row][col].color)
	{
		int i = 1;
		while (i < 5)
		{
			if (board[row][col].color == *(&board[row][col].color + sizeof(Cell) * i))
			{
				i++;
				if (i == 4)
					return 1;
			}
			else
				break;
		}
	}
	return 0;
}
