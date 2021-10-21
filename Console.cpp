#include "Console.h"

Console::Console(int w,int h,const wchar_t*str,bool f, Color color)
{
	SetSize(w, h);
	FixSingle();
	SetTitle(str);
	SetCursor(f);
	SetQuickEdit(f);
	CharSet();
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

	::SetConsoleCursorInfo(ohandle, &info);
}

void Console:: SetTitle(const wchar_t* title)
{
	SetConsoleTitleW(title);
}

void Console::SetSize(int w, int h)
{
	RECT r;
	::GetWindowRect(consoleHandle, &r);
	::MoveWindow(GetConsoleWindow(), r.left, r.top, w, h, true);
}

void Console::SetQuickEdit(bool f)
{
	DWORD prev_mode;
	GetConsoleMode(ihandle, &prev_mode);
	SetConsoleMode(ihandle, (!f) ? (ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE)) : prev_mode);
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
	::GetConsoleScreenBufferInfo(ohandle, &scrBufferInfo);
}
void Console::SetBufferSize()
{
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
		std::cerr << "SetConsoleScreenBufferSize() failed! Reason : " << GetLastError() << std::endl;
		exit(Status);
	}
}
HANDLE Get_OUTPUT_Handle()
{
	return GetStdHandle(STD_OUTPUT_HANDLE);
}
HANDLE Get_INPUT_Handle()
{
	return GetStdHandle(STD_INPUT_HANDLE);
}
HWND Get_CONSOLE_Handle()
{
	return GetConsoleWindow();
}
