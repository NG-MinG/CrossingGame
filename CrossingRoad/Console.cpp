#include "Console.h"

void Console::Initialize()
{
	console_handle		= GetConsoleWindow();
	std_input_handle	= GetStdHandle(STD_INPUT_HANDLE);
	std_output_handle	= GetStdHandle(STD_OUTPUT_HANDLE);
}

void Console::QuickEdit(bool flag)
{
	DWORD prev_mode;
	GetConsoleMode(std_input_handle, &prev_mode);
	SetConsoleMode(std_input_handle, (!flag) ? (ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE)) : prev_mode);
}

void Console::GotoXY(HANDLE hwnd, COORD pos)
{
	::SetConsoleCursorPosition(hwnd, pos);
}

SHORT Console::KeyPress(int key)
{
	return SHORT(GetAsyncKeyState(key) & 1 && GetKeyState(key) & 0x8000);
}

void Console::OpenMusic(const wchar_t* filename)
{
	std::wstring cmd = L"open \"" + std::wstring(filename) + L"\" type mpegvideo alias mp3";
	::mciSendStringW(cmd.c_str(), NULL, 0, NULL);
}

void Console::PlayMusic( int volume)
{
	SetVolume(volume);
	::mciSendStringW(L"play mp3 from 0 repeat", NULL, 0, NULL);
}

void Console::SetVolume(int volume)
{
	std::wstring cmd = L"setaudio mp3 volume to " + std::to_wstring(volume);
	::mciSendStringW(cmd.c_str(), NULL, 0, NULL);
}

void Console::PauseMusic()
{
	::mciSendStringW(L"pause mp3", NULL, 0, NULL);
}

void Console::StopMusic()
{
	::mciSendStringW(L"stop mp3", NULL, 0, NULL);
}

void Console::CloseMusic()
{
	::mciSendStringW(L"close mp3", NULL, 0, NULL);
}

void Console::SetSize(short width, short height)
{
	RECT r;
	::GetWindowRect(console_handle, &r);
	::MoveWindow(console_handle, r.left, r.top, width, height, true);
}

void Console::DisableScrollbar()
{
	CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
	::GetConsoleScreenBufferInfo(std_output_handle, &scrBufferInfo);

	short winWidth = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
	short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;

	short scrBufferWidth = scrBufferInfo.dwSize.X;
	short scrBufferHeight = scrBufferInfo.dwSize.Y;

	COORD newSize{ scrBufferWidth, winHeight };

	::SetConsoleScreenBufferSize(std_output_handle, newSize);
}

void Console::FixSingle()
{
	LONG style = GetWindowLongW(console_handle, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);

	SetWindowLongW(console_handle, GWL_STYLE, style);
}

void Console::SetColor(Color attribs)
{
	CONSOLE_SCREEN_BUFFER_INFOEX cbi;

	cbi.cbSize	= sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	::GetConsoleScreenBufferInfoEx(std_output_handle, &cbi);
	
	cbi.wAttributes = WORD(attribs);
	::SetConsoleScreenBufferInfoEx(std_output_handle, &cbi);
}

void Console::SetCursor(bool m)
{
	const CONSOLE_CURSOR_INFO info { 25, m };
	::SetConsoleCursorInfo(std_output_handle, &info);
}

void Console::Clear(const Color& color)
{
	Graphics::SetColor(std_output_handle, color);
	system("cls");
}

HWND Console::consoleHandle()
{
	return GetConsoleWindow();
}

HANDLE Console::inputHandle()
{
	return GetStdHandle(STD_INPUT_HANDLE);
}

HANDLE Console::outputHandle()
{
	return GetStdHandle(STD_OUTPUT_HANDLE);
}

Console::Console(const short& width, const short& height, const std::wstring& title, const bool& cursor, const Color& color)
{
	Initialize();

	SetColor(color);
	SetConsoleOutputCP(CP_UTF8);
	
	SetSize(width, height);
	SetConsoleTitleW(title.c_str());

	FixSingle();
	DisableScrollbar();
	
	QuickEdit(cursor);
	SetCursor(cursor);
}

Console::Console()
{
	Initialize();
}