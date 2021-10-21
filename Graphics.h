#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#pragma execution_character_set("utf-8")

using namespace std;

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

class Grahphics
{
public:
	static void SetColor(HANDLE, int);
	static void GotoXY(HANDLE, COORD);
	static void DrawTexts(HANDLE, string, COORD, int);
	static void DrawGraphics(HANDLE, const string, COORD, int);
	static SHORT KeyPress(int);
private:

};