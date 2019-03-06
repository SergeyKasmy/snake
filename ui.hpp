#pragma once

#include <ncurses.h>

class Field;
enum class Facing;

using menu_item_t = int;

const static int FIELD_BEGIN_ROW = 1;

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
		const Field *m_field;

		void draw_field();
	public:
		GameUI(WINDOW *p_win);

		void set_field(Field *p_field) { m_field = p_field; };
		void draw(int score);
		Facing get_input();
};