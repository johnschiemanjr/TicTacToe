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

// learning moment: if i had wanted to declare these in the constructor,
// it would have had the same effect as using this initialization list
Board::Board():tiles{{Tile("0"), Tile("1"), Tile("2")},
	{Tile("3"), Tile("4"), Tile("5")},
	{Tile("6"), Tile("7"), Tile("8")}},
	occupied_tiles(0),
	game_over(false),
	winner(false), x_bitboard(0), o_bitboard(0)
{
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
				check_winner(i, j, player_symbol);
			}
		}
	}
}

void Board::print_board() const
{
	cout << "\n";
	cout << "  " << tiles[0][0].get_status() << "  |  " << tiles[0][1].get_status() << "  |  " << tiles[0][2].get_status() << "  " << endl;
	cout << "-----|-----|-----" << endl;
	cout << "  " << tiles[1][0].get_status() << "  |  " << tiles[1][1].get_status() << "  |  " << tiles[1][2].get_status() << "  " << endl;
	cout << "-----|-----|-----" << endl;
	cout << "  " << tiles[2][0].get_status() << "  |  " << tiles[2][1].get_status() << "  |  " << tiles[2][2].get_status() << "  \n" << endl;

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

void Board::check_winner(int x, int y, string symbol)
{
	// check draw
	if(((x_bitboard | o_bitboard) & 0x01FF) == 0x01FF)
	{
        game_over = true;
        winner = false;
    }

    //check row
	for(int i = 0; i < 3; i++)
    {
        if(tiles[x][i].get_status().compare(symbol) != 0)
        {
            break;
        }
        if(i == 2)
        {
        	game_over = true;
        	winner = true;
        }
    }

    //check column
    for(int i = 0; i < 3; i++)
    {
        if(tiles[i][y].get_status().compare(symbol) != 0)
        {
            break;
        }
        if(i == 2)
        {
        	game_over = true;
        	winner = true;
        }
    }

    //check diag
    if(x == y)
    {
        //we're on a diagonal
    	for(int i = 0; i < 3; i++)
    	{
            if(tiles[i][i].get_status().compare(symbol) != 0)
            {
                break;
            }
            if(i == 2)
            {
            	game_over = true;
            	winner = true;
            }
        }
    }

    //check anti diag
    if(x + y == 2)
    {
    	for(int i = 0; i < 3; i++)
    	{
            if(tiles[i][2-i].get_status().compare(symbol) != 0)
            {
                break;
            }
            if(i == 2)
            {
            	game_over = true;
            	winner = true;
            }
        }
    }
}
