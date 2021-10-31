#pragma once
#include <random>
#include "Graphics.h"
#include "Console.h"

class Animal
{
public:
	Animal();

	virtual void Moving() = 0;
	virtual void Tell () = 0;

	short GetWidth() const;
	short GetHeight() const;
	short GetX() const;
	short GetY() const;
	COORD GetPostion() const;
	double GetDistance(const COORD& pos1) const;

	bool isMoving() const;
	void StartMoving(const short& st);
	void StopMoving();

protected:
	HANDLE g_handle;
	RECT GameBoard;

	Color color;
	COORD pos;
	short width, height, state;
	std::string appearance;
};

