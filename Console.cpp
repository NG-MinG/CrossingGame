#include "Console.h"
#include "Graphics.h"

Console::Console() {
	SetSize(1020, 725);  // 1150, 825
	FixSingle();
	SetQuickEdit(false);
	SetCursor(false);
	CharSet();
	SetTitle(L"CROSSING GAME");
	SetBufferSize();
}

void Console::FixSingle()
{
	HWND handle = GetConsoleWindow();

	LONG style = GetWindowLongW(handle, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLongW(handle, GWL_STYLE, style);
}

void Console::SetCursor(bool m)
{
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 25;
	info.bVisible = m;

	::SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void Console::SetSize(int w, int h)
{
	RECT r;
	::GetWindowRect(GetConsoleWindow(), &r);
	::MoveWindow(GetConsoleWindow(), r.left, r.top, w, h, true);
}

void Console::SetQuickEdit(bool f)
{
	DWORD prev_mode;
	GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &prev_mode);
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), (!f) ? (ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE)) : prev_mode);
}

void Console::CharSet()
{
	SetConsoleOutputCP(CP_UTF8);
}

void Console::PlayMusic(const wchar_t* filename)
{
	PlaySound(filename, NULL, SND_FILENAME | SND_ASYNC);
}


void Console::SetBufferSize()
{
	HANDLE ohandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
	::GetConsoleScreenBufferInfo(ohandle, &scrBufferInfo);
	short winWidth = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
	short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;

	short scrBufferWidth = scrBufferInfo.dwSize.X;
	short scrBufferHeight = scrBufferInfo.dwSize.Y;

	COORD newSize{ scrBufferWidth, winHeight };

	int Status = SetConsoleScreenBufferSize(ohandle, newSize);
	if (Status == 0)
	{
		std::cerr << "\nSetConsoleScreenBufferSize() failed! Reason : " << GetLastError() << std::endl;
		exit(Status);
	}
}

void Console::GetSize()
{
	CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
	::GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &scrBufferInfo);
	std::cerr << "Screen Buffer Size : " << scrBufferInfo.dwSize.X << " x " << scrBufferInfo.dwSize.Y << std::endl;
}

void Console:: SetTitle(const wchar_t* title)
{
	SetConsoleTitleW(title);
}

short Console::KeyPress(int key) {
	return GetAsyncKeyState(key) & 0x01;
}

