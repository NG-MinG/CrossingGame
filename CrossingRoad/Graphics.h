#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>

const enum class Color
{
	black,
	blue,
	green,
	aqua,
	red,
	purple,
	yellow,
	white,
	gray,
	lightblue,
	lightgreen,
	lightaqua,
	lightred,
	lightpurple,
	lightyellow,
	brightwhite
};

class Graphics
{
public:
	static void DrawTexts(const std::wstring& text, const COORD& pos, const Color& color);
	static void DrawTexts(const std::wstring& text, const COORD& pos);
	static void DrawTexts(const std::wstring& text, const Color& color);
	static void DrawTexts(const std::wstring& text);

	static void DrawTexts(const std::string& text, const COORD& pos, const Color& color);
	static void DrawTexts(const std::string& text, const COORD& pos);
	static void DrawTexts(const std::string& text, const Color& color);
	static void DrawTexts(const std::string& text);

	static void RemoveArea(const COORD& s_pos, const COORD& e_pos);
	static std::vector<std::string> GetGraphics(const std::string& filename);
	static std::vector<std::string> GetGraphicsR(const std::string& filename);
	static void DrawGraphics(COORD pos, const std::string& filename, const Color& color);
	static void DrawGraphicsR(COORD pos, const std::string& filename, const Color& color);
	static Color GetColor(const Color& background, const Color& text);
};