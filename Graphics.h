#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

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
	static void SetColor(HANDLE, int);
	static void GotoXY(HANDLE, COORD);
	static void DrawTexts(HANDLE, std::string, COORD, int);
	static void DrawGraphics(HANDLE, std::string, COORD, int);
	static void CleanArea(HANDLE, COORD, COORD);
	static SHORT Checkey(int);

private:

};