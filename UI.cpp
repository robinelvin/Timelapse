/*
 * UI.cpp
 *
 *  Created on: 6 Mar 2012
 *      Author: Robin Elvin
 */

#include "UI.h"

UI::UI() : lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7),
		menu(),
		rootItem(),
		lcdBrightness()
{
	_last_button_read = 1023;
	_button_pressed = 0;
	pinMode(LCD_BKL, OUTPUT);
}

UI::~UI()
{
	// TODO Auto-generated destructor stub
}

void UI::InitUserInterface()
{

	_last_button_pressed = BUT_NONE;
	lcdBrightness = MenuItem();
	lcdBrightness.setText("LCD Brightness");
	lcdBrightness.addLeftCallback((void *)this, UI::LCDDarker);
	lcdBrightness.addRightCallback((void *)this, UI::LCDBrighter);
	rootItem = MenuItem();
	rootItem.setText("Settings");
	rootItem.addDown(&lcdBrightness);
	menu.SetRoot(&rootItem);

    // fade up lcd backlight
    for (int d=255; d>0; d--)
    {
        analogWrite(LCD_BKL, d);
        delay(10);
    }
    _lcd_brightness = 255;

    // init lcd to 16x2 display
    lcd.begin(16, 2);

    // clear and turn on autoscroll
    lcd.clear();
    //lcd.autoscroll();

   // banner
    lcd.setCursor(2,0);

    lcd.print("(c)2012 Elvin");

    lcd.setCursor(1,1);
    lcd.print("Consulting Ltd");

    delay(2000);

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Timelapse Engine");
    lcd.setCursor(4,1);
    lcd.print("Version 0.1");

    // setup button input
    pinMode(BUT_PIN, INPUT);

    delay(3000);
    UpdateMenu();
}

void UI::CheckUI()
{
	// Update button state
	if (CheckButtonPressed())
	{
		if (_button_pressed != _last_button_pressed)
		{
			Serial.println(_button_pressed);
			switch (_button_pressed)
			{
			case BUT_UP:
				menu.moveUp();
				break;
			case BUT_DN:
				menu.moveDown();
				break;
			case BUT_LT:
				menu.moveLeft();
				break;
			case BUT_RT:
				menu.moveRight();
				break;
			}
			UpdateMenu();

			_last_button_pressed = _button_pressed;
		}
	}
}

void UI::LCDBrighter(void* ptrUI)
{
	UI* me = (UI*)ptrUI;
	analogWrite(LCD_BKL, me->_lcd_brightness+=10);
}

void UI::LCDDarker(void* ptrUI)
{
	UI* me = (UI*)ptrUI;
	analogWrite(LCD_BKL, me->_lcd_brightness-=10);
}
// Private methods

void UI::UpdateMenu()
{
	Serial.println("Updating menu");
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(menu.getCurrent()->getDisplayText());
}

bool UI::CheckButtonPressed()
{
	int val_read = analogRead(BUT_PIN);

	// Avoid flipping in single read
	if ( abs(_last_button_read - val_read) > BUT_THRESH)
	{
		_last_button_read = val_read;
		_button_pressed = BUT_NONE;
		return false;
	}

	if( val_read > (BUT0_VAL - BUT_THRESH) && val_read < (BUT0_VAL + BUT_THRESH) )
	{
		_button_pressed = BUT_LT;
	}
	else if( val_read > (BUT1_VAL - BUT_THRESH) && val_read < (BUT1_VAL + BUT_THRESH) )
	{
		_button_pressed = BUT_UP;
	}
	else if( val_read > (BUT2_VAL - BUT_THRESH) && val_read < (BUT2_VAL + BUT_THRESH) )
	{
		_button_pressed = BUT_DN;
	}
	else if( val_read > (BUT3_VAL - BUT_THRESH) && val_read < (BUT3_VAL + BUT_THRESH) )
	{
		_button_pressed = BUT_RT;
	}
	else
	{
		_button_pressed = BUT_NONE;
	}
	return true;
}
