#pragma once

#include <functional>
#include <curses.h>

#include <string>
#include <vector>

#include "point.hpp"
#include "field.hpp"

class Field;
enum class Facing;

static const char* bool_to_str(bool b) { return b ? "enabled" : "disabled"; }

struct GameExit : std::exception {};
struct GameEndQuit : std::exception {};

class Ui
{
	public:
		Ui();
		~Ui();
		int display_menu(std::vector<std::string> &p_menu_items, bool p_quit_with_q, std::string p_title = "Snake");
		int dialogbox(std::string p_title, std::vector<std::string> p_buttons);

		// Game Ui
		WINDOW *m_field_win, *m_border_win;
		void game_start(Field &p_field);
		void game_end();
		void draw_static_elements(const Field &p_field);
		Facing get_input();
		void update(const Field &p_field, int p_score);
};
