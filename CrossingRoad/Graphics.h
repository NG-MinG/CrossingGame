#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

#pragma execution_character_set("utf-8")

enum class Color
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
	static void SetColor(const HANDLE& hwnd, const Color& color);

	static void DrawTexts(const HANDLE& hwnd, const std::wstring& text, const COORD&  pos, const Color& color);
	static void DrawTexts(const HANDLE& hwnd, const std::wstring& text, const COORD& pos);
	static void DrawTexts(const HANDLE& hwnd, const std::wstring& text, const Color& color);
	static void DrawTexts(const HANDLE& hwnd, const std::wstring& text);

	static void DrawTexts(const HANDLE& hwnd, const std::string& text, const COORD& pos, const Color& color);
	static void DrawTexts(const HANDLE& hwnd, const std::string& text, const COORD& pos);
	static void DrawTexts(const HANDLE& hwnd, const std::string& text, const Color& color);
	static void DrawTexts(const HANDLE& hwnd, const std::string& text);

	static void RemoveArea(const HANDLE& hwnd, const COORD& s_pos, const COORD& e_pos);
	static std::string GetGraphics(const std::string& filename);
	static std::string GetGraphicsR(const std::string& filename);
	static void DrawGraphics(const HANDLE& hwnd, COORD pos, const std::string& filename, const Color& color);
	static void DrawGraphicsR(const HANDLE& hwnd, COORD pos, const std::string& filename, const Color& color);
	static Color bg_GetColor(const Color& background, const Color& text);
};