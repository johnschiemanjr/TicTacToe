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
#include <time.h>
#include <random>
#include "Player.h"
#include <map>
#include <utility>
#include "Node.h"
#include <memory>

using namespace std;

template<typename S>
auto select_random(const S &s, size_t n)
{
	auto it = begin(s);
	advance(it,n);
	return it;
}

ComputerPlayer::ComputerPlayer(string player_name, string player_symbol, Strategy strategy) :
		Player(player_name, player_symbol),
		strategy(strategy)
{

}

ComputerPlayer::~ComputerPlayer()
{
}

string ComputerPlayer::take_turn(Board board)
{
	cout << get_name() << " taking turn...\n";

	Eval evaluation;

	switch (strategy) {
	case Strategy::RANDOM:
	{
		srand(time(NULL));
		set<string> valid_moves = board.get_valid_moves();
		auto r = rand() % valid_moves.size(); // not _really_ random
		evaluation.best_move = *select_random(valid_moves, r);
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

	cout << "Computer choice: " << evaluation.best_move << endl;

	return evaluation.best_move;
}

Eval ComputerPlayer::monte_carlo(Board current_board)
{
	Eval evaluation;

	Node initial_node = Node(false, NULL);

	//set<>
	for (auto move : current_board.get_valid_moves())
	{

	}

	const int simulations = 200000;
	for (int i = 0; i < simulations; i++)
	{
		//Node leaf = traverse(initial_node);
		//simulation_result = rollout(leaf);
		//back_propogate(leaf, simulation_result);
	}

	return evaluation;
}

double ComputerPlayer::get_ucb(Node node)
{

}

Eval ComputerPlayer::mini_max(Board current_board, bool maximizing_player)
{
	Eval evaluation;
	if (current_board.is_game_over())
	{
		if (current_board.get_valid_moves().size() == 0)
		{
			// game is a draw
			evaluation.evaluation = 0;
		}
		else if (maximizing_player)
		{
			// human has won
			evaluation.evaluation = -1;
		}
		else
		{
			// computer has won
			evaluation.evaluation = 1;
		}
		return evaluation;
	}

	int max_eval = -2;
	int min_eval = 2;
	string max_move = "";
	string min_move = "";
	if (maximizing_player)
	{
		for (auto move : current_board.get_valid_moves())
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
		for (auto move : current_board.get_valid_moves())
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

string ComputerPlayer::get_opposite_symbol(string symbol) const
{
	if (symbol.compare(X) == 0)
	{
		return O;
	}
	else
	{
		return X;
	}
}
