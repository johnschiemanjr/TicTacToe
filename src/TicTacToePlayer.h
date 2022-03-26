/*
 * TicTacToePlayer.h
 *
 *  Created on: Mar 14, 2022
 *      Author: John
 */

#ifndef TICTACTOEPLAYER_H_
#define TICTACTOEPLAYER_H_

#include "Player.h"

class TicTacToePlayer {
public:
	TicTacToePlayer(Player*, Player*, int);
	virtual ~TicTacToePlayer();
	void play();
private:
	Player* player1;
	Player* player2;
	int games;
};

#endif /* TICTACTOEPLAYER_H_ */
