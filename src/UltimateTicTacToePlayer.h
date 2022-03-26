/*
 * UltimateTicTacToePlayer.h
 *
 *  Created on: Mar 14, 2022
 *      Author: John
 */

#ifndef ULTIMATETICTACTOEPLAYER_H_
#define ULTIMATETICTACTOEPLAYER_H_

#include "Player.h"

class UltimateTicTacToePlayer
{
public:
	UltimateTicTacToePlayer(Player*, Player*, int);
	virtual ~UltimateTicTacToePlayer();
	void play();
private:
	Player* player1;
	Player* player2;
	int games;
};

#endif /* ULTIMATETICTACTOEPLAYER_H_ */
