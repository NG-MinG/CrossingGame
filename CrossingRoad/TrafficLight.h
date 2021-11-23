#pragma once
#include "Graphics.h"
#include "Console.h"

template<class T>
class TrafficLight
{
private:
	COORD pos;
	short greenTime, redTime;
	short prevgreenTime, prevredTime;
	bool isRed;

public:
	TrafficLight<T>() {};
	TrafficLight<T>(COORD p, short gt, short rt)
	{
		pos = p;
		greenTime = gt;
		prevgreenTime = gt;
		redTime = rt;
		prevredTime = rt;
		isRed = false;
	}

	void Draw()
	{
		if (isRed == true) Graphics::DrawTexts(Console::outputHandle(), "█", pos, Color::red);
		else Graphics::DrawTexts(Console::outputHandle(), "█", pos, Color::green);
	}

	void UpdateState(std::vector<T*> obj)
	{
		if (greenTime != 0) greenTime--;
		else
		{
			isRed = true;
			if (redTime != 0) redTime--;
			else redTime = prevredTime, greenTime = prevgreenTime, isRed = false;
		}

		Draw();

		for (T* x : obj)
			if (isRed == true) x->StopRedLight();
			else x->RunGreenLight();
	}

};