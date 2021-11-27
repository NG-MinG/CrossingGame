#pragma once
#include "GAnimal.h"

class GMonkey : public GAnimal
{
public:
	GMonkey();
	GMonkey(const Color& c, const std::string& app, const short& st, const COORD& p, const RECT& gb);

	virtual void Moving() override;
	virtual void resetSpeed() override;
	void Sound();
};