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
	MenuItem* moveRight();
	MenuItem* moveLeft();
	MenuItem* moveUp();
	MenuItem* moveDown();

private:
  const char* _itemText;
  void* _leftCallback;
  void* _rightCallback;
  void (*_leftCallbackFunc)(void* callbackObj);
  void (*_rightCallbackFunc)(void* callbackObj);
protected:
  MenuItem* _leftItem;
  MenuItem* _rightItem;
  MenuItem* _downItem;
  MenuItem* _upItem;

};

#endif /* MENUITEM_H_ */
