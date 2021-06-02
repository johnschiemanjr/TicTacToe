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

	Node initial_node = Node(NULL, &current_board, "NO_MOVE", "NO_SYMBOL");
	// get children nodes
	for (auto move : current_board.get_valid_moves())
	{
		Node *child = new Node(&initial_node, &current_board, move, get_symbol());
		initial_node.children.push_back(child);
	}

	const int ITERATIONS_CONSTANT = 10000;
	bool problem_game = false;
	for (int iterations = 0; iterations < ITERATIONS_CONSTANT; iterations++)
	{
		if (iterations == 5000)
		{
			if (current_board.get_valid_moves().size() == 8)
			{
				for(auto child : initial_node.children)
				{
					double average_score = child->total_score / child->visits;
					cout << "Move " << child->move << " Total score : " << child->total_score << " visits: " << child->visits << " for an average score of " << average_score << endl;
				}
				if (initial_node.children[2]->total_score > initial_node.children[4]->total_score
						|| initial_node.children[0]->total_score > initial_node.children[4]->total_score
						|| initial_node.children[6]->total_score > initial_node.children[4]->total_score)
				{
					cout << "Possible problem game." << endl;
					problem_game = false;
					//getchar();
				}
			}

		}
		if (!problem_game)
		{
			search(&initial_node, iterations);
		}
		else
		{
			getchar();
			search_with_log(&initial_node, iterations);
		}
	}

	double max_score = -99999999;
	evaluation.best_move = get_random_move(current_board.get_valid_moves());
	for(auto child : initial_node.children)
	{
		double average_score = child->total_score / child->visits;
		if (average_score > max_score)
		{
			max_score = average_score;
			evaluation.best_move = child->move;
		}
		cout << "Move " << child->move << " Total score : " << child->total_score << " visits: " << child->visits << " for an average score of " << average_score << endl;
	}


	cout << "Best move: " << evaluation.best_move << endl;
	return evaluation;
}

void ComputerPlayer::search(Node *current_node, int iterations) const
{
	//cout << "Searching for move " << current_node->move << endl;
	// check if leaf node
	if (current_node->children.size() == 0)
	{
		//cout << "It's a leaf node!" << endl;
		// leaf node
		if (current_node->visits == 0)
		{
			//cout << "No visits, rolling out!" << endl;
			Board current_board = current_node->state.copy_board();
			rollout(current_node);
			current_node->state = current_board.copy_board();
		}
		else
		{
			//cout << "We've visited this node before. Here's the board we're evaluating:" << endl;
			//current_node->state.print_board();
			if (current_node->state.is_game_over())
			{
				//cout << "This is a terminal node! Rollout to get eval." << endl;
				rollout(current_node);
			}
			else
			{
				//cout << "Not a terminal node. Let's create it's children." << endl;
				for (auto move : current_node->state.get_valid_moves())
				{
					Node *child = new Node(current_node, &current_node->state, move, get_opposite_symbol(current_node->symbol_played));
					current_node->children.push_back(child);
				}
				//cout << current_node->children.size() << endl;
				search(current_node->children[0], iterations);
			}
		}
	}
	else
	{
		// not a leaf node
		//cout << "NOT a leaf node!" << endl;
		// call search on child node that maximizes UCB
		double max_ucb = -9999999; // -1 is the minimum
		Node *move_to_explore = NULL;
		vector<Node*> children = current_node->children;
		if (current_node->symbol_played.compare(get_symbol()))
		{
			//cout << "It's my turn, so pick the move that looks the most promising..." << endl;
			//cout << "Calculating UCB values..." << endl;
			for(auto child : children)
			{
				if (child->visits == 0)
				{
					//cout << child->move << " has not been visited...calling search on this move" << endl;
					search(child, iterations);
					return;
				}
				else
				{
					if (child->get_ucb(current_node->visits) > max_ucb)
					{
						max_ucb = child->get_ucb(current_node->visits);
						move_to_explore = child;
					}
					//cout << child->move << " " << child->get_ucb(current_node->visits) << " total wins: "<< child->total_score << endl;
				}
			}
		}
		else
		{
			auto r = rand() % children.size();
			auto it = begin(children);
			advance(it, r);
			move_to_explore = *it;
		}

		//cout << "Exploring " << move_to_explore->move << endl;
		search(move_to_explore, iterations);
	}
}

void ComputerPlayer::rollout(Node *node) const
{
	//cout << "Simulating move " << node->move << endl;
	//node->state.print_board();
	string symbol_to_play = get_opposite_symbol(node->symbol_played);
	while (!node->state.is_game_over())
	{
		node->state.make_move(get_random_move(node->state.get_valid_moves()), symbol_to_play);
		symbol_to_play = get_opposite_symbol(symbol_to_play);
		//node->state.print_board();
	}

	int eval = 0;
	if (!node->state.has_winner())
	{
		//cout << "Simulation was a draw!" << endl;
	}
	else if (symbol_to_play.compare(get_symbol()))
	{
		//cout << "I have won the simulation!" << endl;;
		eval = 1;
		node->total_score++;
	}
	else
	{
		//cout << "My opponent has won the simulation!" << endl;
		eval = -1;
		node->total_score--;
	}
	//cout << "Back propogating this information up the tree..." << endl;
	Node *parent_node = node->parent;
	while (parent_node)
	{
		parent_node->visits++;
		parent_node->total_score = parent_node->total_score + eval;
		parent_node = parent_node->parent;
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

void ComputerPlayer::search_with_log(Node *current_node, int iterations) const
{
	cout << "Searching for move " << current_node->move << endl;
	// check if leaf node
	if (current_node->children.size() == 0)
	{
		cout << "It's a leaf node!" << endl;
		// leaf node
		if (current_node->visits == 0)
		{
			cout << "No visits, rolling out!" << endl;
			Board current_board = current_node->state.copy_board();
			rollout_with_log(current_node);
			current_node->state = current_board.copy_board();
		}
		else
		{
			cout << "We've visited this node before. Here's the board we're evaluating:" << endl;
			current_node->state.print_board();
			if (current_node->state.is_game_over())
			{
				cout << "This is a terminal node! Rollout to get eval." << endl;
				rollout_with_log(current_node);
			}
			else
			{
				cout << "Not a terminal node. Let's create it's children." << endl;
				for (auto move : current_node->state.get_valid_moves())
				{
					Node *child = new Node(current_node, &current_node->state, move, get_opposite_symbol(current_node->symbol_played));
					current_node->children.push_back(child);
				}
				cout << current_node->children.size() << endl;
				search_with_log(current_node->children[0], iterations);
			}
		}
	}
	else
	{
		// not a leaf node
		cout << "NOT a leaf node!" << endl;
		// call search on child node that maximizes UCB
		double max_ucb = -9999999; // -1 is the minimum
		Node *move_to_explore = NULL;
		vector<Node*> children = current_node->children;
		if (current_node->symbol_played.compare(get_symbol()))
		{
			cout << "It's my turn, so pick the move that looks the most promising..." << endl;
			cout << "Calculating UCB values..." << endl;
			for(auto child : children)
			{
				if (child->visits == 0)
				{
					cout << child->move << " has not been visited...calling search on this move" << endl;
					search_with_log(child, iterations);
					return;
				}
				else
				{
					if (child->get_ucb(current_node->visits) > max_ucb)
					{
						max_ucb = child->get_ucb(current_node->visits);
						move_to_explore = child;
					}
					cout << child->move << " " << child->get_ucb(current_node->visits) << " total wins: "<< child->total_score << endl;
				}
			}
		}
		else
		{
			auto r = rand() % children.size();
			auto it = begin(children);
			advance(it, r);
			move_to_explore = *it;
		}

		cout << "Exploring " << move_to_explore->move << endl;
		search_with_log(move_to_explore, iterations);
	}
}

void ComputerPlayer::rollout_with_log(Node *node) const
{
	cout << "Simulating move " << node->move << endl;
	node->state.print_board();
	string symbol_to_play = get_opposite_symbol(node->symbol_played);
	while (!node->state.is_game_over())
	{
		node->state.make_move(get_random_move(node->state.get_valid_moves()), symbol_to_play);
		symbol_to_play = get_opposite_symbol(symbol_to_play);
		node->state.print_board();
	}

	int eval = 0;
	if (!node->state.has_winner())
	{
		cout << "Simulation was a draw!" << endl;
	}
	else if (symbol_to_play.compare(get_symbol()))
	{
		cout << "I have won the simulation!" << endl;;
		eval = 1;
		node->total_score++;
	}
	else
	{
		cout << "My opponent has won the simulation!" << endl;
		eval = -1;
		node->total_score--;
	}
	cout << "Back propogating this information up the tree..." << endl;
	Node *parent_node = node->parent;
	while (parent_node)
	{
		parent_node->visits++;
		parent_node->total_score = parent_node->total_score + eval;
		parent_node = parent_node->parent;
	}
	node->visits++;
}
