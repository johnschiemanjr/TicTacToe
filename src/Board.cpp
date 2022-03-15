/*
 * Board.cpp
 *
 *  Created on: Nov 15, 2020
 *      Author: John
 */

#include "Board.h"
#include <string>
#include <iostream>
#include <set>
#include <bitset>
#include "helper.h"

using namespace std;

Board::Board(): game_over(false), winner(false), x_bitboard(0), o_bitboard(0)
{
};

Board::Board(bool game_over_copy, bool winner_copy) : x_bitboard(0), o_bitboard(0)
{
	this->game_over = game_over_copy;
	this->winner = winner_copy;
}

Board::~Board()
{
}

void Board::make_move(short move, string player_symbol)
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
string Board::space_to_string(short space) const
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

string Board::get_space(int space) const
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

void Board::print_board() const
{
	cout << "\n";
	cout << "  " << get_space(0) << "  |  " << get_space(1) << "  |  " << get_space(2) << "  " << endl;
	cout << "-----|-----|-----" << endl;
	cout << "  " << get_space(3) << "  |  " << get_space(4) << "  |  " << get_space(5) << "  " << endl;
	cout << "-----|-----|-----" << endl;
	cout << "  " << get_space(6) << "  |  " << get_space(7) << "  |  " << get_space(8) << "  \n" << endl;

//	cout << "X bitboard: " <<  bitset<16>(x_bitboard) << endl;
//	cout << "O bitboard: " << bitset<16>(o_bitboard) << "\n" << endl;
}

bool Board::is_game_over() const
{
	return game_over;
}

bool Board::has_winner() const
{
	return winner;
}

Board Board::copy_board() const
{
	Board new_board = Board(game_over, winner);
	new_board.o_bitboard = o_bitboard;
	new_board.x_bitboard = x_bitboard;
	return new_board;
}

set<short> Board::get_open_spaces() const
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

short Board::get_valid_moves_bitboard() const
{
	return o_bitboard | x_bitboard;
}

void Board::check_winner()
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
