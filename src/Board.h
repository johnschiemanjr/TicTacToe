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

const std::vector<int> wins =
    { 0b0000000000000111,
      0b0000000000111000, // 3 rows
      0b0000000111000000,
      0b0000000100100100,
      0b0000000010010010, // 3 columns
      0b0000000001001001,
      0b0000000100010001, // 2 diagonals
      0b0000000001010100 };

class Board
{
public:
	void print_board() const;
	Board();
	Board(bool, bool, int);
	void make_move(string, string);
	bool is_game_over() const;
	bool has_winner() const;
	set<short> get_open_spaces() const;
	int get_valid_moves_bitboard() const;
	string get_space(int space) const;
	string space_to_string(short space) const;
	void check_winner();
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
