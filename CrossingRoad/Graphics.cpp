#include "Graphics.h"
#include "Console.h"

void Graphics::SetColor(const HANDLE& hwnd, const Color& color)
{
	::SetConsoleTextAttribute(hwnd, (WORD)color);
}

void Graphics::DrawTexts(const HANDLE& hwnd, const std::wstring& str, const COORD& point, const Color& color)
{
	SetColor(hwnd, color);
	Console::GotoXY(hwnd, point);
	std::wcerr << str;
}

void Graphics::DrawTexts(const HANDLE& hwnd, const std::wstring& str, const COORD& point)
{
	Console::GotoXY(hwnd, point);
	std::wcerr << str;
}

void Graphics::DrawTexts(const HANDLE& hwnd, const std::wstring& str, const Color& color)
{
	SetColor(hwnd, color);
	std::wcerr << str;
}

void Graphics::DrawTexts(const HANDLE& hwnd, const std::wstring& str)
{
	std::wcerr << str;
}

void Graphics::DrawTexts(const HANDLE& hwnd, const std::string& str, const COORD& point, const Color& color)
{
	SetColor(hwnd, color);
	Console::GotoXY(hwnd, point);
	std::cerr << str;
}

void Graphics::DrawTexts(const HANDLE& hwnd, const std::string& str, const COORD& point)
{
	Console::GotoXY(hwnd, point);
	std::cerr << str;
}

void Graphics::DrawTexts(const HANDLE& hwnd, const std::string& str, const Color& color)
{
	SetColor(hwnd, color);
	std::cerr << str;
}

void Graphics::DrawTexts(const HANDLE& hwnd, const std::string& str)
{
	std::cerr << str;
}

void Graphics::RemoveArea(const HANDLE& hwnd, const COORD& s_point, const COORD& e_point)
{
	for (SHORT x = s_point.X; x <= e_point.X; ++x)
	{
		for (SHORT y = s_point.Y; y <= e_point.Y; ++y)
		{
			Console::GotoXY(hwnd, {x, y});
			std::cerr << " ";
		}
		std::cerr << "\n";
	}
}

std::string Graphics::GetGraphics(const std::string& filename)
{
	std::string fstring;

	std::ifstream inp(filename);
	std::string str;
	while (std::getline(inp, str)) fstring += (str + '\n');
	inp.close();

	return fstring;
}

std::string Graphics::GetGraphicsR(const std::string& filename)
{
	std::string fstring;

	std::ifstream inp(filename);
	std::string str;
	while (std::getline(inp, str))
	{
		std::reverse(str.begin(), str.end());
		for (int i = 0; i < str.size(); ++i)
		{
			if (str[i] == '(') str[i] = ')';
			else if (str[i] == ')') str[i] = '(';
			else if (str[i] == ']') str[i] = '[';
			else if (str[i] == '[') str[i] = ']';
			else if (str[i] == '<') str[i] = '>';
			else if (str[i] == '>') str[i] = '<';
			else if (str[i] == '\\') str[i] = '/';
			else if (str[i] == '/') str[i] = '\\';
			else if (str[i] == '{') str[i] = '}';
			else if (str[i] == '}') str[i] = '{';
		}
		fstring += (str + '\n');
	}
	inp.close();

	return fstring;
}

void Graphics::DrawGraphics(const HANDLE& hwnd, COORD pos, const std::string& filename, const Color& color)
{
	Graphics::SetColor(hwnd, color);
	
	std::ifstream inp(filename);
	
	std::string str;
	while (std::getline(inp, str))
	{
		Console::GotoXY(hwnd, pos);
		std::cerr << str;
		pos.Y++;
	}
	inp.close();
}

void Graphics::DrawGraphicsR(const HANDLE& hwnd, COORD pos, const std::string& filename, const Color& color)
{
	Graphics::SetColor(hwnd, color);
	
	std::ifstream inp(filename);
	std::string str;
	while (std::getline(inp, str))
	{
		std::reverse(str.begin(), str.end());
		Console::GotoXY(hwnd, pos);
		for (int i = 0; i < str.size(); ++i)
		{
			if		(str[i] == '(') std::cerr << ")";
			else if (str[i] == ')') std::cerr << "(";
			else if (str[i] == ']') std::cerr << "[";
			else if (str[i] == '[') std::cerr << "]";
			else if (str[i] == '<') std::cerr << ">";
			else if (str[i] == '>') std::cerr << "<";
			else if (str[i] == '\\') std::cerr << "/";
			else if (str[i] == '/') std::cerr << R"(\)";
			else if (str[i] == '{') std::cerr << "}";
			else if (str[i] == '}') std::cerr << "{";
			else std::cerr << str[i];
		}
		pos.Y++;
	}
	inp.close();
}

Color Graphics::bg_GetColor(const Color& background, const Color& text)
{
	return Color(15 * int(background) + int(background) + int(text));
}