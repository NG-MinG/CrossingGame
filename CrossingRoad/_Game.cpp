#include "_Game.h"

void _Game::Music()
{
	bool isOpen = false, isStop = false;
	console->OpenMusic(L"music/Menu.mp3");

	while (r_music == true)
	{
		if (!bg_music && !isStop)
		{
			console->StopMusic();
			isStop = true;
			isOpen = false;
		}
		else if (bg_music && !isOpen)
		{
			console->PlayMusic(volume);
			isStop = false;
			isOpen = true;
		}
	}

	console->CloseMusic();
}

void _Game::Initialize()
{
	console		= nullptr;
	r_music		= true;
	bg_music	= true;
	g_music		= true;
	g_exit		= false;
	volume		= 400;
	t_Sound		= std::thread(&_Game::Music, this);
}

_Game::_Game(const short& width, const short& height, const std::wstring& title, const bool& cursor, const Color& color)
{
	Initialize();
	console = new Console(width, height, title, cursor, color);
}

_Game::_Game()
{
	Initialize();
	console = new Console();
}

_Game::~_Game()
{
	g_exit		= true;

	bg_music	= false;
	g_music		= false;
	r_music		= false;

	Sleep(40);

	delete console;
	console = nullptr;

	t_Sound.join();
}
