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
	string best_move;
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
	string take_turn(Board) override;
	string get_opposite_symbol(string) const;
	void rollout(Node*) const;
	void rollout_with_log(Node*) const;
	Eval monte_carlo(Board);
	void search(Node*, int) const;
	void search_with_log(Node*, int) const;
	Eval mini_max(Board, bool);
	ComputerPlayer(string, string, Strategy);
	virtual ~ComputerPlayer();
	Strategy strategy;
};

#endif /* COMPUTERPLAYER_H_ */
