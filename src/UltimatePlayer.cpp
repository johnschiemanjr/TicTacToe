/*
 * UltimatePlayer.cpp
 *
 *  Created on: Mar 26, 2022
 *      Author: John
 */

#include "UltimatePlayer.h"

UltimatePlayer::UltimatePlayer(string player_name, string player_symbol)
{
	this->player_name = player_name;
	this->player_symbol = player_symbol;
}

UltimatePlayer::~UltimatePlayer()
{
}

string UltimatePlayer::get_name() const
{
	return player_name;
}

string UltimatePlayer::get_symbol() const
{
	return player_symbol;
}
