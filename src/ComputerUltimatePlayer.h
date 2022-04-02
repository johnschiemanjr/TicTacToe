/*
 * ComputerUltimatePlayer.h
 *
 *  Created on: Mar 27, 2022
 *      Author: John
 */

#ifndef COMPUTERULTIMATEPLAYER_H_
#define COMPUTERULTIMATEPLAYER_H_

#include <string>
#include "UltimatePlayer.h"

using namespace std;

class ComputerUltimatePlayer : public UltimatePlayer
{
public:
	using UltimatePlayer::UltimatePlayer;
	using UltimatePlayer::get_name;
	using UltimatePlayer::get_symbol;
	virtual UltMove take_turn(UltimateBoard) = 0;
	virtual UltMove take_turn(UltimateBoard, short) = 0;
	ComputerUltimatePlayer(string, string);
	virtual ~ComputerUltimatePlayer();
};

#endif /* COMPUTERULTIMATEPLAYER_H_ */
