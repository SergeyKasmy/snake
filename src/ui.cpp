//#include <stdexcept>
#include <cassert>

#include "ui.hpp"

#include "field.hpp"
#include "player.hpp"
#include "settings.hpp"


#include "controller.hpp"

// TODO: implement the ability to edit game settings
// TODO: implement the ability to enter field size as numbers or with arrows
int Ui::display_menu(std::vector<std::string> &p_menu_items, bool p_quit_with_q, std::string p_title)
{
	std::vector<Point> item_positions(p_menu_items.size());
	for(std::size_t i = 0; i < p_menu_items.size(); ++i)
	{
		item_positions[i] = {LINES / 2 + (int) i, 
							(COLS - (int) p_menu_items[i].length()) / 2};
	}

	try
	{
		erase();
		int selected_item = 0;
		bool is_selected = false;
		while(true)
		{
			mvprintw(LINES / 4, (COLS - p_title.length()) / 2, p_title.c_str());

			for(std::size_t i = 0; i < p_menu_items.size(); ++i)
			{
				mvprintw(item_positions[i].y, item_positions[i].x, p_menu_items[i].c_str());
			}

			// make the currently selected item bold
			mvchgat(item_positions[selected_item].y, item_positions[selected_item].x, p_menu_items[selected_item].length(), A_STANDOUT, 0, NULL);
			refresh();

			switch(getch())
			{
				case KEY_UP:
					selected_item = selected_item != 0 ? selected_item - 1 : p_menu_items.size() - 1;
					break;
				case KEY_DOWN:
					selected_item = selected_item != (int) p_menu_items.size() - 1 ? selected_item + 1 : 0;
					break;
				case '\n':
					is_selected = true;
					break;
				case 'q':
					if(p_quit_with_q) throw GameExit();
					break;
			}

			if(is_selected) 
			{
				erase();
				return selected_item;
			}
		}
	}
	// exit the game, if it's called for an exit
	catch(const GameExit &) {}

	return -1;
}


void Ui::game_start(Field &p_field)
{
	erase();
	refresh();
	m_border_win = newwin(Settings::field_size.y + 2, Settings::field_size.x + 2, (LINES - Settings::field_size.y) / 2 - 1, (COLS - Settings::field_size.x) / 2 - 1);
	m_field_win = newwin(Settings::field_size.y, Settings::field_size.x, (LINES - Settings::field_size.y) / 2, (COLS - Settings::field_size.x) / 2);
	assert(m_border_win != 0);
	assert(m_border_win != 0);
	box(m_border_win, 0, 0);
	wrefresh(m_border_win);
	nodelay(m_field_win, true);
	keypad(m_field_win, true);
	draw_static_elements(p_field);
}

void Ui::game_end()
{
	delwin(m_field_win);
	delwin(m_border_win);
}


Ui::Ui()
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);

	keypad(stdscr, true);
}

Ui::~Ui()
{
	endwin();
}

void Ui::draw_static_elements(const Field &p_field)
{
	for(int row = 0; row < p_field.m_field_size.y; ++row)
	{
		for(int col = 0; col < p_field.m_field_size.x; ++col)
		{
			if(p_field.get({row, col}) == Object::wall) mvwaddch(m_field_win, row , col, '#');
		}
	}

	wrefresh(m_field_win);
}

void Ui::update(const Field &p_field, int p_score)
{
	mvwprintw(m_border_win, 0, 2, "Score: %d", p_score);
	wrefresh(m_border_win);
	for(int row = 0; row < p_field.m_field_size.y; ++row)
	{
		for(int col = 0; col < p_field.m_field_size.x; ++col)
		{
			switch(p_field.get({row, col}))
			{
				case Object::empty:
					mvwaddch(m_field_win, row , col, ' ');
					break;
				case Object::player:
					mvwaddch(m_field_win, row , col, '*');
					break;
				case Object::food:
					mvwaddch(m_field_win, row , col, '$');
					break;
				default:
					break;
			}
		}
	}
	wrefresh(m_field_win);
}

Facing Ui::get_input()
{
	int input = wgetch(m_field_win);
	switch (input)
	{
		case KEY_UP:
			return Facing::up;
		case KEY_RIGHT:
			return Facing::right;
		case KEY_DOWN:
			return Facing::down;
		case KEY_LEFT:
			return Facing::left;
		case 'q':
			throw GameEndQuit();
			break;
	}

	return Facing::null;
}

int Ui::dialogbox(std::string p_title, std::vector<std::string> p_buttons)
{
	// if COLS / 4 < min_width(the width so that all elements would fit) -> width = COLS - 4, else width = COLS / 4
	int width = COLS / 4 < [&p_title, &p_buttons]() -> int 
							{
								int min_width = 0;
								for(std::string button : p_buttons)
								{
									min_width += button.length() + 2;
								}
								min_width = min_width > (int) p_title.length() ? min_width : p_title.length();
								return min_width + 10;
							} () ? COLS - 10 : COLS / 4;

	WINDOW *win = newwin(7, width, (LINES - 7) / 2, (COLS - (width)) / 2);
	keypad(win, true);

	box(win, 0, 0);
	mvwprintw(win, 2, (win->_maxx - p_title.length()) / 2, p_title.c_str());
	wrefresh(win);

	int selected_item = 0;
	while(true)
	{
		for(std::size_t i = 0; i < p_buttons.size(); ++i) 
		{
			// x = (total width of the window / (amount of buttons + 1)) * (current button + 1) - (length of the text of the button / 2)
			mvwprintw(win,
						5, 
						(win->_maxx / (p_buttons.size() + 1)) * (i + 1) - (p_buttons[i].length() / 2),
						p_buttons[i].c_str());
		}

		mvwchgat(win, 5, (win->_maxx / (p_buttons.size() + 1)) * (selected_item + 1) - (p_buttons[selected_item].length() / 2), p_buttons[selected_item].length(), A_STANDOUT, 0, NULL);

		switch(wgetch(win))
		{
			case KEY_LEFT:
				selected_item = selected_item != 0 ? selected_item - 1 : p_buttons.size() - 1;
				break;
			case KEY_RIGHT:
				selected_item = selected_item != (int) p_buttons.size() - 1 ? selected_item + 1 : 0;
				break;
			// Enter
			case '\n':
				werase(win);
				wrefresh(win);
				delwin(win);
				return selected_item;
		}
	}

	throw std::logic_error("Out of the infinite while loop");
}
