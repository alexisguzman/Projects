//Alexis Guzman
//CptS 121
//Connect Four Extra Credit
//2/16/16


#include "connectFourFinal.h"

int main(void)
{
	//Initializing variables
	Cell board[MAX_ROW][MAX_COL] = { { { '\0', FALSE,{ 0, 0 } } } };
	srand(time(NULL));
	Winner winning_player = 0;
	char player = 0, board_full = 0;
	int whose_turn = rand() % 2 + 1;

	//Choosing first turn at random
	switch (whose_turn)
	{
	case 1:
		player = 'R';
		break;
	case 2:
		player = 'B';
		break;
	}

	init_board(board, MAX_ROW, MAX_COL);

	/*Game goes on as long as the board isnt full and there is no winner*/
	while (!winning_player && !board_full)
	{
		system("cls");
		print_board(board);
		turn(board, player);
		system("cls");
		print_board(board);
		check_for_win(board, &winning_player, &player);
	}

	//Congratulates player who won, if there is a winner
	switch (winning_player)
	{
	case RED:
		printf("Congratulations, red player! You have won.\n");
		break;
	case BLUE:
		printf("Congratulations, blue player! You have won.\n");
		break;
	}

	return 0;

}