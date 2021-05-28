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

void ComputerPlayer::search(Node *node) const
{

}

Eval ComputerPlayer::monte_carlo(Board current_board)
{
	Eval evaluation;

	Node initial_node = Node(false, NULL, &current_board, "NO_MOVE", "NO_SYMBOL");


	// get children nodes
	vector<Node*> children = initial_node.children;
	for (auto move : current_board.get_valid_moves())
	{
		Node *child = new Node(true, &initial_node, &current_board, move, get_symbol());
		children.push_back(child);
	}

	string move_to_explore = children[0]->move;
	const int ITERATIONS_CONSTANT = 10;
	for (int iterations = 0; iterations < ITERATIONS_CONSTANT; iterations++)
	{
		cout << "Calculating UCB values..." << endl;
		double max_ucb = 0;
		for(auto child : children)
		{
			if (child->visits == 0)
			{
				cout << child->move << " has not been visited...rolling out." << endl;
				rollout(child);
				break;
			}
			else
			{
				if (child->get_ucb(iterations) > max_ucb)
				{
					max_ucb = child->get_ucb(iterations);
					move_to_explore = child->move;
				}
				cout << child->move << " " << child->get_ucb(iterations) << endl;
			}
		}
		cout << "Exploring " << move_to_explore << endl;
	}

	for(auto child : children)
	{
		delete child;
	}

	evaluation.best_move = move_to_explore;
	return evaluation;
}

void ComputerPlayer::rollout(Node *node) const
{
	cout << "Simulating move " << node->move << endl;
	string next_symbol = get_opposite_symbol(get_symbol());
	while (!node->state.is_game_over())
	{
		node->state.make_move(get_random_move(node->state.get_valid_moves()), next_symbol);
		next_symbol = get_opposite_symbol(next_symbol);
		node->state.print_board();
	}

	if (!node->state.has_winner())
	{
		cout << "Simulation was a draw!" << endl;
	}
	else if (next_symbol.compare(get_symbol()))
	{
		cout << "I have won the simulation!" << endl;;
		node->total_score++;
	}
	else
	{
		cout << "My opponent has won the simulation!" << endl;
		node->total_score--;
	}
	node->visits++;
}

Eval ComputerPlayer::mini_max(Board current_board, bool maximizing_player)
{
	Eval evaluation;
	if (current_board.is_game_over())
	{
		if (current_board.get_valid_moves().size() == 0 && !current_board.has_winner())
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
