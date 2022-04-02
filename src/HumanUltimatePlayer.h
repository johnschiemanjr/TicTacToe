/*
 * HumanUltimatePlayer.h
 *
 *  Created on: Mar 26, 2022
 *      Author: John
 */

#ifndef HUMANULTIMATEPLAYER_H_
#define HUMANULTIMATEPLAYER_H_

#include "UltimatePlayer.h"

class HumanUltimatePlayer : public UltimatePlayer
{
public:
	using UltimatePlayer::UltimatePlayer;
	using UltimatePlayer::get_name;
	using UltimatePlayer::get_symbol;
	UltMove take_turn(UltimateBoard) override;
	UltMove take_turn(UltimateBoard, short) override;
	virtual ~HumanUltimatePlayer();
private:
	short take_turn(Board board, short);
};

#endif /* HUMANULTIMATEPLAYER_H_ */
