#pragma once

#include <functional>
#include <curses.h>

#include <string>
#include <vector>

#include "point.hpp"

class Field;
enum class Facing;


class MainMenu
{
	private:
		void show_settings();
	public:
		MainMenu();
		~MainMenu();
		void show();
};

class GameUi
{
	private:
		WINDOW *m_border_win, *m_field_win;
		const Field *m_field;

		void update_field();
	public:
		GameUi();
		~GameUi();

		void set_field(Field *p_field) { m_field = p_field; };
		void draw_border();
		void update(int p_score);
		Facing get_input();

		void game_start();	// prepare the ui for a new game
		void draw_static_elements();
};

class Ui
{
	public:
		Ui();
		~Ui();
		int display_menu(std::vector<std::string> &p_menu_items, bool p_quit_with_q, std::string p_title = "Snake");
		int dialogbox(std::string p_title, std::vector<std::string> p_buttons);
};
