#include "GPeople.h"

GPeople::GPeople()
{
	Initialize();
}

GPeople::GPeople(const Color& c, const std::string& app, const short& w, const short& h, const COORD& p, const RECT& gb)
{
	Initialize();
	color		= c;
	width		= w;
	height		= h;
	pos			= p;
	appearance	= app;
	GameBoard	= gb;
}

COORD GPeople::GetPosition()
{
	return pos;
}

bool GPeople::Impacted(std::vector<Animal*> animals)
{
	for (const Animal* obj : animals)
		if (((pos.X + width - 1 >= obj->GetX()) && (obj->GetX() + obj->GetWidth() - 1 >= pos.X)
			&& (pos.Y + height - 1 >= obj->GetY()) && (obj->GetY() + obj->GetHeight() - 1 >= pos.Y)) == true)
		{
			alive = false;
			return true;
		}

	return false;
}

bool GPeople::Impacted(std::vector<Vehicle*> vehicles)
{
	for (const Vehicle* obj : vehicles)
		if (((pos.X + width - 1 >= obj->GetX()) && (obj->GetX() + obj->GetWidth() - 1 >= pos.X)
			&& (pos.Y + height - 1 >= obj->GetY()) && (obj->GetY() + obj->GetHeight() - 1 >= pos.Y)) == true)
		{
			alive = false;
			return true;
		}

	return false;
}

bool GPeople::Dead()
{
	return alive == false;
}

void GPeople::Initialize()
{
	color		= Color::lightaqua;
	width		= NULL;
	height		= NULL;
	GameBoard	= { NULL, NULL, NULL, NULL };
	pos			= { NULL, NULL };
	appearance	= "\0";
	alive		= true;
	g_handle	= Console::consoleHandle();
}

void GPeople::DrawEffect()
{
	for (int i = 0; i < 4; ++i)
	{
		Draw();
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		Graphics::RemoveArea(Console::outputHandle(), pos, { short(pos.X + width - 1), short(pos.Y + height - 1) });
		Graphics::DrawGraphics(Console::outputHandle(), { pos.X, short(pos.Y - 1) }, "graphics/people/peopledie.txt", Color::lightpurple);
		std::this_thread::sleep_for(std::chrono::milliseconds(220));
	}
}


void GPeople::Draw()
{
	Graphics::DrawGraphics(Console::outputHandle(), pos, appearance, color);
}

void GPeople::Moving(const short& st)
{
	Graphics::RemoveArea(Console::outputHandle(), pos, {short(pos.X + width - 2), short(pos.Y + height - 1)});

	switch (st)
	{
	case 1:
		if (pos.Y > GameBoard.top + 1)
			pos.Y--;
		break;
	case 2:
		if (pos.Y < GameBoard.bottom - height - 1)
			pos.Y++;
		break;
	case 3:
		if (pos.X > GameBoard.left + 2) 
			pos.X--;
		break;
	case 4:
		if (pos.X < GameBoard.right - width - 1)
			pos.X++;
		break;
	}
	Draw();
}
