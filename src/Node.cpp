/*
 * Node.cpp
 *
 *  Created on: Nov 19, 2020
 *      Author: John
 */

#include "Node.h"
#include <memory>

Node::Node(bool is_leaf, Node *parent) : visits(0), total_score(0)
{
	this->is_leaf = is_leaf;
	this->parent = parent;
}

Node::~Node()
{
}


