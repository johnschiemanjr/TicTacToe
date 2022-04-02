/*
 * UltimatePlayer.h
 *
 *  Created on: Mar 26, 2022
 *      Author: John
 */

#ifndef ULTIMATEPLAYER_H_
#define ULTIMATEPLAYER_H_

#include <string>
#include "helper.h"
#include "UltimateBoard.h"

using namespace std;

class UltimatePlayer
{
public:
	UltimatePlayer(string, string);
	string get_name() const;
	string get_symbol() const;
	virtual UltMove take_turn(UltimateBoard) = 0;
	virtual UltMove take_turn(UltimateBoard, short) = 0;
	virtual ~UltimatePlayer();
private:
	string player_name;
	string player_symbol;
};

#endif /* ULTIMATEPLAYER_H_ */
