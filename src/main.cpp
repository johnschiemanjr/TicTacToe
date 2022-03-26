#include <iostream>
#include "TicTacToePlayer.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"
#include "helper.h"
#include "UltimateTicTacToePlayer.h"
#include "HumanUltimatePlayer.h"

using namespace std;

int main()
{
	Player *player1 = new HumanUltimatePlayer("Human 1", O);
	Player *player2 = new HumanUltimatePlayer("Human 2", X);
	//ComputerPlayer *player1 = new ComputerPlayer("Computer 1", O, ComputerPlayer::Strategy::RANDOM);
	//ComputerPlayer *player2 = new ComputerPlayer("Computer 2", X, ComputerPlayer::Strategy::MONTE_CARLO);

	UltimateTicTacToePlayer game = UltimateTicTacToePlayer(player1, player2, 1);
	//TicTacToePlayer game = TicTacToePlayer(player1, player2, 1);

	game.play();

	delete player1;
	delete player2;

	return 0;
}
