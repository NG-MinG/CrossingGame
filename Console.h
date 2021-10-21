#pragma once
#include "Graphics.h"

#pragma comment(lib, "winmm.lib")

using namespace std;

class Console
{
public:
	Console(int, int, const wchar_t*, bool, Color);
	void FixSingle();
	void SetCursion(bool);
	void SetSize(int, int);
	void SetQuickEdit(bool);
	void CharSet();
	void GetSize();
	void SetBufferSize();
	void SetConsoleColor(Color);

	static HANDLE get_OUTPUT_Handle();
	static HANDLE get_INPUT_Handle();
	static HWND get_CONSOLE_Handle();
	static void PlayMusic(const wchar_t*);
	static short KeyPress(int);

private:
	HANDLE oHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE iHandle = GetStdHandle(STD_INPUT_HANDLE);
	HWND consoleHandle = GetConsoleWindow();
};