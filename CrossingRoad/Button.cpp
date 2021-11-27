#include "Button.h"

void Button::Initialize()
{
	b_text = "\0";
	b_pos = { 0, 0 };
	b_color = Color::white;
}

Button::Button()
{
	Initialize();
}

Button::Button(const std::string& text)
{
	Initialize();
	b_text = text;
}

Button::Button(const std::string& text, const COORD& pos)
{
	Initialize();

	b_text = text;
	b_pos = pos;
}

Button::Button(const std::string& text, const COORD& pos, const Color& color)
{
	Initialize();

	b_text = text;
	b_pos = pos;
	b_color = color;
}

void Button::Draw()
{
	Graphics::DrawTexts(b_text, b_pos, b_color);
}

void Button::Draw(const Color& color)
{
	Graphics::DrawTexts(b_text, b_pos, color);
}

void Button::DrawEffect(const Color& color)
{
	for (int i = 0; i < 4; ++i)
	{
		Draw();
		Sleep(140);
		Draw(color);
		Sleep(100);
	}
	Draw(color);
}

void Button::SetText(const std::string& text)
{
	b_text = text;
}

void Button::SetColor(const Color& color)
{
	b_color = color;
}