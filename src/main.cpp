#include <iostream>
#include <vector>
#include <time.h>
#include <random>
#include "Board.h"
#include "Player.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"
#include "Tile.h"
#include <utility>
#include <memory>

using namespace std;

int main()
{
	int humanWins = 0;
	int compWins = 0;
	int draws = 0;
	srand(time(NULL));
	for (int i = 0; i < 100; i++)
	{
	cout << "Game " << i + 1 << endl;
	Board board = Board();
	board.print_board();

	//HumanPlayer *human = new HumanPlayer("Computer 1", O);
	ComputerPlayer *human = new ComputerPlayer("Computer 1", O, ComputerPlayer::Strategy::MONTE_CARLO);
	ComputerPlayer *computer = new ComputerPlayer("Computer 2", X, ComputerPlayer::Strategy::RANDOM);
	vector<Player*> players;

	if (rand() % 2 == 0)
	{
		cout << human->get_name() << " goes first!" << endl;
		players.push_back(human);
		players.push_back(computer);
	}
	else
	{
		cout << computer->get_name() << " goes first!" << endl;
		players.push_back(computer);
		players.push_back(human);
	}

	int turn_counter = 0;
	do
	{
		string move = players[turn_counter % 2]->take_turn(board);
		board.make_move(move, players[turn_counter % 2]->get_symbol());
		turn_counter++;

		board.print_board();

	} while (!board.is_game_over());

	const int MAX_MOVES = 9;
	if (turn_counter == MAX_MOVES && !board.has_winner())
	{
		cout << "It's a draw!" << endl;
		draws++;
	}
	else
	{
		cout << players[--turn_counter % 2]->get_name() << " is the winner!" << endl;
		if (players[turn_counter % 2]->get_name().compare("Computer 1") == 0)
		{
			humanWins++;
		}
		else if (players[turn_counter % 2]->get_name().compare("Computer 2") == 0)
		{
			compWins++;
		}
	}

	board.print_board();

	delete human;
	delete computer;
	}
	cout << "Computer 1 wins: " << humanWins << endl;
	cout << "Computer 2 wins: " << compWins << endl;
	cout << "Draws : " << draws << endl;
	return 0;
}
