/*
 * Node.cpp
 *
 *  Created on: Nov 19, 2020
 *      Author: John
 */

#include "Node.h"
#include <memory>
#include <set>
#include <math.h>
#include "helper.h"
#include <set>

Node::Node(Node *parent, Board *state, short move, string symbol) : visits(0), total_score(0)
{
	this->parent = parent;
	this->move = move;
	this->symbol_played = symbol;
	if (move != -1)
	{
		this->state = state->copy_board();
		this->state.make_move(move, symbol);
	}
}

Node::~Node()
{
	for(auto child : children)
	{
	  delete child;
	}
}

void Node::rollout()
{
	string symbol_to_play = get_opposite_symbol(symbol_played);
	while (!state.is_game_over())
	{
		state.make_move(get_random_move_bitboard(state.get_open_spaces()), symbol_to_play);
		symbol_to_play = get_opposite_symbol(symbol_to_play);
	}

	int eval = 0;
	if (!state.has_winner())
	{
		// simulation was a draw
	}
	else if (symbol_to_play.compare(get_opposite_symbol(symbol_played)))
	{
		eval = -1;
		total_score--;
	}
	else
	{
		eval = 1;
		total_score++;
	}

	Node *parent_node = parent;
	while (parent_node)
	{
		eval *= -1;
		parent_node->visits++;
		parent_node->total_score = parent_node->total_score + eval;
		parent_node = parent_node->parent;
	}
	visits++;
}

void Node::search()
{
	// check if leaf node
	if (children.size() == 0)
	{
		// leaf node
		if (visits == 0)
		{
			Board current_board = state.copy_board();
			rollout();
			state = current_board.copy_board();
		}
		else
		{
			if (state.is_game_over())
			{
				rollout();
			}
			else
			{
				for (auto move : state.get_open_spaces())
				{
					Node *child = new Node(this, &state, move, get_opposite_symbol(symbol_played));
					children.push_back(child);
				}
				children[0]->search();
			}
		}
	}
	else
	{
		// not a leaf node
		// call search on child node that maximizes UCB
		double max_ucb = -9999999; // -1 is the minimum
		Node *move_to_explore = NULL;
		for(auto child : children)
		{
			if (child->visits == 0)
			{
				child->search();
				return;
			}
			else
			{
				if (child->get_ucb(visits) > max_ucb)
				{
					max_ucb = child->get_ucb(visits);
					move_to_explore = child;
				}
			}
		}

		move_to_explore->search();
	}
}

double Node::get_ucb(int iterations) const
{
	double inside_sqrt = (log(iterations)) / visits;
	double outside_sqrt = sqrt(inside_sqrt) * 1.4;
	double vi = total_score / visits;
	return vi + outside_sqrt;
}

