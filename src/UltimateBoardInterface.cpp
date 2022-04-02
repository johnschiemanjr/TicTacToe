/*
 * UltimateBoardInterface.cpp
 *
 *  Created on: Mar 20, 2022
 *      Author: John
 */

#include "UltimateBoardInterface.h"
#include <iostream>

using namespace std;

UltimateBoardInterface::UltimateBoardInterface()
{
}

UltimateBoardInterface::~UltimateBoardInterface()
{
}

void UltimateBoardInterface::print_board(Board *boards) const
{
	cout << "\n";
	for (int i = 0; i < 3; i++)
	{
		boards[3*i].print_row(0, 1, 2);
		cout << "   | ";
		boards[3*i+1].print_row(0, 1, 2);
		cout << "   | ";
		boards[3*i+2].print_row(0, 1, 2);
		cout << "  " << endl;
		cout << "-----|-----|----- | -----|-----|----- | -----|-----|-----" << endl;
		boards[3*i].print_row(3, 4, 5);
		cout << "   | ";
		boards[3*i+1].print_row(3, 4, 5);
		cout << "   | ";
		boards[3*i+2].print_row(3, 4, 5);
		cout << "  " << endl;
		cout << "-----|-----|----- | -----|-----|----- | -----|-----|-----" << endl;
		boards[3*i].print_row(6, 7, 8);
		cout << "   | ";
		boards[3*i+1].print_row(6, 7, 8);
		cout << "   | ";
		boards[3*i+2].print_row(6, 7, 8);
		cout << "  " << endl;
		if (i != 2)
		{
			cout << "==================|===================|===================" << endl;
		}
	}
	cout << "\n";
}
