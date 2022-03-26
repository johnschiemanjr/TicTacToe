/*
 * HumanPlayer.cpp
 *
 *  Created on: Nov 16, 2020
 *      Author: John
 */

#include <iostream>
#include "HumanPlayer.h"
#include "helper.h"

using namespace std;

HumanPlayer::~HumanPlayer()
{
}

short HumanPlayer::take_turn(Board board)
{
	LocalBoard* local_board = dynamic_cast<LocalBoard*>(board);

	cout << "Please enter your move:\n";

	int user_choice_bitboard;
	int valid_moves_bitboard = local_board->get_valid_moves_bitboard();
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


