/*
 * Camera.cpp
 *
 *  Created on: 17 Mar 2012
 *      Author: Robin
 */

#include "Camera.h"

Camera::Camera(int focus_pin, int shutter_pin)
{
	_focus_pin = focus_pin;
	_shutter_pin = shutter_pin;
	// TODO Read from eeprom
	interval = 1.0;
	exposure_time = 100;
	focus_hold_time = 0;
	focus_with_shutter = 0;
	post_exposure_delay = 100;
}

void Camera::reset()
{
	shots = 0;
}

void Camera::focus()
{

}

void Camera::fire()
{
	// Fire camera shutter
	if ( focus_with_shutter )
	{
		digitalWrite(_focus_pin, HIGH);
	}

	digitalWrite(_shutter_pin, HIGH);
	shots++;
	Serial.print("Firing camera for ");
	Serial.print(exposure_time);
	Serial.print("ms");
	MsTimer2::set(exposure_time, (void *)this, Camera::stop);
	MsTimer2::start();
}

void Camera::stop(void * instance)
{
	Camera* me = (Camera*)instance;
	digitalWrite(me->_shutter_pin, LOW);
	digitalWrite(me->_focus_pin, LOW);
	MsTimer2::stop();
	Serial.print("Camera firing complete");
	// TODO Flag cycle complete
}
