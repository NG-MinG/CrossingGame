#include "Graphics.h"

void Grahphics::SetColor(HANDLE Handle, int color)
{
	SetConsoleTextAttribute(Handle, color);
}

void Grahphics::GotoXY(HANDLE Handle, COORD pos)
{
	SetConsoleCursorPosition(Handle, pos);
}

void Grahphics::DrawTexts(HANDLE Handle, string str, COORD pos, int color)
{
	GotoXY(Handle, pos);
	SetColor(Handle, color);
	cout << str;
}

void Grahphics::DrawGraphics(HANDLE Handle, const string filename, COORD pos, int color)
{
	string str;
	ifstream infile(filename);
	if (!infile.is_open())
	{
		cout << "Openning file fail!" << endl;
		return;
	}
	else
	{
		SetColor(Handle, color);
		while (!infile.eof())
		{
			getline(infile, str);
			GotoXY(Handle, pos);
			cout << str;
			pos.Y++;
		}
	}
	infile.close();
}

SHORT Grahphics::KeyPress(int key)
{
	return GetAsyncKeyState(key) & 0x01; // keypress nhấn phím
}
