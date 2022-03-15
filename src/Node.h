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
#include <vector>
#include "Board.h"

using namespace std;

class Node
{
public:
	Node *parent;
	vector<Node*> children;
	int visits;
	Board state;
	short move;
	string symbol_played;
	double total_score;
	Node(Node*, Board*, short, string);
	~Node();
	void search();
	void rollout();
	double get_ucb(int iterations) const;
};

#endif /* NODE_H_ */
