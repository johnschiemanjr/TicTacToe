/*
 * RandomUltimatePlayer.h
 *
 *  Created on: Mar 27, 2022
 *      Author: John
 */

#ifndef RANDOMULTIMATEPLAYER_H_
#define RANDOMULTIMATEPLAYER_H_

#include <string>
#include "ComputerUltimatePlayer.h"

class RandomUltimatePlayer : public ComputerUltimatePlayer
{
public:
	using ComputerUltimatePlayer::ComputerUltimatePlayer;
	using ComputerUltimatePlayer::get_name;
	using ComputerUltimatePlayer::get_symbol;
	UltMove take_turn(UltimateBoard) override;
	UltMove take_turn(UltimateBoard, short) override;
	RandomUltimatePlayer(string, string);
	virtual ~RandomUltimatePlayer();
};

#endif /* RANDOMULTIMATEPLAYER_H_ */
