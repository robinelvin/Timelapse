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
  valueEntry = 0;
  inputType = Nothing;
  //_rightCallback = _rightCallbackFunc = _leftCallback = _leftCallbackFunc = 0;
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
  if (! valueEntry && _rightItem != 0)
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
  if (! valueEntry && _leftItem != 0)
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
	if (!valueEntry && _upItem != 0)
	{
		return _upItem;
	}
	else
	{
		valueEntry = 0;
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
	  // No lower entry so make this value entry mode
	  valueEntry = 1;
	  return this;
	}
}

void MenuItem::setValue(bool value)
{
	current_value = value;
}

void MenuItem::setValue(float value)
{
	current_value = value * 100;
}

void MenuItem::setValue(int value)
{
	current_value = value;
}

float MenuItem::getFloatValue()
{
	return (float)current_value / 100;
}

int MenuItem::getIntValue()
{
	return (int)current_value;
}

bool MenuItem::getBoolValue()
{
	return current_value >= 1;
}
