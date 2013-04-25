#pragma once
class ColorRGB
{
public:
	ColorRGB(float red, float green, float blue);
	~ColorRGB(void);

	float ColorRGB::getRed();
	float ColorRGB::getGreen();
	float ColorRGB::getBlue();

private:
	float red;
	float green;
	float blue;
};

