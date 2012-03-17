/*
 * MenuItem.h
 *
 *  Created on: 10 Mar 2012
 *      Author: Robin
 */

#ifndef MENUITEM_H_
#define MENUITEM_H_

//typedef void (*menu_callback)(void);

class MenuItem {
public:
	MenuItem();
	void setText(const char * itemText);
	const char* getText();
	const char* getDisplayText();
	void addRight(MenuItem* menuItem);
	void addDown(MenuItem* menuItem);
	void addLeftCallback(void* callbackObj, void (*callbackFunction)(void* callbackObj));
	void addRightCallback(void* callbackObj, void (*callbackFunction)(void* callbackObj));

	void setValue(float value);
	void setValue(int value);
	void setValue(bool value);

	float getFloatValue();
	int getIntValue();
	bool getBoolValue();

	MenuItem* moveRight();
	MenuItem* moveLeft();
	MenuItem* moveUp();
	MenuItem* moveDown();

	MenuItem* _leftItem;
	MenuItem* _rightItem;
	MenuItem* _downItem;
	MenuItem* _upItem;
	// Flag whether we are entering a value
	bool valueEntry;
	enum valuetype_t { Float = 1 << 7, OnOff = 1 << 6, Integer = 1 << 5, Nothing = 0 };
	valuetype_t inputType;
	unsigned long current_value;

private:
  const char* _itemText;
  void* _leftCallback;
  void* _rightCallback;
  void (*_leftCallbackFunc)(void* callbackObj);
  void (*_rightCallbackFunc)(void* callbackObj);
protected:

};

#endif /* MENUITEM_H_ */
