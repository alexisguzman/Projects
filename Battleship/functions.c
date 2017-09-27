#include "functions.h"


/*This function displays a welcome screen 
takes no parameters and and doesn't return anything*/
void welcome_screen(void)
{
	puts("***** Welcome to Battleship! *****\n");
	puts("Rules of the Game:\n");
	puts("1. This is a two player game.\n");
	puts("2. Player1 is you and Player2 is the computer.\n");
	puts("3. First, you'll play ships in valid locations.\n");
	puts("4. Every turn, you will have one shot.\n");
	puts("5. You'll be notified if you hit or missed the ships.\n");
	puts("6. In order to sink a ship you must hit all of its cells.\n");
	puts("7. First player to shink all opponents ships, wins.\n");
	puts("GOOD LUCK!!!");
	system("pause");
	system("cls");



}
/*This function initializes a board with two for loops to be able to 
go through all of the two dimensional array. Takes in a player board and 
the nuber of rows and cols as parameters.*/
void initialize_game_board(char player_board[][11], int rows, int cols)
{
	int index_rows = 0, index_cols = 0;

	for (index_rows = 0; index_rows < rows; index_rows++)
	{
		for (index_cols = 0; index_cols < cols; index_cols++)
		{
			player_board[index_rows][index_cols] = '~';
		}
	}	
}
/*This functions displays the menu asking how the player
would like to place his ships and takes in a player board as a
parameter but doesn't return anything.*/
void display_menu(char player_board[][11])
{

	int option = 0;
	while (option > 2 || option < 1) 
	{
	puts("Please select from the following menu:\n");
	puts("1. Enter positions manually.");
	puts("2. Randomize ship positions.");
	scanf("%d", &option);
	}
	switch (option)
	{
	case 1:
		manually_place_ships_on_board(player_board);
		break;
	case 2:
		randomly_place_ships_on_board(player_board);
		break;
	}
	
}

/*This function is used to check all of the things that couls go wrong when 
placing ships manually. Any bound violations, overlaps, or illegal placing.
It takes in the board as a parameter but doesn't return anything.*/
void manually_place_ships_on_board(char player_board[][11])
{
	system("cls");
	
	int index = 0, row = 0, column = 0, overlap = 0;
	puts("Please enter the five cells to place the Carrier across\n(row followed by column):");
	for (index = 0; index < 5; index++)
	{
		scanf("%d%d", &row, &column);
		check_overlap(player_board, row, column, &index, 'c');
		player_board[row][column] = 'c';
		if (index >= 1) 
		{
			check_contiguous(player_board, row, column, &index);
		}
		
		
				
	}
	puts("Please enter the four cells to place the Battleship across\n(row followed by column):");
	index = 0;
	do 
	{
		
		scanf("%d%d", &row, &column);
		overlap = check_overlap(player_board, row, column, &index, 'b');
		if (!overlap)
		{
			player_board[row][column] = 'b';
			if (index >= 1)
			{
				check_contiguous(player_board, row, column, &index);
			}
			index++;
		}
		
	} while (index < 4);
	puts("Please enter the three cells to place the Cruiser across\n(row followed by column):");
	index = 0;
	do
	{

		scanf("%d%d", &row, &column);
		overlap = check_overlap(player_board, row, column, &index, 'b');
		if (!overlap)
		{
			player_board[row][column] = 'r';
			if (index >= 1)
			{
				check_contiguous(player_board, row, column, &index);
			}
			index++;
		}

	} while (index < 3);
	puts("Please enter the three cells to place the Submarine across\n(row followed by column):");
	index = 0;
	do
	{

		scanf("%d%d", &row, &column);
		overlap = check_overlap(player_board, row, column, &index, 'b');
		if (!overlap)
		{
			player_board[row][column] = 's';
			if (index >= 1)
			{
				check_contiguous(player_board, row, column, &index);
			}
			index++;
		}

	} while (index < 3);
	puts("Please enter the two cells to place the Destroyer across\n(row followed by column):");
	index = 0;
	do
	{

		scanf("%d%d", &row, &column);
		overlap = check_overlap(player_board, row, column, &index, 'b');
		if (!overlap)
		{
			player_board[row][column] = 'd';
			if (index >= 1)
			{
				check_contiguous(player_board, row, column, &index);
			}
			index++;
		}

	} while (index < 2);
}

/*This function is used in the manually placing function to check the overlapping
condition when choosing coordinates. It takes in a board, the coordinates and a ship initial
as parameters and returns a 0 if there is no overlap and a 1 if there is.*/
int check_overlap(char player_board[][11], int row, int cols, int *index, char ship_initial)
{
	int r_index = 0, c_index = 0;
	if (player_board[row][cols] != '~')
	{
		printf("Those coordinates are already in use. Please re-enter ALL coordinates for this \nship.(row followed by column):\n");
		*index = 0;
		for (r_index = 0; r_index < 10; r_index++)
		{
			for (c_index = 0; c_index < 10; c_index++)
			{
				if (player_board[r_index][c_index] == ship_initial)
				{
					player_board[r_index][c_index] = '~';
				}
			}
		}
		return 1;
	}
	return 0;
}

/*This function is also used to check that the coordinates entered are constiguous.
It takes in a board, the coordinates and the index as a parameter.*/
void check_contiguous(char player_board[][11], int row, int cols, int *index)
{
	char check = player_board[row][cols], up = player_board[row - 1][cols], down = player_board[row + 1][cols],
		right = player_board[row][cols + 1], left = player_board[row][cols - 1];
	if (check != right && check != left && check != up && check != down)
	{
		puts("Please re-enter last coordinate and make sure it's valid.\nAlso, remember you cannot place ships diagonally!\n");
		player_board[row][cols] = '~';
		*index--;
	}
}

/*This function randomly places the ships on board without having to enter your own
coordinates. It takes in the player board as an input and doesn't return anything.*/
void randomly_place_ships_on_board(char player_board[][11])
{
	int index = 0, rows = 0, cols = 0, r_index = 0, c_index = 0;

	rndm_ship_strt_pt(player_board, 5, 'c');
	rndm_ship_strt_pt(player_board, 4, 'b');
	rndm_ship_strt_pt(player_board, 3, 'r');
	rndm_ship_strt_pt(player_board, 3, 's');
	rndm_ship_strt_pt(player_board, 2, 'd');


}

/*This does all of the checks for random ship placing. Checks overlap, contiguous,
and makes sure it is within the bounds of the board. It takes in player board, ship size 
and ship initial as parameters and doesnt return anything.*/
void rndm_ship_strt_pt(char player_board[][11], int ship_size, char ship_initial)
{
	int rows = 0, cols = 0, index = 0, check = 0, direction = 0;
	
	while (check == 0)
	{
		rows = rand() % 10;
		cols = rand() % 10;

		if (player_board[rows][cols] == '~')
		{
			direction = rand() % 4 + 1;
			for (index = 0; index < ship_size; index++)
			{

				switch (direction)
				{
				case 1:
					if (player_board[rows][cols + index] == '~') 
					{
						player_board[rows][cols + index] = ship_initial;
						check = 1;
					}
					else
					{
						for (rows = 0; rows < 10; rows++)
						{
							for (cols = 0; cols < 10; cols++)
							{
								if (player_board[rows][cols] == ship_initial)
								{
									player_board[rows][cols] = '~';
								}
							}
						}
						check = 0;
					}
					break;
				case 2:
					if (player_board[rows][cols - index] == '~')
					{
						player_board[rows][cols - index] = ship_initial;
						check = 1;
					}
					else
					{
						for (rows = 0; rows < 10; rows++)
						{
							for (cols = 0; cols < 10; cols++)
							{
								if (player_board[rows][cols] == ship_initial)
								{
									player_board[rows][cols] = '~';
								}
							}
						}
						check = 0;
					}
					break;
				case 3:
					if (player_board[rows + index][cols] == '~')
					{
						player_board[rows + index][cols] = ship_initial;
						check = 1;
					}
					else
					{
						for (rows = 0; rows < 10; rows++)
						{
							for (cols = 0; cols < 10; cols++)
							{
								if (player_board[rows][cols] == ship_initial)
								{
									player_board[rows][cols] = '~';
								}
							}
						}
						check = 0;
					}
					break;
				case 4:
					if (player_board[rows - index][cols] == '~')
					{
						player_board[rows - index][cols] = ship_initial;
						check = 1;
					}
					else
					{
						for (rows = 0; rows < 10; rows++)
						{
							for (cols = 0; cols < 10; cols++)
							{
								if (player_board[rows][cols] == ship_initial)
								{
									player_board[rows][cols] = '~';
								}
							}
						}
						check = 0;
					}
					break;
				default:
					break;
				}
				if (check == 0)
				{
					break;
				}
			}
		}
		else
		{
			check = 0;
		}
	}
}

/*This function just is used to choose who starts the game.
No parameters are taken in. If 1 is returned, it's player 1's turn
and if 2 is returned it is player 2's turn.*/
int select_who_starts(void)
{
	int first_turn = 0;
	first_turn = rand() % 2 + 1;
	return first_turn;
}

/*This function checks if the coordinates entered are valid
and also prints turn information to file.
It takes in a player board, the board being modified, a file to write to, the turn number, and 
the player as parameters and returns a 1 if shot is a hit and 0 if it's a miss.*/
int take_shot(char player_board[][11], char mod_board[][11], FILE *statistics, int turn, int player)
{
	int rows = 0, cols = 0, check = 0, hit_miss = 0;
	if (player == 1)
	{ 
		while (check == 0)
		{
			puts("Enter a target:");
			scanf("%d%d", &rows, &cols);
			if (rows > 9 || cols > 9 || rows < 0 || cols < 0)
			{
				puts("Please enter values 0-9.");
				check = 0;
			}
			else 
			{

				check = 1;
			}
		}
	}
	else if (player == 2)
	{
		rows = rand() % 10;
		cols = rand() % 10;
	}
	hit_miss = check_shot(player_board, mod_board, rows, cols, statistics, turn, player);
	if (hit_miss)
	{
		fprintf(statistics, "Player %d, turn %d: %d, %d is a hit!\n\n", player, turn, rows, cols);
	}
	else
	{
		fprintf(statistics, "Player %d, turn %d: %d, %d is a miss!\n\n", player, turn, rows, cols);
	}
	return hit_miss;
	
}

/*This function checks whether the shot is a hit or a miss.
It takes in a player board, board modified, the coordinates, a file, the turn number
and the player as parameters and returns a 1 if it's a hit and 0 if it's a miss*/
int check_shot(char player_board[][11], char mod_board[][11], int rows, int cols,FILE *statistics, int turn, int player)
{
	
	char ship[11] = { '\0' };
	switch (player_board[rows][cols])
	{
	case 'c':
		strcpy(ship, "Carrier");
		break;
	case 'b':
		strcpy(ship, "Battleship");
		break;
	case 'r':
		strcpy(ship, "Cruiser");
		break;
	case 's':
		strcpy(ship, "Submarine");
		break;
	case 'd':
		strcpy(ship, "Destroyer");
		break;
	}
	switch (player_board[rows][cols])
	{
	case 'c':
	case 'b':
	case 'r':
	case 's':
	case 'd':
		if (player == 2)
		{
			printf("Player %d selects: %d,%d\n", player, rows, cols);
		}
		printf("%d,%d is a hit on %s!\n", rows, cols, ship);
		check_if_ship_sunk(player_board, rows, cols, statistics, player);
		player_board[rows][cols] = '*';
		mod_board[rows][cols] = '*';
		return 1;
		break;
	case '~':
		if (player == 2) 
		{
			printf("Player %d selects: %d,%d\n", player, rows, cols);
		}
		printf("%d,%d is a miss!\n", rows, cols);
		player_board[rows][cols] = 'm';
		mod_board[rows][cols] = 'm';
		return 0;
		break;
	case 'm':
	case '*':
		if (player == 1)
		{
			printf("%d,%d has already been used.\n", rows, cols);
		}
		take_shot(player_board, mod_board, statistics, turn, player);
		break;
	}
}

/*This functions checks if the player won.
Takes in a board and player as parameters. Returns player number if it's a win
and a 0 if no one has won.*/
int is_winner(char player_board[][11], int player)
{
	int r_index = 0, c_index = 0, is_win = 0;
	
	for (r_index = 0; r_index < 10; r_index++)
	{
		for (c_index = 0; c_index < 10; c_index++)
		{
			if (player_board[r_index][c_index] != '~' && player_board[r_index][c_index] != '*' && player_board[r_index][c_index] != 'm')
			{
				return is_win;
			}
		}
	}
	
	return player;
}

/*This displays a congratulation message when someone wins.
It takes in player as a parameter and doesnt return anything.*/
void congrats_message(int player)
{
	system("cls");
	printf("Congratulations! Player %d, you won!\n", player);
}

/*This function displays the board.
It takes in a board, number of rows, number of columns, and player as
parameters and doesnt return anything.*/
void display_board(char player_board[][11], int rows, int cols, int player)
{
	int index_rows = 0, index_cols = 0;
	
	printf("Player %d game board:\n", player);
	printf("  0 1 2 3 4 5 6 7 8 9\n");
	for (index_rows = 0; index_rows < rows; index_rows++)
	{
		printf("%d ", index_rows);
		for (index_cols = 0; index_cols < cols; index_cols++)
		{
			printf("%c ", player_board[index_rows][index_cols]);
		}
		putchar('\n');
	}
	printf("\n");

}

/*This function checks whether the shot taken sinks the ship or not.
If it does, it displays a message to the screen. It takes in player board,
coordinates, file, and player as parameters and doesn't return anything.*/
void check_if_ship_sunk(char player_board[][11], int row, int col, FILE *statitics, int player)
{
	int r_index = 0, c_index = 0, check = 0;
	char ship_sunk[14] = { '\0' };
	if (player_board[row][col] != '~' )
	{ 
		for (r_index = 0; r_index < 10; r_index++)
		{
			for (c_index = 0; c_index < 10; c_index++)
			{
				if (player_board[r_index][c_index] == player_board[row][col])
				{
					if (r_index != row || c_index != col)
					{
						check = 0;
						break;
					}
				}
				else
				{
					check = 1;
				}
			
				
					
				
			}
			if (check == 0)
			{
				break;
			}
		}
		if (check)
		{
			switch (player_board[row][col])
			{
			case 'c':
				strcpy(ship_sunk, "carrier");
				break;
			case 'b':
				strcpy(ship_sunk, "battleship");
				break;
			case 'r':
				strcpy(ship_sunk, "cruiser");
				break;
			case 's':
				strcpy(ship_sunk, "submarine");
				break;
			case 'd':
				strcpy(ship_sunk, "destroyer");
				break;
			}
			printf("The %s has been sunk! Good job!\n", ship_sunk);
			fprintf(statitics, "Player %d sunk the opponents %s!\n\n", player, ship_sunk);
		}
		
	}
}

/*This function prints the stats to a file.
It takes in a file, struct, and player as a parameter.*/
void output_stats(FILE *infile, Stats player, int player_)
{

	fprintf(infile, "Player %d stats:\n", player_);
	fprintf(infile, "Hits: %d\n", player.hits);
	fprintf(infile, "Misses: %d\n", player.misses);
	fprintf(infile, "Hit to miss ratio: %.2lf\n\n", player.hit_miss_ratio);
}
