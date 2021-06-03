/*
 * Board.h
 *
 *  Created on: Nov 15, 2020
 *      Author: John
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <string>
#include <iostream>
#include "Tile.h"
#include <set>

using namespace std;

class Board
{
public:
	void print_board() const;
	Board();
	Board(bool, bool, int);
	void make_move(string, string);
	bool is_game_over() const;
	bool has_winner() const;
	set<string> get_valid_moves() const;
	void check_winner(int, int, string);
	Board copy_board() const;
	virtual ~Board();
private:
	Tile tiles[3][3];
	int occupied_tiles;
	bool game_over;
	bool winner;
};

#endif /* BOARD_H_ */
