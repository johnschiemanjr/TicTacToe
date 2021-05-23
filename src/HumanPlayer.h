/*
 * HumanPlayer.h
 *
 *  Created on: Nov 16, 2020
 *      Author: John
 */

#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

#include <string>
#include "Player.h"

using namespace std;

class HumanPlayer : public Player
{
public:
	using Player::Player;
	using Player::get_name;
	using Player::get_symbol;
	string take_turn(Board board) override;
	virtual ~HumanPlayer();
};

#endif /* HUMANPLAYER_H_ */
