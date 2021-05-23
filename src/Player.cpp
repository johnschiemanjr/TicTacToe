/*
 * Player.cpp
 *
 *  Created on: Nov 16, 2020
 *      Author: John
 */

#include "Player.h"
#include <string>
#include <iostream>

using namespace std;

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


