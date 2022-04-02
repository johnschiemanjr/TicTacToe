/*
 * HumanUltimatePlayer.cpp
 *
 *  Created on: Mar 26, 2022
 *      Author: John
 */

#include "HumanUltimatePlayer.h"


HumanUltimatePlayer::~HumanUltimatePlayer()
{
}

UltMove HumanUltimatePlayer::take_turn(UltimateBoard board)
{
	UltMove move;
	cout << "Please enter which board you would like to play on:\n";

	short user_choice_global;
	short valid_boards_bitboard = board.get_available_boards_bitboard();

	string user_choice;
	do
	{
		cin >> user_choice;
		user_choice_global = spaces[stoi(user_choice)] | valid_boards_bitboard;

		if (user_choice_global == valid_boards_bitboard)
		{
			cout << user_choice <<  " is an invalid board, please re-enter:" << endl;
		}
	} while (user_choice_global == valid_boards_bitboard);

	move.global_space = stoi(user_choice);
	move.local_space = take_turn(board.get_boards()[stoi(user_choice)], stoi(user_choice));

	return move;
}

UltMove HumanUltimatePlayer::take_turn(UltimateBoard board, short board_to_play)
{
	UltMove move;

	move.global_space = board_to_play;
	move.local_space = take_turn(board.get_boards()[board_to_play], board_to_play);

	return move;
}

short HumanUltimatePlayer::take_turn(Board board, short board_to_play)
{
	cout << "Please enter your move on board " << board_to_play << ":\n";

	int user_choice_bitboard;
	int valid_moves_bitboard = board.get_valid_moves_bitboard();

	string user_choice;
	do
	{
		cin >> user_choice;
		user_choice_bitboard = spaces[stoi(user_choice)] | valid_moves_bitboard;

		if (user_choice_bitboard == valid_moves_bitboard)
		{
			cout << user_choice <<  " is an invalid move, please re-enter:" << endl;
		}
	} while (user_choice_bitboard == valid_moves_bitboard);
	return spaces[stoi(user_choice)];
}
