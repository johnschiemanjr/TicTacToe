/*
 * Tile.cpp
 *
 *  Created on: Nov 15, 2020
 *      Author: John
 */
#include "Tile.h"
#include <string>
#include <iostream>

using namespace std;

struct InvalidSymbolException : public exception
{
   const char * what () const throw ()
	{
	   return "Invalid Symbol on board:";
	}
};

Tile::Tile(string status)
{
	this->status = status;
}

Tile::~Tile()
{
}

string Tile::get_status() const
{
	return status;
}

void Tile::set_status(string status)
{
	if (!status.compare(O) && !status.compare(X))
	{
		try
		{
			throw InvalidSymbolException();
		}
		catch (InvalidSymbolException& e)
		{
			cout << e.what() << " " << status << endl;
		}
	}
	else
	{
		this->status = status;
	}
}


