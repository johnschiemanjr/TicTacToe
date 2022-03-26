/*
 * TicTacToeGame.h
 *
 *  Created on: Mar 20, 2022
 *      Author: John
 */

#ifndef TICTACTOEGAME_H_
#define TICTACTOEGAME_H_

#include "Player.h"

class TicTacToeGame
{
public:
	TicTacToeGame(Player*, Player*, int);
	virtual ~TicTacToeGame();
	void play();
private:
	Player* player1;
	Player* player2;
	int games;
};

#endif /* TICTACTOEGAME_H_ */
