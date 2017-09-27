
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

typedef struct stats
{
	int hits;
	int misses;
	double hit_miss_ratio;
} Stats;
void welcome_screen(void);
void display_menu(char player_board[][11]);
void initialize_game_board(char player_board[][11], int rows, int cols);
int select_who_starts(void);
void manually_place_ships_on_board(char player_board[][11]);
int check_overlap(char player_board[][11], int row, int cols, int *index, char ship_initial);
void check_contiguous(char player_board[][11], int row, int cols, int *index);
void randomly_place_ships_on_board(char player_board[][11]);
void rndm_ship_strt_pt(char player_board[][11], int ship_size, char ship_initial);
int take_shot(char player_board[][11], char mod_board[][11], FILE *statistics, int turn, int player);
int check_shot(char player_board[][11], char mod_board[][11], int rows, int cols, int player);
int is_winner(char player_board[][11], int player);
void congrats_message(int player);
void display_board(char player_board[][11], int rows, int cols, int player);
void output_current_move(int hit_miss, int a, int b);
void check_if_ship_sunk(char player_board[][11], int row, int col);
void output_stats(FILE *infile, Stats player, int player_);

