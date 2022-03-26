/*
 * UltimateTicTacToeGame.h
 *
 *  Created on: Mar 20, 2022
 *      Author: John
 */

#ifndef ULTIMATETICTACTOEGAME_H_
#define ULTIMATETICTACTOEGAME_H_

#include "Player.h"

class UltimateTicTacToeGame
{
public:
	UltimateTicTacToeGame(Player*, Player*, int);
	virtual ~UltimateTicTacToeGame();
	void play();
private:
	Player* player1;
	Player* player2;
	int games;
};

#endif /* ULTIMATETICTACTOEGAME_H_ */
