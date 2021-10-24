#pragma once
#include "Graphics.h"
class Button
{
private:
	Color color;
	COORD pos;
	std::string title;
public:
	Button(std::string, COORD, Color);
	std::string GetContent();
	COORD GetPos();
	int GetColor();
	void MakeEffect();
	void Draw();
	void Draw(Color);
};