/*
 * UltimateBoard.h
 *
 *  Created on: Mar 20, 2022
 *      Author: John
 */

#ifndef ULTIMATEBOARD_H_
#define ULTIMATEBOARD_H_

#include "Board.h"

class UltimateBoard : public Board
{
public:
	UltimateBoard();
	virtual ~UltimateBoard();
	Board* get_boards();
	short get_available_boards_bitboard() const;
private:
	Board boards[9];
	bool game_over;
	bool winner;
	short x_bitboard;
	short o_bitboard;
};

#endif /* ULTIMATEBOARD_H_ */
