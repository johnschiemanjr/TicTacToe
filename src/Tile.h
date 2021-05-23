/*
 * Tile.h
 *
 *  Created on: Nov 15, 2020
 *      Author: John
 */

#ifndef TILE_H_
#define TILE_H_

#include <string>

using namespace std;

const string O = "O";
const string X = "X";

class Tile
{
public:
	Tile(string status);
	string get_status() const;
	void set_status(string status);
	virtual ~Tile();
private:
	string status;
};


#endif /* TILE_H_ */
