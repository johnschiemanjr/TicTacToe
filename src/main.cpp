#include <iostream>
#include <vector>
#include <time.h>
#include <random>
#include "Board.h"
#include "Player.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"
#include <utility>
#include <memory>
#include "helper.h"
#include "TicTacToeGame.h"
#include "UltimateTicTacToeGame.h"

using namespace std;

int main()
{
	//Player *player1 = new HumanUltimatePlayer("Human 1", O);
	//Player *player2 = new HumanUltimatePlayer("Human 2", X);
	ComputerPlayer *player1 = new ComputerPlayer("Computer 1", O, ComputerPlayer::Strategy::RANDOM);
	ComputerPlayer *player2 = new ComputerPlayer("Computer 2", X, ComputerPlayer::Strategy::MONTE_CARLO);

	UltimateTicTacToeGame game = UltimateTicTacToeGame(player1, player2, 1);
	//TicTacToeGame game = TicTacToeGame(player1, player2, 1);

	game.play();

	delete player1;
	delete player2;

	return 0;
}
