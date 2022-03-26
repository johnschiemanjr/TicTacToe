/*
 * TicTacToePlayer.cpp
 *
 *  Created on: Mar 14, 2022
 *      Author: John
 */

#include "TicTacToePlayer.h"
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

TicTacToePlayer::TicTacToePlayer(Player *player1, Player *player2, int games)
{
	this->games = games;
	this->player1 = player1;
	this->player2 = player2;
}

TicTacToePlayer::~TicTacToePlayer()
{
}

void TicTacToePlayer::play()
{
	int player1Wins = 0;
	int player2Wins = 0;
	int draws = 0;
	srand(time(NULL));
	for (int i = 0; i < games; i++)
	{
		cout << "Game " << i + 1 << endl;
		LocalBoard board = LocalBoard();
		board.print_board();

		vector<Player*> players;

		if (rand() % 2 == 0)
		{
			cout << player1->get_name() << " goes first!" << endl;
			players.push_back(player1);
			players.push_back(player2);
		}
		else
		{
			cout << player2->get_name() << " goes first!" << endl;
			players.push_back(player2);
			players.push_back(player1);
		}

		int turn_counter = 0;
		do
		{
			short move = players[turn_counter % 2]->take_turn(board);
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
				player1Wins++;
			}
			else if (players[turn_counter % 2]->get_name().compare("Computer 2") == 0)
			{
				player2Wins++;
			}
		}

		board.print_board();
	}
	cout << "Computer 1 wins: " << player1Wins << endl;
	cout << "Computer 2 wins: " << player2Wins << endl;
	cout << "Draws: " << draws << endl;
}
