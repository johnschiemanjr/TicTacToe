/*
 * UltimateBoard.h
 *
 *  Created on: Mar 20, 2022
 *      Author: John
 */

#ifndef ULTIMATEBOARD_H_
#define ULTIMATEBOARD_H_

#include "Board.h"
#include "helper.h"

class UltimateBoard
{
public:
	const static short FREE_PLAY = -1;
	UltimateBoard();
	virtual ~UltimateBoard();
	Board* get_boards();
	short get_available_boards_bitboard() const;
	set<short> get_available_boards() const;
	void make_move(UltMove, string);
	void check_winner();
	short get_board_to_play() const;
	bool is_game_over() const;
	bool has_winner() const;
private:
	Board boards[9];
	bool game_over;
	bool winner;
	short x_bitboard;
	short o_bitboard;
	short draw_bitboard;
	// human readable short, i.e. 0-9, -1 for free play
	short board_to_play;
	void set_board_to_play(short);
};

#endif /* ULTIMATEBOARD_H_ */
