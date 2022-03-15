/*
 * ComputerPlayer.cpp
 *
 *  Created on: Nov 16, 2020
 *      Author: John
 */

#include <string>
#include <iostream>
#include <set>
#include "Board.h"
#include "ComputerPlayer.h"
#include "Player.h"
#include <map>
#include <utility>
#include "Node.h"
#include <memory>
#include "helper.h"
#include <chrono>

using namespace std;

ComputerPlayer::ComputerPlayer(string player_name, string player_symbol, Strategy strategy) :
		Player(player_name, player_symbol),
		strategy(strategy)
{

}

ComputerPlayer::~ComputerPlayer()
{
}

short ComputerPlayer::take_turn(Board board)
{
	cout << get_name() << " taking turn...\n";

	Eval evaluation;

	switch (strategy) {
	case Strategy::RANDOM:
	{
		//evaluation.best_move = get_random_move(board.get_valid_moves());
		short move = get_random_move_bitboard(board.get_open_spaces());
		evaluation.best_move = move;
		break;
	}
	case Strategy::MINIMAX:
	{
		evaluation = mini_max(board, true);
		break;
	}
	case Strategy::MONTE_CARLO:
		evaluation = monte_carlo(board);
	}

	return evaluation.best_move;
}

Eval ComputerPlayer::monte_carlo(Board current_board)
{
	Eval evaluation;

	Node *initial_node = new Node(NULL, &current_board, -1, "NO_SYMBOL");
	// get children nodes
	for (auto move : current_board.get_open_spaces())
	{
		Node *child = new Node(initial_node, &current_board, move, get_symbol());
		initial_node->children.push_back(child);
	}

	const int ITERATIONS_CONSTANT = 10000;
	for (int iterations = 0; iterations < ITERATIONS_CONSTANT; iterations++)
	{
		initial_node->search();
	}

	double max_score = -99999999;
	evaluation.best_move = get_random_move_bitboard(current_board.get_open_spaces());
	for(auto child : initial_node->children)
	{
		double average_score = child->total_score / child->visits;
		if (average_score > max_score)
		{
			max_score = average_score;
			evaluation.best_move = child->move;
		}
		//cout << "Move " << child->move << " Total score : " << child->total_score << " visits: " << child->visits << " for an average score of " << average_score << endl;
	}


	//cout << "Best move: " << evaluation.best_move << endl;
	return evaluation;

	delete initial_node;
}

Eval ComputerPlayer::mini_max(Board current_board, bool maximizing_player)
{
	Eval evaluation;
	if (current_board.is_game_over())
	{
		if (current_board.is_game_over() && !current_board.has_winner())
		{
			// game is a draw
			evaluation.evaluation = 0;
		}
		else if (maximizing_player)
		{
			// other player has won
			evaluation.evaluation = -1;
		}
		else
		{
			// this player has won
			evaluation.evaluation = 1;
		}
		return evaluation;
	}

	int max_eval = -2;
	int min_eval = 2;
	short max_move;
	short min_move;
	if (maximizing_player)
	{
		for (auto move : current_board.get_open_spaces())
		{
			Board board_with_move = current_board;
			board_with_move.make_move(move, get_symbol());
			Eval move_eval = mini_max(board_with_move, false);
			int eval = move_eval.evaluation;
			if (eval >= max_eval)
			{
				max_eval = eval;
				max_move = move;
			}
		}
		evaluation.best_move = max_move;
		evaluation.evaluation = max_eval;
	}
	else
	{
		for (auto move : current_board.get_open_spaces())
		{
			Board board_with_move = current_board;
			string opposite = get_opposite_symbol(get_symbol());
			board_with_move.make_move(move, opposite);
			Eval move_eval = mini_max(board_with_move, true);
			int eval = move_eval.evaluation;
			if (eval <= min_eval)
			{
				min_eval = eval;
				min_move = move;
			}
		}
		evaluation.best_move = min_move;
		evaluation.evaluation = min_eval;
	}

	return evaluation;
}

