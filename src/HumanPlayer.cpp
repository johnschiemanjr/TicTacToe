/*
 * HumanPlayer.cpp
 *
 *  Created on: Nov 16, 2020
 *      Author: John
 */

#include <iostream>
#include "Board.h"
#include "HumanPlayer.h"

using namespace std;

HumanPlayer::~HumanPlayer()
{
}

string HumanPlayer::take_turn(Board board)
{
	cout << "Please enter your move:\n";

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
	return user_choice;
}


