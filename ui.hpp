#pragma once

// TODO: optimize include's
#include <ncurses.h>
#include <string>
#include <vector>

#include "point.h"

class Field;
enum class Facing;

using menu_item_t = int;

const static int FIELD_BEGIN_ROW = 1;

struct MenuItem
{
	std::string label;
	Point pos;
};

class MainMenu
{
	private:
		int m_size_rows, m_size_cols;

		template<typename Functor>
		void display_menu(std::vector<MenuItem> p_menu_items, Functor p_selected_item_handler, bool p_quit_with_q, std::string p_title = "Snake");
		void new_game();
		void show_settings();
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

		void update_field();
	public:
		GameUI(WINDOW *p_win);

		void set_field(Field *p_field) { m_field = p_field; };
		void draw_static_elements();
		void update(int score);
		Facing get_input();
};