/*
 * HumanPlayer.cpp
 *
 *  Created on: Nov 16, 2020
 *      Author: John
 */

#include <string>
#include <iostream>
#include <set>
#include "Board.h"
#include "HumanPlayer.h"

using namespace std;

HumanPlayer::~HumanPlayer()
{
}

string HumanPlayer::take_turn(Board board)
{
	cout << "Please enter your move:\n";

	set<string> valid_moves = board.get_valid_moves();
	string user_choice;
	do
	{
		cin >> user_choice;
		if (valid_moves.find(user_choice) == valid_moves.end())
		{
			cout << "INVALID MOVE " << user_choice << endl;
		}
	} while (valid_moves.find(user_choice) == valid_moves.end());
	return user_choice;
}


