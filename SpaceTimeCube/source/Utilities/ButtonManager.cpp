//ButtonManager.cpp
//Keeps track of the state information of the three buttons on the zSpace stylus
//index 0 ---> Oval button
//index 1 --->
//index 2 --->

#include "ButtonManager.h"
#include <ZSpace\Tracker\ITrackerButtonCapability.h>

bool* ButtonManager::buttonsHeld = NULL;
bool* ButtonManager::buttonsPressed = NULL;
bool* ButtonManager::buttonsReleased = NULL;
bool* ButtonManager::oldButtonState = NULL;


ButtonManager::ButtonManager(void)
{
}
//Initializes button state information
void ButtonManager::init(){
	buttonsHeld = new bool[NUM_BUTTONS];
	buttonsPressed = new bool[NUM_BUTTONS];
	buttonsReleased = new bool[NUM_BUTTONS];
	oldButtonState = new bool[NUM_BUTTONS];

	for(int i = 0; i < NUM_BUTTONS; i++) {
		buttonsHeld[i] = false;
		buttonsPressed[i] = false;
		buttonsReleased[i] = false;
		oldButtonState[i] = false;
	}
}

//Update the current button states
void ButtonManager::update(bool* buttonState)
{
	if(buttonState){
		for(int i = 0; i < NUM_BUTTONS; i++){
			//buttons has just been pressed
			if(buttonState[i] && !oldButtonState[i]){
				buttonsPressed[i] = true;
				buttonsReleased[i] = false;
				buttonsHeld[i] = true;
			}
			//button has just been released
			else if(!buttonState[i] && oldButtonState[i]){
				buttonsReleased[i] = true;
				buttonsHeld[i] = false;
				buttonsPressed[i] = false;
			}
			//button is down, but has not just been pressed
			else if(buttonState[i]){
				buttonsHeld[i] = true;
				buttonsPressed[i] = false;
				buttonsReleased[i] = false;
			}
			//Update the previous button state
			oldButtonState[i] = buttonState[i];
		}
	}
}

//Tests if a particular button is currently being held
//Returns false if out-of-range
bool ButtonManager::isButtonHeld(int index)
{
	bool result;
	if(index < 0 || index > NUM_BUTTONS)
		result = false;
	else
		result = buttonsHeld[index];
	return result;
}

//Tests if a button has just been released
//Returns false if out-of-range
bool ButtonManager::isButtonReleased(int index)
{
	bool result;
	if(index < 0 || index > NUM_BUTTONS)
		result = false;
	else
		result = buttonsReleased[index];
	return result;
}

//Test if a button has just been pressed
//Returns false if out-of-range
bool ButtonManager::isButtonPressed(int index)
{
	bool result;
	if(index < 0 || index > NUM_BUTTONS)
		result = false;
	else
		result = buttonsPressed[index];
	return result;
}

//destructor
ButtonManager::~ButtonManager(void)
{
	delete buttonsHeld;
	delete buttonsPressed;
	delete buttonsReleased;
	delete oldButtonState;
}
