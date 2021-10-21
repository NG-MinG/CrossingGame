#include "Button.h"

Button::Button(string filename, COORD p, Color c)
{
	content = filename;
	pos = p;
	color = c;
}
std::string Button::GetContent()
{
	return content;
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
	for (int i = 0; i <= 4; i++)
	{
		Grahphics::DrawTexts(o_Handle, content, pos, mamau);
		Sleep(120);
		Grahphics::DrawTexts(o_Handle, content, pos, GetColor());
		Sleep(100);
	}
	Grahphics::DrawTexts(o_Handle, content, pos, mamau);
}