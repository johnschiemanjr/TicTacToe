/*
 * HumanUltimatePlayer.h
 *
 *  Created on: Mar 19, 2022
 *      Author: John
 */

#ifndef HUMANULTIMATEPLAYER_H_
#define HUMANULTIMATEPLAYER_H_

#include <string>
#include "Player.h"
#include "helper.h"
#include "UltimateBoard.h"

class HumanUltimatePlayer : public Player
{
public:
	using Player::Player;
	using Player::get_name;
	using Player::get_symbol;
	UltMove take_turn(UltimateBoard);
	HumanUltimatePlayer();
	virtual ~HumanUltimatePlayer();
private:
	short take_turn(Board board) override;
};

#endif /* HUMANULTIMATEPLAYER_H_ */
