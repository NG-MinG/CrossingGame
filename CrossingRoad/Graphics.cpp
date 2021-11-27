#include "Graphics.h"
#include "Console.h"

void Graphics::DrawTexts(const std::wstring& str, const COORD& point, const Color& color)
{
	Console::SetColor(color);
	Console::GotoXY(point);
	std::wcerr << str;
}

void Graphics::DrawTexts(const std::wstring& str, const COORD& point)
{
	Console::GotoXY(point);
	std::wcerr << str;
}

void Graphics::DrawTexts(const std::wstring& str, const Color& color)
{
	Console::SetColor(color);
	std::wcerr << str;
}

void Graphics::DrawTexts(const std::wstring& str)
{
	std::wcerr << str;
}

void Graphics::DrawTexts(const std::string& str, const COORD& point, const Color& color)
{
	Console::SetColor(color);
	Console::GotoXY(point);
	std::cerr << str;
}

void Graphics::DrawTexts(const std::string& str, const COORD& point)
{
	Console::GotoXY(point);
	std::cerr << str;
}

void Graphics::DrawTexts(const std::string& str, const Color& color)
{
	Console::SetColor(color);
	std::cerr << str;
}

void Graphics::DrawTexts(const std::string& str)
{
	std::cerr << str;
}

void Graphics::RemoveArea(const COORD& s_point, const COORD& e_point)
{
	for (SHORT x = s_point.X; x <= e_point.X; ++x)
	{
		for (SHORT y = s_point.Y; y <= e_point.Y; ++y)
		{
			Console::GotoXY({ x, y });
			std::cerr << " ";
		}
		std::cerr << "\n";
	}
}

std::vector<std::string> Graphics::GetGraphics(const std::string& filename)
{
	std::vector<std::string> omatrix;
	std::ifstream inp(filename);
	std::string str;
	while (std::getline(inp, str))
		omatrix.push_back(str);
	inp.close();

	return omatrix;
}

std::vector<std::string> Graphics::GetGraphicsR(const std::string& filename)
{
	std::vector<std::string> omatrix;

	std::ifstream inp(filename);
	std::string str;
	while (std::getline(inp, str))
	{
		std::reverse(str.begin(), str.end());
		for (unsigned int i = 0; i < str.size(); ++i)
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
		omatrix.push_back(str);
	}
	inp.close();

	return omatrix;
}

void Graphics::DrawGraphics(COORD pos, const std::string& filename, const Color& color)
{

	Console::SetColor(color);

	std::ifstream inp(filename);

	std::string str;
	while (std::getline(inp, str))
	{
		Console::GotoXY(pos);
		std::cerr << str;
		pos.Y++;
	}
	inp.close();
}

void Graphics::DrawGraphicsR(COORD pos, const std::string& filename, const Color& color)
{
	Console::SetColor(color);

	std::ifstream inp(filename);

	std::string str;
	while (std::getline(inp, str))
	{
		std::reverse(str.begin(), str.end());
		Console::GotoXY(pos);
		for (unsigned int i = 0; i < str.size(); ++i)
		{
			if (str[i] == '(') std::cerr << ")";
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

Color Graphics::GetColor(const Color& background, const Color& text)
{
	return Color(15 * int(background) + int(background) + int(text));
}