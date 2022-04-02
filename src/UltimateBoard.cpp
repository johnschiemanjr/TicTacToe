/*
 * UltimateBoard.cpp
 *
 *  Created on: Mar 20, 2022
 *      Author: John
 */

#include "UltimateBoard.h"
#include <bitset>

UltimateBoard::UltimateBoard(): game_over(false), winner(false), x_bitboard(0), o_bitboard(0), draw_bitboard(0), board_to_play(FREE_PLAY)
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
	return o_bitboard | x_bitboard | draw_bitboard;
}

set<short> UltimateBoard::get_available_boards() const
{
	set<short> open_spaces;
	for (short space : spaces)
	{
		if ((get_available_boards_bitboard() | space) != get_available_boards_bitboard())
		{
			open_spaces.insert(space);
		}
	}
	return open_spaces;
}

short UltimateBoard::get_board_to_play() const
{
	return board_to_play;
}

void UltimateBoard::set_board_to_play(short space)
{
	short board_index = 0;
	int i = 0;
	for (short s : spaces)
	{
		if (space == s)
		{
			board_index = i;
			break;
		}
		i++;
	}

	Board board = boards[board_index];
	if (board.is_game_over())
	{
		board_to_play = FREE_PLAY;
	}
	else
	{
		board_to_play = board_index;
	}

	cout << "Board to play: " << board_to_play << endl;
}

void UltimateBoard::make_move(UltMove move, string player_symbol)
{
	this->boards[move.global_space].make_move(move.local_space, player_symbol);
	set_board_to_play(move.local_space);

	if (this->boards[move.global_space].is_game_over() && this->boards[move.global_space].has_winner())
	{
		cout << player_symbol << " has won on board " << move.global_space << endl;
		if (!player_symbol.compare(X))
		{
			x_bitboard = x_bitboard ^ spaces[move.global_space];
		}
		else
		{
			o_bitboard = o_bitboard ^ spaces[move.global_space];
		}
		check_winner();
	}
	else if(this->boards[move.global_space].is_game_over() && !this->boards[move.global_space].has_winner())
	{
		cout << "Board " << move.global_space << " has been drawn." << endl;
		draw_bitboard = draw_bitboard ^ spaces[move.global_space];
	}
}

void UltimateBoard::check_winner()
{
	// check draw
	if (((x_bitboard | o_bitboard) & 0x01FF) == 0x01FF)
	{
        game_over = true;
        winner = false;
    }

	//check winner
	for (unsigned int i = 0; i < wins.size(); i++)
	{
		if ((x_bitboard & wins[i]) == wins[i])
		{
			cout << "X has won!" << endl;
			game_over = true;
			winner = true;
		}
		else if ((o_bitboard & wins[i]) == wins[i])
		{
			cout << "O has won!" << endl;
			game_over = true;
			winner = true;
		}
	}
}

bool UltimateBoard::is_game_over() const
{
	return game_over;
}

bool UltimateBoard::has_winner() const
{
	return winner;
}

