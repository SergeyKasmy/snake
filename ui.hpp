#pragma once

#include <ncurses.h>

#include "field.hpp"
#include "player.hpp"

class MainMenu
{
    public:
        MainMenu();
        ~MainMenu();
        void show();
};

class GameUI
{
    private:
        WINDOW *mWin;
    public:
        GameUI(WINDOW *pWin);
        ~GameUI();
        void display_field(Field *field);
        Facing get_input();
};