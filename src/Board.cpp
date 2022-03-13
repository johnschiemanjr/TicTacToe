/*
 * Board.cpp
 *
 *  Created on: Nov 15, 2020
 *      Author: John
 */

#include "Board.h"
#include "Tile.h"
#include <string>
#include <iostream>
#include <set>
#include <bitset>

using namespace std;

// learning moment: if I had wanted to declare these in the constructor,
// it would have had the same effect as using this initialization list
Board::Board():tiles{{Tile("0"), Tile("1"), Tile("2")},
	{Tile("3"), Tile("4"), Tile("5")},
	{Tile("6"), Tile("7"), Tile("8")}},
	occupied_tiles(0),
	game_over(false),
	winner(false), x_bitboard(0), o_bitboard(0)
{
	this->o_bitboard = 0;
};

Board::Board(bool game_over_copy, bool winner_copy, int occupied) : tiles{{Tile("0"), Tile("1"), Tile("2")},
	{Tile("3"), Tile("4"), Tile("5")},
	{Tile("6"), Tile("7"), Tile("8")}}, x_bitboard(0), o_bitboard(0)
{
	this->game_over = game_over_copy;
	this->occupied_tiles = occupied;
	this->winner = winner_copy;
}

Board::~Board()
{
}

void Board::make_move(string tile, string player_symbol)
{
	short move = stoi(tile);
	if (!player_symbol.compare(X))
	{
		x_bitboard = x_bitboard ^ spaces[move];
	}
	else
	{
		o_bitboard = o_bitboard ^ spaces[move];
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (tiles[i][j].get_status().compare(tile) == 0)
			{
				tiles[i][j].set_status(player_symbol);
				occupied_tiles++;
				check_winner();
			}
		}
	}
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

	cout << "X bitboard: " <<  bitset<16>(x_bitboard) << endl;
	cout << "O bitboard: " << bitset<16>(o_bitboard) << "\n" << endl;
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
	Board new_board = Board(game_over, winner, occupied_tiles);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			new_board.tiles[i][j].set_status(tiles[i][j].get_status());
		}
	}
	new_board.o_bitboard = o_bitboard;
	new_board.x_bitboard = x_bitboard;
	return new_board;
}

set<string> Board::get_valid_moves() const
{
	set<string> valid_moves;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (tiles[i][j].get_status().compare(O) != 0 &&
					tiles[i][j].get_status().compare(X) != 0)
			{
				valid_moves.insert(tiles[i][j].get_status());
			}
		}
	}
	return valid_moves;
}

int Board::get_valid_moves_bitboard() const
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
