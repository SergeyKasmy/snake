#pragma once

#include <ncurses.h>

class Field;
enum class Facing;

using menu_item_t = int;

class MainMenu
{
	private:
		int m_size_rows, m_size_cols;

		void select(menu_item_t p_selected_item);
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
		void display_field(Field *p_field);
		Facing get_input();
};