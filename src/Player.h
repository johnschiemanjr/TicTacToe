/*
 * Player.h
 *
 *  Created on: Nov 16, 2020
 *      Author: John
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include "Board.h"

using namespace std;

class Player
{
public:
	Player(string, string);
	string get_name() const;
	string get_symbol() const;
	virtual string take_turn(Board) = 0;
	virtual ~Player();
private:
	string player_name;
	string player_symbol;
};

#endif /* PLAYER_H_ */
