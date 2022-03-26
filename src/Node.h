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
#include "LocalBoard.h"

using namespace std;

class Node
{
public:
	Node *parent;
	vector<Node*> children;
	int visits;
	LocalBoard state;
	short move;
	string symbol_played;
	double total_score;
	Node(Node*, LocalBoard*, short, string);
	~Node();
	void search();
	void rollout();
	double get_ucb(int iterations) const;
};

#endif /* NODE_H_ */
