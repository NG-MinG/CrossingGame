#pragma once
#include "Graphics.h"

class Button
{
private:
	std::string b_text;
	COORD b_pos;
	Color b_color;
	const HANDLE g_handle = GetStdHandle(STD_OUTPUT_HANDLE);

	void Initialize();
public:
	Button();
	Button(const std::string& text);
	Button(const std::string& text, const COORD& pos);
	Button(const std::string& text, const COORD& pos, const Color& color);

	void Draw();
	void Draw(const Color& color);
	void DrawEffect(const Color& color);
};

