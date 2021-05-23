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

using namespace std;

// learning moment: if i had wanted to declare these in the constructor,
// it would have had the same effect as using this initialization list
Board::Board():tiles{{Tile("1"), Tile("2"), Tile("3")},
	{Tile("4"), Tile("5"), Tile("6")},
	{Tile("7"), Tile("8"), Tile("9")}},
	occupied_tiles(0),
	game_over(false)
{
};

Board::~Board()
{
}

void Board::make_move(string tile, string player_symbol)
{
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
}

bool Board::is_game_over() const
{
	return game_over;
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
            }
        }
    }

    //check anti diag (thanks rampion)
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
            }
        }
    }

    //check draw
    if(occupied_tiles == 9)
    {
        game_over = true;
    }
}
