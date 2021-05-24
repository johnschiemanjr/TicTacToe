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
		evaluation.best_move = get_random_move(board.get_valid_moves());
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

	Node initial_node = Node(false, NULL, &current_board, "NO_MOVE");

	// get children nodes
	set<Node*> children = initial_node.children;
	for (auto move : current_board.get_valid_moves())
	{
		Node *child = new Node(true, &initial_node, &current_board, move);
		children.insert(child);
	}

	int iterations = 1;
	if (iterations == 0)
	{
		// First iteration, roll out on first node.
		//rollout(children[0]);
	}
	else
	{
		cout << "Calculating UCB values..." << endl;
		for(auto child : children)
		{
			child->state.print_board();
			delete child;
		}
	}

	const int simulations = 200000;
	for (int i = 0; i < simulations; i++)
	{
		//Node leaf = traverse(initial_node);
		//simulation_result = rollout(leaf);
		//back_propogate(leaf, simulation_result);
	}

	evaluation.best_move = get_random_move(current_board.get_valid_moves());
	return evaluation;
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
