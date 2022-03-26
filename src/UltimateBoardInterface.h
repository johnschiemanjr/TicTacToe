/*
 * UltimateBoardInterface.h
 *
 *  Created on: Mar 14, 2022
 *      Author: John
 */

#ifndef ULTIMATEBOARDINTERFACE_H_
#define ULTIMATEBOARDINTERFACE_H_

#include "LocalBoard.h"

class UltimateBoardInterface {
public:
	UltimateBoardInterface();
	virtual ~UltimateBoardInterface();
	void print_board(LocalBoard*) const;
};

#endif /* ULTIMATEBOARDINTERFACE_H_ */
