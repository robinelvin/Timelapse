/*
 * Menu.h
 *
 *  Created on: 10 Mar 2012
 *      Author: Robin
 */

#ifndef MENU_H_
#define MENU_H_

#include "MenuItem.h"

class Menu
{
public:
	Menu();
	void SetRoot(MenuItem*);
	MenuItem* getCurrent();
	MenuItem* moveUp();
	MenuItem* moveDown();
	MenuItem* moveLeft();
	MenuItem* moveRight();

private:
    MenuItem* _root;
    MenuItem* _current;

};

#endif /* MENU_H_ */
