/*
 * LocalBoard.h
 *
 *  Created on: Mar 19, 2022
 *      Author: John
 */

#ifndef LOCALBOARD_H_
#define LOCALBOARD_H_

#include <string>
#include <iostream>
#include <set>
#include <vector>
#include "Board.h"

using namespace std;

class LocalBoard : public Board
{
public:
	bool game_on() const;
	void print_row(int, int, int) const;
	void print_board() const;
	LocalBoard();
	LocalBoard(bool, bool);
	void make_move(short, string);
	bool is_game_over() const;
	bool has_winner() const;
	set<short> get_open_spaces() const;
	short get_valid_moves_bitboard() const;
	string get_space(int space) const;
	string space_to_string(short space) const;
	void check_winner();
	LocalBoard copy_board() const;
	virtual ~LocalBoard();
private:
	bool game_over;
	bool winner;
	short x_bitboard;
	short o_bitboard;
};


#endif /* LOCALBOARD_H_ */
