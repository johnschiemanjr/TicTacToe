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
#include <set>
#include <vector>

using namespace std;

class Board
{
public:
	bool game_on() const;
	void print_row(int, int, int) const;
	void print_board() const;
	Board();
	Board(bool, bool);
	void make_move(short, string);
	bool is_game_over() const;
	bool has_winner() const;
	set<short> get_open_spaces() const;
	short get_valid_moves_bitboard() const;
	string get_space(int space) const;
	string space_to_string(short space) const;
	void check_winner();
	Board copy_board() const;
	virtual ~Board();
private:
	bool game_over;
	bool winner;
	short x_bitboard;
	short o_bitboard;
};

#endif /* BOARD_H_ */
