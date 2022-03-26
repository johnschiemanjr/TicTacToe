/*
 * UltimateBoardInterface.h
 *
 *  Created on: Mar 20, 2022
 *      Author: John
 */

#ifndef ULTIMATEBOARDINTERFACE_H_
#define ULTIMATEBOARDINTERFACE_H_

#include "Board.h"

class UltimateBoardInterface {
public:
	UltimateBoardInterface();
	virtual ~UltimateBoardInterface();
	void print_board(Board*) const;
};


#endif /* ULTIMATEBOARDINTERFACE_H_ */
