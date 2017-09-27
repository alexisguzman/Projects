

/*******************************************************************************************
* Programmer: Alexis Guzman                                                                   *
* Class: CptS 121, Fall  2016; Lab Section 1                                           *
* Programming Assignment: PA 6                                                 *
* Date: November, 5, 2016                                                                       *
* Description: This program simulates the game of battleship. It is mainly a good practice 
			   for file writting, arrays, and structs. But it is also good for loop practice 
			   and everything else.										    *
*******************************************************************************************/
#include "functions.h"


int main(void)
{
	//All variables initialized
	char player1_board[11][11] = { '\0' };
	char player2_board[11][11] = { '\0' };
	char player2_hide_board[11][11] = { '\0' };
	int rows = 10, cols = 10, turn = 0, game_winner = 0, hits = 0, misses = 0, hit_check = 0, turn_num = 1;
	double h_m_ratio = 0;
	FILE *statistics = NULL;
	statistics = fopen("battleship.log", "w");//File opened
	Stats player1 = { 0, 0, 0 }, player2 = { 0, 0, 0 };
	srand((unsigned int)time(NULL));

	welcome_screen();
	initialize_game_board(player1_board, rows, cols);
	initialize_game_board(player2_board, rows, cols);
	initialize_game_board(player2_hide_board, rows, cols);
	display_menu(player1_board);
	system("cls");
	randomly_place_ships_on_board(player2_board);

	turn = select_who_starts();

	printf("Player %d was randomly chosen to start!\n", turn);
	system("pause");
	system("cls");
	while (game_winner == 0) //Game keeps running while theres no winner.
	{
		if (turn == 1)
		{
			hit_check = 0;
			system("cls");
			display_board(player1_board, rows, cols, 1);
			display_board(player2_board, rows, cols, 2);//If you want to see ships, switch player2_hide_board for player2_board 
			hit_check = take_shot(player2_board, player2_hide_board, statistics, turn_num, 1);
			if (hit_check == 1) // This if - else statement updates stats depending on whether player hits or misses
			{
				player1.hits += 1;
			}
			else
			{
				player1.misses += 1;
			}
			system("pause");
			game_winner = is_winner(player2_board, 1);
			turn = 2;//This makes turn switch back and forth

		}
		else if (turn == 2)
		{
			hit_check = 0;
			system("cls");
			display_board(player1_board, rows, cols, 1);
			display_board(player2_hide_board, rows, cols, 2);//If you want to see ships, switch player2_hide_board for player2_board 
			hit_check = take_shot(player1_board, player1_board, statistics, turn_num, 2);
			if (hit_check == 1)//This if-else statement updates stats depending on whether player hits or misses
			{
				player2.hits += 1;
			}
			else
			{
				player2.misses += 1;
			}
			game_winner = is_winner(player1_board, 2);
			system("pause");
			turn = 1;//This makes turn switch back and forth
		}
		turn_num++;//This counts number of turns
		switch (game_winner)//Congratulates winner
		{
		case 1:
			congrats_message(game_winner);
			break;
		case 2:
			congrats_message(game_winner);
			break;
		default:
			break;
		}

	}
	//Calculates hit/miss ratios
	player1.hit_miss_ratio = (double)player1.hits / (player1.hits + player1.misses)* 100;
	player2.hit_miss_ratio = (double)player2.hits / (player2.hits + player2.misses)*100;

	output_stats(statistics, player1, 1);
	output_stats(statistics, player2, 2);
	fclose(statistics);//File closed
}
