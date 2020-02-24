#include <stdexcept>

#include "ui.hpp"

#include "field.hpp"
#include "game.hpp"
#include "player.hpp"
#include "settings.hpp"


#include "controller.hpp"

struct GameExit : std::exception {};

static const char* bool_to_str(bool b) { return b ? "enabled" : "disabled"; }

// TODO: implement the ability to edit game settings
// TODO: implement the ability to enter field size as numbers or with arrows
void Ui::display_menu(std::vector<MenuItem> &p_menu_items, std::function<void(menu_item_t)> p_selected_item_handler, bool p_quit_with_q, std::string p_title)
{
	for(std::size_t i = 0; i < p_menu_items.size(); ++i)
	{
		p_menu_items[i].pos = {LINES / 2 + (int) i, 
							(COLS - (int) p_menu_items[i].label.length()) / 2};
	}

	try
	{
		erase();
		menu_item_t selected_item = 0;
		bool is_selected = false;
		while(true)
		{
			mvprintw(LINES / 4, (COLS - p_title.length()) / 2, p_title.c_str());

			for(std::size_t i = 0; i < p_menu_items.size(); ++i)
			{
				mvprintw(p_menu_items[i].pos.y, p_menu_items[i].pos.x, p_menu_items[i].label.c_str());
			}

			// make the currently selected item bold
			mvchgat(p_menu_items[selected_item].pos.y, p_menu_items[selected_item].pos.x, p_menu_items[selected_item].label.length(), A_STANDOUT, 0, NULL);
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
				p_selected_item_handler(selected_item);
				is_selected = false;
				erase();
			}
		}
	}
	// exit the game, if it's called for an exit
	catch(const GameExit &) {}
}

void MainMenu::new_game()
{
	erase();
	refresh();
}

void MainMenu::show_settings()
{
	std::vector<MenuItem> settings_menu_items = {{ 
												{std::string("Field size: ") + std::to_string(Settings::field_size.y) + " rows, " + std::to_string(Settings::field_size.x) + " cols", {}},
												{std::string("Walls: ") + bool_to_str(Settings::enable_walls), {} }, 
												}};
	Ui::display_menu(settings_menu_items, 
				[&settings_menu_items](menu_item_t p_selected_item) 
				{
					switch (p_selected_item)
					{
						case 0:
							switch(Settings::field_size.y) 
							{
								case 18:
									Settings::field_size = {25, 50};
									break;
								case 25:
									Settings::field_size = {10, 20};
									break;
								default:
							 		Settings::field_size = {18, 35};
									break;
							}
							settings_menu_items[0].label = std::string("Field size: ") + std::to_string(Settings::field_size.y) + " rows, " + std::to_string(Settings::field_size.x) + " cols";
							break;
						case 1:
							Settings::enable_walls = !Settings::enable_walls;
							settings_menu_items[1].label = std::string("Walls: ") + bool_to_str(Settings::enable_walls);
							break;
						default:
							break;
					}
				}, 
				true, "Settings");
}

// sets up the main ui
MainMenu::MainMenu()
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);

	keypad(stdscr, true);
}

MainMenu::~MainMenu()
{
	endwin();
}

void MainMenu::show()
{
}

GameUI::GameUI()
{
	m_border_win = newwin(Settings::field_size.y + 2, Settings::field_size.x + 2, (LINES - Settings::field_size.y) / 2 - 1, (COLS - Settings::field_size.x) / 2 - 1);
	m_field_win = newwin(Settings::field_size.y, Settings::field_size.x, (LINES - Settings::field_size.y) / 2, (COLS - Settings::field_size.x) / 2);
	draw_border();
	nodelay(m_field_win, true);
	keypad(m_field_win, true);
}

GameUI::~GameUI()
{
	delwin(m_field_win);
	delwin(m_border_win);
}

void GameUI::draw_border()
{
	box(m_border_win, 0, 0);
	wrefresh(m_border_win);
}

void GameUI::draw_static_elements()
{
	for(int row = 0; row < m_field->m_field_size.y; ++row)
	{
		for(int col = 0; col < m_field->m_field_size.x; ++col)
		{
			if(m_field->get({row, col}) == Object::wall) mvwaddch(m_field_win, row , col, '#');
		}
	}

	wrefresh(m_field_win);
}

void GameUI::update(int p_score)
{
	mvwprintw(m_border_win, 0, 2, "Score: %d", p_score);
	wrefresh(m_border_win);
	update_field();
	wrefresh(m_field_win);
}

void GameUI::update_field()
{
	for(int row = 0; row < m_field->m_field_size.y; ++row)
	{
		for(int col = 0; col < m_field->m_field_size.x; ++col)
		{
			switch(m_field->get({row, col}))
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
}

Facing GameUI::get_input()
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

menu_item_t Ui::dialogbox(std::string p_title, std::vector<std::string> p_buttons)
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

	menu_item_t selected_item = 0;
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
