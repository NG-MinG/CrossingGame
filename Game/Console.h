#pragma once
#include <iostream>
#include <Windows.h>
#include "Graphics.h"
#include <string>
#pragma comment(lib, "winmm.lib")

class Console
{
public:
	Console(int, int, const wchar_t*, bool,Color);
	void FixSingle();
	void SetSize(int, int);
	void SetCursor(bool);
	void SetQuickEdit(bool);
	void CharSet();
	void GetSize();
	void SetTitle(const wchar_t*);
	void SetBufferSize();
	static void PlayMusic(const wchar_t*);
	static HANDLE Get_OUTPUT_Handle();
	static HANDLE Get_INTPUT_Handle();
	static HWND Get_CONSOLE_Handle();

	void OpenMusic(std::wstring filename);
	void PlayMusic();
	void PauseMusic();
	void StopMusic();
	void CloseMusic();
	void SetVoLume(int);

private:
	HANDLE ohandle = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE ihandle = GetStdHandle(STD_INPUT_HANDLE);
	HWND consoleHandle = GetConsoleWindow();
};