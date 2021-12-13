#pragma once
#include <fstream>
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
	TrafficLight();
	TrafficLight(const COORD& p, const short& gt, const short& rt);
	void Draw();
	void UpdateState(std::vector<T*>& obj);
};

template<class T>
TrafficLight<T>::TrafficLight()
{
	pos = { NULL, NULL };
	greenTime = 40;
	prevgreenTime = 40;
	redTime = 30;
	prevredTime = 30;
	isRed = false;
}

template<class T>
TrafficLight<T>::TrafficLight(const COORD& p, const short& gt, const short& rt)
{
	pos = p;
	greenTime = gt;
	prevgreenTime = gt;
	redTime = rt;
	prevredTime = rt;
	isRed = false;
}

template<class T>
void TrafficLight<T>::Draw()
{
	Graphics::DrawTexts("O", pos, Color::gray);
	Graphics::DrawTexts("O", { pos.X, short(pos.Y + 1) }, Color::gray);

	(isRed) ? Graphics::DrawTexts("O", pos, Color::lightred)
		: Graphics::DrawTexts("O", { pos.X, short(pos.Y + 1) }, Color::lightgreen);
}

template<class T>
void TrafficLight<T>::UpdateState(std::vector<T*>& obj)
{
	if (greenTime != 0) greenTime--;
	else
	{
		isRed = true;
		if (redTime != 0) redTime--;
		else redTime = prevredTime, greenTime = prevgreenTime, isRed = false;
	}

	Draw();

	for (T*& x : obj)
		(isRed) ? x->StopRedLight() : x->RunGreenLight();
}