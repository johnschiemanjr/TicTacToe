/*
 * Player.cpp
 *
 *  Created on: Nov 16, 2020
 *      Author: John
 */

#include "Player.h"
#include <string>
#include <iostream>
#include <time.h>
#include <random>
#include <string>


using namespace std;

template<typename S>
auto select_random(const S &s, size_t n)
{
	auto it = begin(s);
	advance(it,n);
	return it;
}

Player::Player(string player_name, string player_symbol)
{
	this->player_name = player_name;
	this->player_symbol = player_symbol;
}

Player::~Player()
{
}

string Player::get_name() const
{
	return player_name;
}

string Player::get_symbol() const
{
	return player_symbol;
}

string Player::get_random_move(set<string> valid_moves) const
{
	auto r = rand() % valid_moves.size();
	return *select_random(valid_moves, r);
}


