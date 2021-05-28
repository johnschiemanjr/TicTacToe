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

Node::Node(Node *parent, Board *state, string move, string symbol) : visits(0), total_score(0)
{
	this->parent = parent;
	this->move = move;
	this->symbol_played = symbol;
	if (move.compare("NO_MOVE") != 0)
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

double Node::get_ucb(int iterations) const
{
	double inside_sqrt = (log(iterations)) / visits;
	double outside_sqrt = sqrt(inside_sqrt) * 1.4;
	double vi = total_score / visits;
	return vi + outside_sqrt;
}

