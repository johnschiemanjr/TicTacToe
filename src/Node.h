/*
 * Node.h
 *
 *  Created on: Nov 19, 2020
 *      Author: John
 */

#ifndef NODE_H_
#define NODE_H_

#include <string>
#include <memory>
#include <set>
#include "Board.h"

using namespace std;

class Node
{
public:
	Node *parent;
	set<Node*> children;
	int visits;
	bool is_leaf;
	Board state;
	string move;
	double total_score;
	Node(bool, Node*, Board*, string);
	~Node();
	double get_ucb() const;
};

#endif /* NODE_H_ */
