#include "Button.h"
#include"Console.h"
#include "Graphics.h"

Button::Button(std::string s, COORD p, Color c)
{
	title = s;
	pos = p;
	color = c;
}
std::string Button::GetContent()
{
	return title;
}
COORD Button::GetPos()
{
	return pos;
}
int Button::GetColor()
{
	return (int)color;
}
void Button::MakeEffect()
{
	for (int i = 0; i < 4; i++)
	{
		Graphics::DrawTexts(GetStdHandle(STD_OUTPUT_HANDLE), title, pos, 15 * (int)Color::white + (int)Color::white);
		Sleep(120);
		Graphics::DrawTexts(GetStdHandle(STD_OUTPUT_HANDLE), title, pos,GetColor());
		Sleep(100);
	}
	Graphics::DrawTexts(GetStdHandle(STD_OUTPUT_HANDLE), title, pos, 15 * (int)Color::white + (int)Color::white);
}