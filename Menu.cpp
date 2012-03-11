/*
 * Menu.cpp
 *
 *  Created on: 10 Mar 2012
 *      Author: Robin
 */

#include "Menu.h"

Menu::Menu()
{

}

void Menu::SetRoot(MenuItem* rootItem)
{
	_root = rootItem;
	_current = rootItem;
}

MenuItem* Menu::getCurrent()
{
	return _current;
}

MenuItem* Menu::moveDown()
{
	_current = _current->moveDown();
	return _current;
}

MenuItem* Menu::moveUp()
{
	_current = _current->moveUp();
	return _current;
}

MenuItem* Menu::moveLeft()
{
	_current = _current->moveLeft();
	return _current;
}

MenuItem* Menu::moveRight()
{
	_current = _current->moveRight();
	return _current;
}
