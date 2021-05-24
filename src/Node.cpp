/*
 * Node.cpp
 *
 *  Created on: Nov 19, 2020
 *      Author: John
 */

#include "Node.h"
#include <memory>
#include <set>

Node::Node(bool is_leaf, Node *parent, Board *state, string move) : visits(0), total_score(0)
{
	this->is_leaf = is_leaf;
	this->parent = parent;
	this->move = move;
	if (move.compare("NO_MOVE") != 0)
	{
		this->state = state->copy_board();
		this->state.make_move(move, "O");
	}
}

Node::~Node()
{
	for(auto child : children)
	{
	  delete child;
	}
}

double Node::get_ucb() const
{
	return 1.2;
}

