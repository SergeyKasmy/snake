#pragma once

#include <functional>
#include <curses.h>

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
		void show_settings();
	public:
		MainMenu();
		~MainMenu();
		void show();

		static void display_menu(std::vector<MenuItem> &p_menu_items, std::function<void(menu_item_t)> p_selected_item_handler, bool p_quit_with_q, std::string p_title = "Snake");
		void new_game();
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
		static menu_item_t dialogbox(std::string p_title, std::vector<std::string> p_buttons);
};
