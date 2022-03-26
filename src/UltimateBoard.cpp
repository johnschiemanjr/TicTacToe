/*
 * UltimateBoard.cpp
 *
 *  Created on: Mar 20, 2022
 *      Author: John
 */

#include "UltimateBoard.h"

UltimateBoard::UltimateBoard(): game_over(false), winner(false), x_bitboard(0), o_bitboard(0)
{
	const short NUM_BOARDS = 9;
	for (int i = 0; i < NUM_BOARDS; i++)
	{
		this->boards[i] = Board();
	}
}

UltimateBoard::~UltimateBoard()
{
}

Board* UltimateBoard::get_boards()
{
	return boards;
}

short UltimateBoard::get_available_boards_bitboard() const
{
	return o_bitboard | x_bitboard;
}

