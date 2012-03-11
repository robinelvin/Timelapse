// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef Timelapse_H_
#define Timelapse_H_
#include "Arduino.h"
//add your includes for the project Timelapse here
#include <HardwareSerial.h>

#include "UI.h"

//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif


// motor PWM
#define MOTOR0_P 5
#define MOTOR1_P 6
#define MOTOR0_DIR 15
#define MOTOR1_DIR 16

 // camera pins
#define CAMERA_PIN 13
#define FOCUS_PIN 12

#define MAX_MOTORS 2


//add your function definitions for the project Timelapse here
UI ui;



//Do not add code below this line
#endif /* Timelapse_H_ */
