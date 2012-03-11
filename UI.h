/*
 * UI.h
 *
 *  Created on: 6 Mar 2012
 *      Author: Robin Elvin
 */

#ifndef UI_H_
#define UI_H_
#include "Arduino.h"
#include <LiquidCrystal.h>
#include <HardwareSerial.h>
#include "Menu.h"
#include "MenuItem.h"

class UI {
public:
	UI();
	virtual ~UI();
	void InitUserInterface();
	void CheckUI();
	static void LCDBrighter(void* callbackObj);
	static void LCDDarker(void* callbackObj);

private:
	// last read button (analog) value
	int _last_button_read;
	byte _button_pressed;
	byte _last_button_pressed;
	LiquidCrystal lcd;
	bool CheckButtonPressed();
	void UpdateMenu();
	Menu menu;
	MenuItem rootItem;
	MenuItem lcdBrightness;
	int _lcd_brightness;
};

// lcd pins
#define LCD_RS  2
#define LCD_EN  8
#define LCD_D4  7
#define LCD_D5  6
#define LCD_D6  5
#define LCD_D7  4

// lcd backlight pin
#define LCD_BKL 9
// which input is our button
#define BUT_PIN A0

// which buttons?
#define BUT_UP 2
#define BUT_DN 3
#define BUT_LT 1
#define BUT_RT 4
#define BUT_NONE 0

// analog button read values
#define BUT0_VAL  930
#define BUT1_VAL  854
#define BUT2_VAL  788
#define BUT3_VAL  732

// button variance range
#define BUT_THRESH  10

// how many ms does a button have
// to be held before triggering another
// action? (for scrolling, etc.)

#define HOLD_BUT_MS 200

// how much to increment for each cycle the button is held?

#define HOLD_BUT_VALINC 10

#endif /* UI_H_ */
