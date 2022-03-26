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
	Board();
	virtual ~Board();
private:
	bool game_over;
	bool winner;
	short x_bitboard;
	short o_bitboard;
};

#endif /* BOARD_H_ */
