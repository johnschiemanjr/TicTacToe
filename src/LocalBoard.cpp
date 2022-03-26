/*
 * LocalBoard.cpp
 *
 *  Created on: Mar 19, 2022
 *      Author: John
 */

#include "LocalBoard.h"
#include <string>
#include <iostream>
#include <set>
#include <bitset>
#include "helper.h"

using namespace std;

LocalBoard::LocalBoard(): game_over(false), winner(false), x_bitboard(0), o_bitboard(0)
{
};

LocalBoard::LocalBoard(bool game_over_copy, bool winner_copy) : x_bitboard(0), o_bitboard(0)
{
	this->game_over = game_over_copy;
	this->winner = winner_copy;
}

LocalBoard::~LocalBoard()
{
}

void LocalBoard::make_move(short move, string player_symbol)
{
	if (!player_symbol.compare(X))
	{
		x_bitboard = x_bitboard ^ move;
	}
	else
	{
		o_bitboard = o_bitboard ^ move;
	}
	check_winner();
}

// Method to convert space to GUI friendly string
string LocalBoard::space_to_string(short space) const
{
	int i = 0;
	for (short s : spaces)
	{
		if (space == s)
		{
			return to_string(i);
		}
		i++;
	}
	return to_string(i);
}

string LocalBoard::get_space(int space) const
{
	if ((x_bitboard & spaces[space]) == spaces[space])
	{
		return X;
	}
	else if ((o_bitboard & spaces[space]) == spaces[space])
	{
		return O;
	}
	else return to_string(space);
}

void LocalBoard::print_row(int left, int center, int right) const
{
	cout << "  " << get_space(left) << "  |  " << get_space(center) << "  |  " << get_space(right);
}

void LocalBoard::print_board() const
{
	cout << "\n";
	print_row(0, 1, 2);
	cout << "\n";
	cout << "-----|-----|-----" << endl;
	print_row(3, 4, 5);
	cout << "\n";
	cout << "-----|-----|-----" << endl;
	print_row(6, 7, 8);
	cout << "\n" << endl;

//	cout << "X bitboard: " <<  bitset<16>(x_bitboard) << endl;
//	cout << "O bitboard: " << bitset<16>(o_bitboard) << "\n" << endl;
}

bool LocalBoard::is_game_over() const
{
	return game_over;
}

bool LocalBoard::has_winner() const
{
	return winner;
}

LocalBoard LocalBoard::copy_board() const
{
	LocalBoard new_board = LocalBoard(game_over, winner);
	new_board.o_bitboard = o_bitboard;
	new_board.x_bitboard = x_bitboard;
	return new_board;
}

set<short> LocalBoard::get_open_spaces() const
{
	set<short> open_spaces;
	for (short space : spaces)
	{
		if ((get_valid_moves_bitboard() | space) != get_valid_moves_bitboard())
		{
			open_spaces.insert(space);
		}
	}
	return open_spaces;
}

short LocalBoard::get_valid_moves_bitboard() const
{
	return o_bitboard | x_bitboard;
}

void LocalBoard::check_winner()
{
	// check draw
	if (((x_bitboard | o_bitboard) & 0x01FF) == 0x01FF)
	{
        game_over = true;
        winner = false;
    }

	//check winner
	for (unsigned int i = 0; i < wins.size(); i++)
	{
		if ((x_bitboard & wins[i]) == wins[i])
		{
			game_over = true;
			winner = true;
		}
		else if ((o_bitboard & wins[i]) == wins[i])
		{
			game_over = true;
			winner = true;
		}
	}
}
