#pragma once

#ifdef __unix__
	#include <ncurses.h>
#elif _WIN32
	#include <pdcurses.h>
#endif

#include <string>
#include <vector>

#include "point.hpp"

class Field;
enum class Facing;

using menu_item_t = int;

struct MenuItem
{
	std::string label;
	Point pos;
};

class MainMenu
{
	private:
		template<typename Functor>
		void display_menu(std::vector<MenuItem> &p_menu_items, Functor p_selected_item_handler, bool p_quit_with_q, std::string p_title = "Snake");
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
		WINDOW *m_border_win, *m_field_win;
		const Field *m_field;

		void update_field();
	public:
		GameUI();
		~GameUI();

		void set_field(Field *p_field) { m_field = p_field; };
		void draw_border();
		void draw_static_elements();
		void update(int p_score);
		Facing get_input();

};

class UIUtils
{
	public:
		UIUtils() = delete;
		static menu_item_t dialogbox(std::string p_text, std::vector<std::string> p_buttons);
};
