// Do not remove the include below
#include "Timelapse.h"

//The setup function is called once at startup of the sketch
void setup()
{
	ui = UI();
	Serial.begin(9600);
	// Set up on-board LED for diagnostic output
	pinMode(LED_BUILTIN, OUTPUT);
	ui.InitUserInterface();
}

// The loop function is called in an endless loop
void loop()
{
	//Add your repeated code here
	//delay(1000);
	ui.CheckUI();
}
