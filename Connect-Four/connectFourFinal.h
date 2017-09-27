#include <stdio.h>		//All of the libraries required plus a couple more
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_ROW 6 //Constants
#define MAX_COL 7

typedef enum occupied
{
	FALSE, TRUE
} Occupied;

typedef enum winner
{
	RED = 1, BLUE
} Winner;

typedef struct location
{
	int row;
	int col;
} Location;


typedef struct cell
{
	char color;
	Occupied isOccupied;
	Location place;
} Cell;

//All functions
void init_board(Cell board[][MAX_COL], int rows, int cols);
void print_board(Cell board[][MAX_COL]);
void turn(Cell board[][MAX_COL], char player);
int validate_move(Cell board[][MAX_COL], int chosen_col);
void check_for_win(Cell board[][MAX_COL], Winner *winner, char *player);
int check_diagonal(Cell board[][MAX_COL], int row, int col);
int check_vertical(Cell board[][MAX_COL], int row, int col);
int check_horizontal(Cell board[][MAX_COL], int row, int col);