#pragma once
class ButtonManager
{
public:
	ButtonManager(void);
	~ButtonManager(void);

	static void init();
	static void update(bool* buttonState);

	static bool isButtonHeld(int index);
	static bool isButtonReleased(int index);
	static bool isButtonPressed(int index);

private:
	static bool* buttonsPressed;
	static bool* buttonsReleased;
	static bool* buttonsHeld;
	static bool* oldButtonState;

	static const int NUM_BUTTONS = 3;
};

