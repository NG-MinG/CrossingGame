#include "Graphics.h"
#include "Console.h"

Graphics::Graphics() {
	// Graphics::DrawGraphics(GetStdHandle(STD_OUTPUT_HANDLE), "menu.txt", COORD{ 28, 7 }, (int)Color::lightyellow);
}

void Graphics::SetColor(HANDLE hwnd, int color)
{
	SetConsoleTextAttribute(hwnd, color);
}

void Graphics::DrawGraphics(HANDLE hwnd, const std::string filename, COORD pos, int color)
{
	std::string str;
	std::ifstream inp(filename);
	SetColor(hwnd, color);
	while (!inp.eof())
	{
		std::getline(inp, str);
		GotoXY(hwnd, pos);
		std::cout << str;
		pos.Y++;
	}
	inp.close();
}

void Graphics::GotoXY(HANDLE hwnd, COORD pos)
{
	SetConsoleCursorPosition(hwnd, pos);
}

void Graphics::DrawTexts(HANDLE hwnd, std::string str, COORD pos, int color)
{
	GotoXY(hwnd, pos);
	SetConsoleTextAttribute(hwnd, color);
	std::cout << str;
}
