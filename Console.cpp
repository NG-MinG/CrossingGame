#include "Console.h"

Console::Console(int w, int h, const wchar_t* title, bool flag, Color color)
{
	SetSize(w, h);
	FixSingle();
	SetCursion(flag);
	SetQuickEdit(flag);
	CharSet();
	SetBufferSize();
	SetConsoleTitleW(title);
}

void Console::FixSingle()
{
	LONG style = GetWindowLongW(consoleHandle, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLongW(consoleHandle, GWL_STYLE, style);
}

void Console::SetCursion(bool flag)
{
	CONSOLE_CURSOR_INFO info;
	info.bVisible = flag;
	info.dwSize = 25;

	::SetConsoleCursorInfo(oHandle, &info);
}


void Console::SetSize(int w, int h)
{
	RECT r;

	::GetWindowRect(consoleHandle, &r);
	::MoveWindow(consoleHandle, r.left, r.top, w, h, true);
}

void Console::SetQuickEdit(bool f)
{
	DWORD prev_mode;

	GetConsoleMode(iHandle, &prev_mode);
	SetConsoleMode(iHandle, (!f) ? (ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE)) : prev_mode);
}

void Console::CharSet()
{
	SetConsoleOutputCP(CP_UTF8);
}

void Console::PlayMusic(const wchar_t* filename)
{
	PlaySound(filename, NULL, SND_FILENAME | SND_ASYNC);
}

void Console::GetSize()
{
	CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;

	::GetConsoleScreenBufferInfo(oHandle, &scrBufferInfo);
	cerr << "Screen Buffer Size : " << scrBufferInfo.dwSize.X << " x " << scrBufferInfo.dwSize.Y << std::endl;
}

void Console::SetBufferSize()
{
	CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;

	::GetConsoleScreenBufferInfo(oHandle, &scrBufferInfo);
	short winWidth = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
	short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;

	short scrBufferWidth = scrBufferInfo.dwSize.X;
	short scrBufferHeight = scrBufferInfo.dwSize.Y;

	COORD newSize{ scrBufferWidth, winHeight };

	int Status = SetConsoleScreenBufferSize(oHandle, newSize);
	if (Status == 0)
	{
		std::cerr << "SetConsoleScreenBufferSize() failed! Reason : " << GetLastError() << std::endl;
		exit(Status);
	}
}

void Console::SetConsoleColor(Color color)
{
	CONSOLE_SCREEN_BUFFER_INFOEX cbi;
	cbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	::GetConsoleScreenBufferInfoEx(oHandle, &cbi);
	cbi.wAttributes = (WORD)color;
	::SetConsoleScreenBufferInfoEx(oHandle, &cbi);
}

short Console::KeyPress(int key)
{
	return GetAsyncKeyState(key) & 0x01; // keypress nhấn phím
}

HANDLE Console::get_OUTPUT_Handle()
{
	return GetStdHandle(STD_OUTPUT_HANDLE);
}

HANDLE Console::get_INPUT_Handle()
{
	return GetStdHandle(STD_INPUT_HANDLE);
}

HWND Console::get_CONSOLE_Handle()
{
	return GetConsoleWindow();
}