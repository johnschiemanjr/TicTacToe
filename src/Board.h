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
#include <vector>

using namespace std;

const std::vector<short> spaces =
    { 0b0000000000000001, // 0
      0b0000000000000010,
      0b0000000000000100,
      0b0000000000001000, //3
      0b0000000000010000,
      0b0000000000100000,
      0b0000000001000000, // 6
      0b0000000010000000,
	  0b0000000100000000,
    };

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
	short x_bitboard;
	short o_bitboard;
};

#endif /* BOARD_H_ */
