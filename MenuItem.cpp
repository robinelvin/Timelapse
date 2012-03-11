/*
 * MenuItem.cpp
 *
 *  Created on: 10 Mar 2012
 *      Author: Robin
 */

#include "MenuItem.h"

MenuItem::MenuItem()
{
  _downItem = _upItem = _leftItem = _rightItem = 0;
}

void MenuItem::setText(const char* itemText)
{
	_itemText = itemText;
}

const char* MenuItem::getText()
{
  return _itemText;
}

const char* MenuItem::getDisplayText()
{
  return _itemText;
}

// Add items
void MenuItem::addDown(MenuItem* menuItem)
{
  //menuItem->_upItem = this;
  _downItem = menuItem;
}


void MenuItem::addRight(MenuItem* menuItem)
{
  menuItem->_leftItem = this;
  if ( _upItem != 0)
  {
    menuItem->_upItem = _upItem;
  }
  _rightItem = menuItem;
}

void MenuItem::addRightCallback(void* callbackObj, void (*callbackFunction)(void* callbackObj))
{
	_rightCallback = callbackObj;
	_rightCallbackFunc = callbackFunction;
}

void MenuItem::addLeftCallback(void* callbackObj, void (*callbackFunction)(void* callbackObj))
{
	_leftCallback = callbackObj;
	_leftCallbackFunc = callbackFunction;
}

// Navigate items
MenuItem* MenuItem::moveRight()
{
  if (_rightItem)
  {
    return _rightItem;
  }
  else
  {
	  if (_rightCallbackFunc)
	  {
		  _rightCallbackFunc(_rightCallback);
	  }
    return this;
  }
}

MenuItem* MenuItem::moveLeft()
{
  if (_leftItem)
  {
    return _leftItem;
  }
  else
  {
	  if (_leftCallbackFunc)
	  {
		  _leftCallbackFunc(_leftCallback);
	  }
    return this;
  }
}

MenuItem* MenuItem::moveUp()
{
  if (_upItem != 0)
  {
    return _upItem;
  }
  else
  {
    return this;
  }
}

MenuItem* MenuItem::moveDown()
{
  if (_downItem != 0)
  {
    _downItem->_upItem = this;
    return _downItem;
  }
  else
  {
    return this;
  }
}
