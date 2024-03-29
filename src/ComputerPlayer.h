/*
 * ComputerPlayer.h
 *
 *  Created on: Nov 16, 2020
 *      Author: John
 */

#ifndef COMPUTERPLAYER_H_
#define COMPUTERPLAYER_H_

#include <string>
#include "Player.h"
#include "Node.h"

using namespace std;

struct Eval
{
	short best_move;
	int evaluation;
};

class ComputerPlayer : public Player
{
public:
	enum class Strategy
	{
		RANDOM,
		MINIMAX,
		MONTE_CARLO
	};

	using Player::Player;
	using Player::get_name;
	using Player::get_symbol;
	short take_turn(Board) override;
	Eval monte_carlo(Board);
	Eval mini_max(Board, bool);
	ComputerPlayer(string, string, Strategy);
	virtual ~ComputerPlayer();
	Strategy strategy;
};

#endif /* COMPUTERPLAYER_H_ */
