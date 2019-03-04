#pragma once

#include <ncurses.h>

#include "field.hpp"
#include "player.hpp"

struct GameExit : std::exception {};

class MainMenu
{
	private:
		enum class MenuItem { new_game, exit };

		int m_size_rows, m_size_cols;

		void select(MenuItem p_selected_item);
		void new_game();
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