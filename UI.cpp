/*
 * UI.cpp
 *
 *  Created on: 6 Mar 2012
 *      Author: Robin Elvin
 */

#include "UI.h"

UI::UI() : lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7), camera(FOCUS_PIN, SHUTTER_PIN)
//		menu(),
//		manualMove(),
//		axis1(),
//		axis2(),
//		camera(),
//		settings(),
//		scope(),
//		lcdBrightness(),
//		lcdFadeTime()
{
	_last_button_read = 1023;
	_button_pressed = 0;
	runStatus = NotRunning;
	externalInterval = ExternalNone;
	idle_time = millis();

	pinMode(LCD_BKL, OUTPUT);
}

void UI::InitUserInterface()
{

	_last_button_pressed = BUT_NONE;
	lcdBrightness = MenuItem();
	lcdBrightness.setText("LCD Brightness");
	lcdBrightness.addLeftCallback((void *)this, UI::LCDDarker);
	lcdBrightness.addRightCallback((void *)this, UI::LCDBrighter);
	lcdBrightness.inputType = MenuItem::Integer;
	lcdBrightness.setValue((int)_lcd_brightness);

	lcdFadeTime.setText("Light Fade (ms)");
	lcdFadeTime.addLeftCallback((void *)this, UI::LCDTimeoutDecrease);
	lcdFadeTime.addRightCallback((void *)this, UI::LCDTimeoutIncrease);
	lcdFadeTime.inputType = MenuItem::Integer;
	lcdFadeTime.setValue((int)_lcd_fade_timeout);

	lcdBrightness.addRight(&lcdFadeTime);

	manualMoveItem = MenuItem();
	manualMoveItem.setText("Manual Move");

	axis1Item = MenuItem();
	axis1Item.setText("Axis 1");

	axis2Item = MenuItem();
	axis2Item.setText("Axis 2");

	cameraItem = MenuItem();
	cameraItem.setText("Camera");

	settingsItem = MenuItem();
	settingsItem.setText("Settings");


	//rootItem.addDown(&lcdBrightness);
	menu.SetRoot(&manualMoveItem);
	manualMoveItem.addRight(&axis1Item);
	axis1Item.addRight(&axis2Item);
	axis2Item.addRight(&cameraItem);
	cameraItem.addRight(&settingsItem);

	settingsItem.addDown(&lcdBrightness);

	_lcd_brightness = 100;

    // fade up lcd backlight
	// TODO Fade up to saved level
    for (int d=255; d>_lcd_brightness; d--)
    {
        analogWrite(LCD_BKL, d);
        delay(10);
    }


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
    ShowHomeScreen();
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

		if (_button_pressed != BUT_NONE)
		{
			idle_time = millis();
			analogWrite(LCD_BKL, 0);
		}
	else if (millis() - idle_time > _lcd_fade_timeout)
		{
		    for (int d=0; d<_lcd_brightness; d++)
		    {
		        analogWrite(LCD_BKL, d);
		        delay(10);
		    }
		}
	}
}

void UI::FadeLCD()
{

}

void UI::ShowHomeScreen()
{
	lcd.clear();
	lcd.setCursor(0, 0);
	if ( runStatus & Running )
	{
		if ( externalInterval & (External1 | External2))
		{
			lcd.print("Ext");
		}
		else
		{
			lcd.print("On");
		}
	}
	else
	{
		lcd.print("Off");
	}
	lcd.setCursor(4, 0);
	lcd.print(camera.interval);
	lcd.print("s ");
	if (camera.shots > 999)
	{
		lcd.setCursor(10, 0);
	}
	else if (camera.shots > 99)
	{
		lcd.setCursor(11, 0);
	}
	else if (camera.shots > 9)
	{
		lcd.setCursor(12, 0);
	}
	else
	{
		lcd.setCursor(13, 0);
	}
	lcd.print('[');
	lcd.print(camera.shots);
	lcd.print(']');
}

// Menu callbacks

void UI::LCDBrighter(void* ptrUI)
{
	UI* me = (UI*)ptrUI;
	if (me->_lcd_brightness > 4)
	{
		me->_lcd_brightness-=5;
		analogWrite(LCD_BKL, me->_lcd_brightness);
		me->lcd.setCursor(7, 1);
		me->lcd.print(me->_lcd_brightness);
	}
}

void UI::LCDDarker(void* ptrUI)
{
	UI* me = (UI*)ptrUI;
	if (me->_lcd_brightness < 251)
	{
		me->_lcd_brightness+=5;
		analogWrite(LCD_BKL, me->_lcd_brightness);
		me->lcd.setCursor(7, 1);
		me->lcd.print(me->_lcd_brightness);
	}
}

void UI::LCDTimeoutIncrease(void* ptrUI)
{
	UI* me = (UI*)ptrUI;
	if (me->_lcd_fade_timeout < 30000)
	{
		me->_lcd_fade_timeout+=250;
		me->lcd.setCursor(7, 1);
		me->lcd.print(me->_lcd_fade_timeout);
	}
}

void UI::LCDTimeoutDecrease(void* ptrUI)
{
	UI* me = (UI*)ptrUI;
	if (me->_lcd_fade_timeout > 249)
	{
		me->_lcd_fade_timeout-=250;
		me->lcd.setCursor(7, 1);
		me->lcd.print(me->_lcd_fade_timeout);
	}
}



// Private methods
void UI::PrintValue()
{
	switch (menu.getCurrent()->inputType)
	{
	case MenuItem::Float:
		lcd.setCursor(6, 1);
		lcd.print(menu.getCurrent()->getFloatValue());
		break;
	case MenuItem::Integer:
		lcd.setCursor(6, 1);
		lcd.print(menu.getCurrent()->getIntValue());
		break;
	case MenuItem::OnOff:
		lcd.setCursor(7, 1);
		if (menu.getCurrent()->getBoolValue())
		{
			lcd.print("On ");
		}
		else
		{
			lcd.print("Off");
		}
		break;
	case MenuItem::Nothing:
		break;
	}
}


void UI::UpdateMenu()
{
	Serial.println("Updating menu");
	lcd.clear();
	if (menu.getCurrent()->valueEntry)
	{
		lcd.setCursor(0, 1);
		lcd.print('<');
		lcd.setCursor(15, 1);
		lcd.print('>');
		PrintValue();
	}
	else
	{
		if (menu.getCurrent()->_leftItem)
		{
			lcd.setCursor(0, 0);
			lcd.print('<');
		}

		if (menu.getCurrent()->_rightItem)
		{
			lcd.setCursor(15, 0);
			lcd.print('>');
		}
	}
	lcd.setCursor(1, 0);
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
