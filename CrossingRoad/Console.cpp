#include "Console.h"

void Console::Initialize()
{
	console_handle		= GetConsoleWindow();
	std_input_handle	= GetStdHandle(STD_INPUT_HANDLE);
	std_output_handle	= GetStdHandle(STD_OUTPUT_HANDLE);
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

void Console::SetColor(const Color& color)
{
	::SetConsoleTextAttribute(outputHandle(), WORD(color));
}

void Console::SetSize(const short& width, const short& height)
{
	RECT r;
	::GetWindowRect(console_handle, &r);
	::MoveWindow(console_handle, r.left, r.top, width, height, true);
}

void Console::FixSingle()
{
	LONG style = GetWindowLongW(console_handle, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME) & ~(WS_MINIMIZEBOX) & ~(WS_MINIMIZE);

	::SetWindowLongW(console_handle, GWL_STYLE, style);
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

void Console::SetCursor(const bool& flag)
{
	const CONSOLE_CURSOR_INFO info{ 25, flag };
	::SetConsoleCursorInfo(std_output_handle, &info);
}

void Console::Clear(const Color& color)
{
	SetColor(color);
	system("cls");
}

void Console::QuickEdit(bool flag)
{
	DWORD prev_mode;
	GetConsoleMode(std_input_handle, &prev_mode);
	SetConsoleMode(std_input_handle, (!flag) ? (ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE)) : prev_mode);
}

void Console::GotoXY(const COORD& pos)
{
	::SetConsoleCursorPosition(outputHandle(), pos);
}

COORD Console::GetXY()
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	return (GetConsoleScreenBufferInfo(outputHandle(), &cbsi)) ? cbsi.dwCursorPosition : COORD{ 0, 0 };
}

std::string Console::GetChar(const COORD& pos, const short& w, const short& h)
{
	std::string s;
	char a[1];
	DWORD num_read;

	if (h == -1)
	{
		for (short x = 0; x <= w; ++x)
		{
			ReadConsoleOutputCharacterA(outputHandle(), a, DWORD(1), { short(pos.X + x), pos.Y }, LPDWORD(&num_read));
			s.push_back(*a);
		}
	}
	else if (w == -1)
	{
		for (short y = 0; y <= h; ++y)
		{
			ReadConsoleOutputCharacterA(outputHandle(), a, DWORD(1), { pos.X, short(pos.Y + y) }, LPDWORD(&num_read));
			s.push_back(*a);
		}
	}
	
	return s;
}

SHORT Console::KeyPress(const KeyCode& key)
{
	return SHORT(GetAsyncKeyState(int(key)) & 1 && GetKeyState(int(key)) >> 15);
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

void Console::OpenMusic(const wchar_t* filename)
{
	std::wstring cmd = L"open \"" + std::wstring(filename) + L"\" type mpegvideo alias mp3";
	::mciSendStringW(cmd.c_str(), NULL, 0, NULL);
}

void Console::PlayMusic(const int& volume, bool repeat)
{
	SetVolume(volume);
	if (repeat) ::mciSendStringW(L"play mp3 from 0 repeat", NULL, 0, NULL);
	else ::mciSendStringW(L"play mp3 from 0", NULL, 0, NULL);
}

void Console::PlayMusicAsync(const wchar_t* filename)
{
	PlaySoundW(filename, NULL, SND_FILENAME | SND_ASYNC);
}

void Console::SetVolume(const int& volume)
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

short random(short start, short end)
{
	if (end < start) std::swap(start, end);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(start, end);

	return dis(gen);
}
