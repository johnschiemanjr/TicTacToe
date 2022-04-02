#include <iostream>
#include <vector>
#include <time.h>
#include <random>
#include "Board.h"
#include "Player.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"
#include "HumanUltimatePlayer.h"
#include "RandomUltimatePlayer.h"
#include <utility>
#include <memory>
#include "helper.h"
#include "TicTacToeGame.h"
#include "UltimateTicTacToeGame.h"

using namespace std;

int main()
{
	//UltimatePlayer *player1 = new RandomUltimatePlayer("Human 1", O);
	//UltimatePlayer *player2 = new RandomUltimatePlayer("Human 2", X);
	ComputerPlayer *player1 = new ComputerPlayer("Computer 1", O, ComputerPlayer::Strategy::MINIMAX);
	ComputerPlayer *player2 = new ComputerPlayer("Computer 2", X, ComputerPlayer::Strategy::MONTE_CARLO);

	//UltimateTicTacToeGame game = UltimateTicTacToeGame(player1, player2, 1);
	TicTacToeGame game = TicTacToeGame(player1, player2, 100);

	game.play();

	delete player1;
	delete player2;

	return 0;
}
