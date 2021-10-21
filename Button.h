#pragma once
#include "Graphics.h"
#include"Console.h"
class Button
{
private:
	Color	color;
	COORD	pos;
	string	content;
	int		mamau = (15 * (int)Color::white + (int)Color::white);
	HANDLE	o_Handle = GetStdHandle(STD_OUTPUT_HANDLE);
public:
	Button(string, COORD, Color);
	string GetContent();
	COORD GetPos();
	int GetColor();
	void MakeEffect();
};