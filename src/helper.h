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

const string O = "O";
const string X = "X";

const std::vector<short> spaces =
    { 0b0000000000000001, // 0
      0b0000000000000010,
      0b0000000000000100,
      0b0000000000001000, //3
      0b0000000000010000,
      0b0000000000100000,
      0b0000000001000000, // 6
      0b0000000010000000,
	  0b0000000100000000,
    };

const std::vector<int> wins =
    { 0b0000000000000111,
      0b0000000000111000, // 3 rows
      0b0000000111000000,
      0b0000000100100100,
      0b0000000010010010, // 3 columns
      0b0000000001001001,
      0b0000000100010001, // 2 diagonals
      0b0000000001010100 };

string get_random_move(set<string> valid_moves);
short get_random_move_bitboard(set<short> open_spaces);
string get_opposite_symbol(string);

#endif /* HELPER_H_ */
