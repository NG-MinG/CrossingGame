#include "GDino.h"

GDino::GDino(const Color& c, const std::string& app, const short& w, const short& h, const short& st, const COORD& p, const RECT& gb)
	: Animal()
{
	color		= c;
	appearance	= app;
	width		= w;
	height		= h;
	state		= st;
	pos			= p;
	GameBoard	= gb;
}

void GDino::Draw(const short& start, const short& end)
{
	if (pos.X > GameBoard.left + 2)
		Console::GotoXY(g_handle, pos);
	else
		Console::GotoXY(g_handle, { short(GameBoard.left + 2), pos.Y });

	for (int cnt = 0, y = 0, i = 0; i < appearance.size(); ++i)
	{
		++cnt;
		if (cnt == width)
		{
			++y;
			cnt = 0;
			if (pos.X > GameBoard.left + 2)
				Console::GotoXY(g_handle, { pos.X, short(pos.Y + y) });
			else
				Console::GotoXY(g_handle, { short(GameBoard.left + 2), short(pos.Y + y) });
			continue;
		}

		if (pos.X > GameBoard.left + 2)
		{
			if (pos.X + width > GameBoard.right)
			{
				if (cnt < end)
					std::cout << appearance[i];
			}
			else std::cout << appearance[i];
		}
		else
		{
			if (pos.X + width > GameBoard.left + 2 && cnt > start)
				std::cout << appearance[i];
		}
	}
}

void GDino::Draw()
{
	static const std::string filename = appearance;
	switch (state)
	{
	case 1:
		if (filename == appearance) appearance = Graphics::GetGraphics(filename);

		Graphics::SetColor(g_handle, color);
		Draw((GameBoard.left - pos.X + 2), width - (pos.X + width - GameBoard.right));

		break;
	case 2:
		if (filename == appearance) appearance = Graphics::GetGraphicsR(filename);

		Graphics::SetColor(g_handle, color);
		Draw((GameBoard.left - pos.X + 2), width - (pos.X + width - GameBoard.right));

		break;
	}
}

void GDino::MovingLeft()
{
	static const COORD p_run = pos;

	if (pos.X > GameBoard.left + 1 && pos.X < GameBoard.right - 1)
		Graphics::RemoveArea(g_handle, pos, { short(pos.X), short(pos.Y + height - 1) });

	pos.X++;
	Draw();

	if (pos.X > GameBoard.right - 1)
	{
		pos = p_run;
		StopMoving();
	}
}

void GDino::MovingRight()
{
	static const COORD p_run = pos;

	if (pos.X > GameBoard.left - width + 4 && pos.X < GameBoard.right - width)
		Graphics::RemoveArea(g_handle, { short(pos.X + width - 3), pos.Y }, { short(pos.X + width - 1), short(pos.Y + height - 1) });

	if (pos.X < GameBoard.right - width + 1)
		Graphics::RemoveArea(g_handle, { short(pos.X + width - 2), pos.Y }, { short(pos.X + width - 2), short(pos.Y + height - 1) });

	pos.X--;
	Draw();

	if (pos.X < GameBoard.left - width + 4)
	{
		Graphics::RemoveArea(g_handle, { short(pos.X + width - 1), pos.Y }, { short(pos.X + width), short(pos.Y + height - 1) });
		pos = p_run;
		StopMoving();
	}
}

void GDino::Moving()
{
	switch (state)
	{
	case 1:
		MovingLeft();
		break;
	case 2:
		MovingRight();
		break;
	}
}

void GDino::Tell()
{
}
