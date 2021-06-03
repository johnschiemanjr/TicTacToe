/*
 * Node.h
 *
 *  Created on: Nov 19, 2020
 *      Author: John
 */

#ifndef HELPER_H_
#define HELPER_H_

#include <string>
#include <set>

using namespace std;

string get_random_move(set<string> valid_moves);
string get_opposite_symbol(string);

#endif /* HELPER_H_ */
