#include <iostream>
#include <string>
#include <Windows.h>

#pragma comment(lib, "winmm.lib")

class Console
{
public:
	Console();
	void FixSingle();
	void SetSize(int, int);
	void SetCursor(bool);
	void SetQuickEdit(bool);
	void CharSet();
	void GetSize();
	// void SetConsoleColor(Color);
	void SetTitle(const wchar_t* title);
	void SetBufferSize();

	static short KeyPress(int key);

	static void PlayMusic(const wchar_t*);
	static HANDLE Get_OUTPUT_Handle();
	static HANDLE Get_INPUT_Handle();
	static HWND Get_CONSOLE_Handle();
	
private:
	HANDLE oHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE iHandle = GetStdHandle(STD_INPUT_HANDLE);
	HWND consoleHandle = GetConsoleWindow();
};

