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

using namespace std;

class Node
{
public:
	Node *parent;
	int visits;
	bool is_leaf;
	double total_score;
	Node(bool, Node*);
	~Node();
};

#endif /* NODE_H_ */
