/*
 * RandomUltimatePlayer.cpp
 *
 *  Created on: Mar 27, 2022
 *      Author: John
 */

#include "RandomUltimatePlayer.h"

RandomUltimatePlayer::RandomUltimatePlayer(string player_name, string player_symbol) :
ComputerUltimatePlayer(player_name, player_symbol)
{
}

RandomUltimatePlayer::~RandomUltimatePlayer()
{
}

UltMove RandomUltimatePlayer::take_turn(UltimateBoard board)
{
	UltMove move;
	short bitboard_move = get_random_move(board.get_available_boards());
	// Convert bitboard to user-friendly space
	short board_index = 0;
	int i = 0;
	for (short s : spaces)
	{
		if (bitboard_move == s)
		{
			board_index = i;
			break;
		}
		i++;
	}

	move.global_space = board_index;
	move.local_space = get_random_move(board.get_boards()[board_index].get_open_spaces());
	cout << "Computer chooses board " << board_index << " space " << board.get_boards()[board_index].space_to_string(move.local_space) << endl;
	return move;
}

UltMove RandomUltimatePlayer::take_turn(UltimateBoard board, short board_to_play)
{
	UltMove move;

	move.global_space = board_to_play;
	move.local_space = get_random_move(board.get_boards()[board_to_play].get_open_spaces());
	cout << "Computer chooses board " << board_to_play << " space " << board.get_boards()[board_to_play].space_to_string(move.local_space) << endl;

	return move;
}
