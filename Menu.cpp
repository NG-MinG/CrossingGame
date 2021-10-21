#include "Menu.h"
#include "Graphics.h"
#include "Console.h"

Menu::Menu(bool *bg_ms,  bool*g_ms) {
    bg_music = bg_ms;
    g_music = g_ms;
}

Menu::Menu() {
    bg_music = g_music = nullptr;
}

void Menu::DrawMenu() {
    Graphics::DrawGraphics(GetStdHandle(STD_OUTPUT_HANDLE), "menu.txt", COORD{ 28, 7 }, (int)Color::lightyellow);
}

void Menu::HookMainMenu() {

    int i = 1;

    Graphics::DrawTexts(GetStdHandle(STD_OUTPUT_HANDLE), " PLAY NEW GAME ", COORD{ 56, 26 }, (int)Color::lightgreen);

    while (true) {
        if (Console::KeyPress(VK_DOWN) || Console::KeyPress(VK_RIGHT))
        {
            Graphics::DrawTexts(GetStdHandle(STD_OUTPUT_HANDLE), " PLAY NEW GAME ", COORD{ 56, 26 }, (int)Color::lightyellow);
            Graphics::DrawTexts(GetStdHandle(STD_OUTPUT_HANDLE), " LOAD GAME ", COORD{ 58, 28 }, (int)Color::lightyellow);
            Graphics::DrawTexts(GetStdHandle(STD_OUTPUT_HANDLE), " RANKING ", COORD{ 59, 30 }, (int)Color::lightyellow);
            Graphics::DrawTexts(GetStdHandle(STD_OUTPUT_HANDLE), " OPTIONS ", COORD{ 59, 32 }, (int)Color::lightyellow);

            i++;

            if (i == 5)
                i = 1;

            switch (i)
            {
            case 1: {
                Graphics::DrawTexts(GetStdHandle(STD_OUTPUT_HANDLE), " PLAY NEW GAME ", COORD{ 56, 26 }, (int)Color::lightgreen);
                break;
            }
            case 2: {
                Graphics::DrawTexts(GetStdHandle(STD_OUTPUT_HANDLE), " LOAD GAME ", COORD{ 58, 28 }, (int)Color::lightgreen);
                break;
            }
            case 3: {
                Graphics::DrawTexts(GetStdHandle(STD_OUTPUT_HANDLE), " RANKING ", COORD{ 59, 30 }, (int)Color::lightgreen);
                break;
            }
            case 4: {
                Graphics::DrawTexts(GetStdHandle(STD_OUTPUT_HANDLE), " OPTIONS ", COORD{ 59, 32 }, (int)Color::lightgreen);
                break;
            }
            }
        }
        else if (Console::KeyPress(VK_UP) || Console::KeyPress(VK_LEFT)) {
            Graphics::DrawTexts(GetStdHandle(STD_OUTPUT_HANDLE), " PLAY NEW GAME ", COORD{ 56, 26 }, (int)Color::lightyellow);
            Graphics::DrawTexts(GetStdHandle(STD_OUTPUT_HANDLE), " LOAD GAME ", COORD{ 58, 28 }, (int)Color::lightyellow);
            Graphics::DrawTexts(GetStdHandle(STD_OUTPUT_HANDLE), " RANKING ", COORD{ 59, 30 }, (int)Color::lightyellow);
            Graphics::DrawTexts(GetStdHandle(STD_OUTPUT_HANDLE), " OPTIONS ", COORD{ 59, 32 }, (int)Color::lightyellow);

            if (i == 1)
                i = 4;
            else i--;

            switch (i)
            {
            case 1: {
                Graphics::DrawTexts(GetStdHandle(STD_OUTPUT_HANDLE), " PLAY NEW GAME ", COORD{ 56, 26 }, (int)Color::lightgreen);
                break;
            }
            case 2: {
                Graphics::DrawTexts(GetStdHandle(STD_OUTPUT_HANDLE), " LOAD GAME ", COORD{ 58, 28 }, (int)Color::lightgreen);
                break;
            }
            case 3: {
                Graphics::DrawTexts(GetStdHandle(STD_OUTPUT_HANDLE), " RANKING ", COORD{ 59, 30 }, (int)Color::lightgreen);
                break;
            }
            case 4: {
                Graphics::DrawTexts(GetStdHandle(STD_OUTPUT_HANDLE), " OPTIONS ", COORD{ 59, 32 }, (int)Color::lightgreen);
                break;
            }
            }
        }
    }
}