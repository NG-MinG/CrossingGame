#include "GCAR.h"

GCAR::GCAR(const Color& c, const std::string& app , const short& st, const short& w, const short& h, COORD p):Vehicle()
{
	color = c;
	pos = p;
	appearance = app;
	width = w;
	height = h;
	state = st;
}

void GCAR::Draw()
{
	if(state==1)
	Graphics::DrawGraphics(ohandle, appearance, pos, (int)color);
	else if(state==2)
	Graphics::DrawGraphicsR(ohandle, appearance, pos, (int)color);
}
void GCAR::MovingLeft()
{
	static const COORD p_run = pos;
	if (pos.X <= 77)
	{
		Graphics::CleanArea(ohandle, pos, { pos.X,short(pos.Y + height - 1) });
		pos.X++;
		Draw();
	}
	else
	{
		Graphics::CleanArea(ohandle, pos, { short(pos.X + width - 1),short(pos.Y + height - 1) });
		pos = p_run;
		StopMoving();
	}
}
void GCAR::MovingRight()
{
	static const COORD p_run = pos;
	if (pos.X >=15 )
	{
		Graphics::CleanArea(ohandle, { short(pos.X + width - 3),pos.Y }, { short(pos.X + width - 1),short(pos.Y + height - 1) });
		pos.X--;
		Draw();
	}
	else
	{
		Graphics::CleanArea(ohandle, pos, { short(pos.X + width - 1),short(pos.Y + height - 1) });
		pos = p_run;
		StopMoving();
	}
}
void GCAR::Moving()
{
	if (state == 1)
		MovingLeft();
	else if (state == 2)
		MovingRight();
	
}
void GCAR::Beep()
{
}


