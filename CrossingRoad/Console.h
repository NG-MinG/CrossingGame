#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include "Graphics.h"

#pragma execution_character_set("utf-8")
#pragma comment(lib, "winmm.lib")

const enum class KeyCode
{
	A = 0x41,
	B = 0x42,
	C = 0x43,
	D = 0x44,
	E = 0x45,
	F = 0x46,
	G = 0x47,
	H = 0x48,
	I = 0x49,
	J = 0x4A,
	K = 0x4B,
	L = 0x4C,
	M = 0x4D,
	N = 0x4E,
	O = 0x4F,
	P = 0x50,
	Q = 0x51,
	R = 0x52,
	S = 0x53,
	T = 0x54,
	U = 0x55,
	V = 0x56,
	W = 0x57,
	X = 0x58,
	Y = 0x59,
	Z = 0x5A
};

short random(short start, short end);

class Console
{
private:
	HWND console_handle;
	HANDLE std_input_handle;
	HANDLE std_output_handle;

	void Initialize();

public:
	Console(const short& width, const short& height, const std::wstring& title, const bool& cursor, const Color& color);
	Console();

	static void SetColor(const Color& color);
	void SetSize(const short& width, const short& height);

	void FixSingle();
	void DisableScrollbar();

	void SetCursor(const bool& flag);
	void QuickEdit(bool flag);

	void Clear(const Color& color);
	static void GotoXY(const COORD& pos);
	static COORD GetXY();
	static std::string GetChar(const COORD& pos, const short& w, const short& h);
	static SHORT KeyPress(const KeyCode& key);

	static void OpenMusic(const wchar_t* filename);
	static void SetVolume(const int& volume);
	static void PlayMusic(const int& volume, bool repeat = true);
	static void PlayMusicAsync(const wchar_t* filename);
	static void PauseMusic();
	static void StopMusic();
	static void CloseMusic();

	static HWND consoleHandle();
	static HANDLE inputHandle();
	static HANDLE outputHandle();
};