/*
 * UltimateTicTacToeGame.h
 *
 *  Created on: Mar 20, 2022
 *      Author: John
 */

#ifndef ULTIMATETICTACTOEGAME_H_
#define ULTIMATETICTACTOEGAME_H_

#include "UltimatePlayer.h"

class UltimateTicTacToeGame
{
public:
	UltimateTicTacToeGame(UltimatePlayer*, UltimatePlayer*, int);
	virtual ~UltimateTicTacToeGame();
	void play();
private:
	UltimatePlayer* player1;
	UltimatePlayer* player2;
	int games;
};

#endif /* ULTIMATETICTACTOEGAME_H_ */
