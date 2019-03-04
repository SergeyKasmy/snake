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
		WINDOW *m_win;
	public:
		GameUI(WINDOW *p_win);
		~GameUI();
		void display_field(Field *p_field);
		Facing get_input();
};