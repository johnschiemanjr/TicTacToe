/*
 * UltimateTicTacToePlayer.cpp
 *
 *  Created on: Mar 14, 2022
 *      Author: John
 */

#include "UltimateTicTacToePlayer.h"
#include <iostream>
#include <vector>
#include <time.h>
#include <random>
#include "Board.h"
#include "UltimateBoard.h"
#include "Player.h"
#include "ComputerPlayer.h"
#include "HumanUltimatePlayer.h"
#include <utility>
#include <memory>
#include "helper.h"
#include "UltimateBoardInterface.h"

UltimateTicTacToePlayer::UltimateTicTacToePlayer(Player *player1, Player *player2, int games)
{
	this->games = games;
	this->player1 = player1;
	this->player2 = player2;
}

UltimateTicTacToePlayer::~UltimateTicTacToePlayer()
{
}

void UltimateTicTacToePlayer::play()
{
	int player1Wins = 0;
	int player2Wins = 0;
	int draws = 0;
	srand(time(NULL));
	for (int i = 0; i < games; i++)
	{
		cout << "Game " << i + 1 << endl;
		UltimateBoard ult_board = UltimateBoard();
		UltimateBoardInterface interface = UltimateBoardInterface();
		interface.print_board(ult_board.get_boards());

		HumanUltimatePlayer *player1 = new HumanUltimatePlayer("Human 1", O);
		HumanUltimatePlayer *player2 = new HumanUltimatePlayer("Human 2", X);
		vector<HumanUltimatePlayer*> players;

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
			UltMove move = players[turn_counter % 2]->take_turn(ult_board);
			ult_board.make_move(move, players[turn_counter % 2]->get_symbol());
			turn_counter++;

			interface.print_board(ult_board.get_boards());

		} while (!ult_board.is_game_over());

		const int MAX_MOVES = 9;
		if (turn_counter == MAX_MOVES && !ult_board.has_winner())
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

		interface.print_board(ult_board.get_boards());
	}
	cout << "Computer 1 wins: " << player1Wins << endl;
	cout << "Computer 2 wins: " << player2Wins << endl;
	cout << "Draws: " << draws << endl;
}

