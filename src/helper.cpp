/*
 * Helper.cpp
 *
 *  Created on: Nov 15, 2020
 *      Author: John
 */

#include <iostream>
#include <set>
#include "Tile.h"

using namespace std;
template<typename S>
auto select_random(const S &s, size_t n)
{
	auto it = begin(s);
	advance(it,n);
	return it;
}

string get_random_move(set<string> valid_moves)
{
	auto r = rand() % valid_moves.size();
	return *select_random(valid_moves, r);
}

string get_opposite_symbol(string symbol)
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
