/*
 * HumanUltimatePlayer.cpp
 *
 *  Created on: Mar 19, 2022
 *      Author: John
 */

#include "HumanUltimatePlayer.h"

HumanUltimatePlayer::HumanUltimatePlayer()
{
}

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

	move.global_space = spaces[stoi(user_choice)];
	move.local_space = take_turn(board.get_boards()[stoi(user_choice)]);

	return move;
}

short HumanUltimatePlayer::take_turn(Board board)
{
	LocalBoard* local_board = dynamic_cast<LocalBoard*>(board);
	cout << "Please enter your move:\n";

	int user_choice_bitboard;
	int valid_moves_bitboard = local_board.get_valid_moves_bitboard();
	delete local_board;

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

