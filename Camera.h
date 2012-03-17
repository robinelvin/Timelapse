/*
 * Camera.h
 *
 *  Created on: 17 Mar 2012
 *      Author: Robin
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "Arduino.h"
#include "MsTimer2.h"

class Camera {
public:
	Camera(int focus_pin, int shutter_pin);

	void focus();
	void fire();
	void reset();
	static void stop(void * instance);

	// Shots fired
	int shots;
	float interval;
	unsigned long exposure_time;
	unsigned int focus_hold_time;
	unsigned int post_exposure_delay;
	// Whether to focus at same time as firing shutter
	bool focus_with_shutter;

private:
	int _focus_pin;
	int _shutter_pin;
};

#endif /* CAMERA_H_ */
