#include "ui.hpp"

#include "game.hpp"
#include "player.hpp"
#include "settings.hpp"

struct GameExit : std::exception {};

inline const char* const bool_to_str(bool b) { return b ? "enabled" : "disabled"; }

// TODO: implement the ability to edit game settings
// TODO: implement the ability to enter field size as numbers or with arrows
template<typename Functor>
void MainMenu::display_menu(std::vector<MenuItem> &p_menu_items, Functor p_selected_item_handler, bool p_quit_with_q, std::string p_title)
{
	for(int i = 0; i < p_menu_items.size(); ++i)
	{
		p_menu_items[i].pos = {m_size_rows / 2 + i, 
							(m_size_cols - p_menu_items[i].label.length()) / 2};
	}

	try
	{
		erase();
		menu_item_t selected_item = 0;
		bool is_selected = false;
		while(true)
		{
			mvprintw(m_size_rows / 4, (m_size_cols - p_title.length()) / 2, p_title.c_str());

			for(int i = 0; i < p_menu_items.size(); ++i)
			{
				mvprintw(p_menu_items[i].pos.y, p_menu_items[i].pos.x, p_menu_items[i].label.c_str());
			}

			// make the currently selected item bold
			mvchgat(p_menu_items[selected_item].pos.y, p_menu_items[selected_item].pos.x, p_menu_items[selected_item].label.length(), A_BOLD, 0, NULL);
			refresh();

			switch(getch())
			{
				case KEY_UP:
				{
					int arr_size = p_menu_items.size();
					selected_item = (((selected_item - 1) % arr_size) + arr_size) % arr_size;
					break;
				}
				case KEY_DOWN:
					selected_item = (selected_item + 1) % p_menu_items.size();
					break;
				case '\n':
					is_selected = true;
					break;
				case 'q':
				case 27:
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
	WINDOW *game_win = newwin(Settings::field_size.y + FIELD_BEGIN_ROW, Settings::field_size.x, (m_size_rows - Settings::field_size.y) / 2, (m_size_cols - Settings::field_size.x) / 2);
	GameUI *game_ui = new GameUI(game_win);

	Game game(game_ui);
	game.start();

	delwin(game_win);
	delete game_ui;
}

void MainMenu::show_settings()
{
	std::vector<MenuItem> settings_menu_items = {{ 
												{std::string("Field size: ") + std::to_string(Settings::field_size.y) + " rows, " + std::to_string(Settings::field_size.x) + " cols"},
												{std::string("Walls: ") + bool_to_str(Settings::enable_walls), {} }, 
												}};
	display_menu(settings_menu_items, 
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
									Settings::field_size = {10, 15};
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
	getmaxyx(stdscr, m_size_rows, m_size_cols);
}

MainMenu::~MainMenu()
{
	endwin();
}

void MainMenu::show()
{
	std::vector<MenuItem> main_menu_items = {{ 
											{"New Game", {} },
											{"Settings", {} },
											{"Exit", {} }
											}};

	display_menu(main_menu_items, 
				[this](menu_item_t p_selected_item)
				{
					switch(p_selected_item)
					{
						// New Game
						case 0:
							new_game();
							break;
						// Settings
						case 1:
							show_settings();
							break;
						case 2:
							throw GameExit();
					}
				}, false);
}

GameUI::GameUI(WINDOW *p_win) : m_win(p_win)
{
	nodelay(m_win, true);
	keypad(m_win, true);
}

void GameUI::draw_static_elements()
{
	for(int row = 0; row < m_field->m_field_size.y; ++row)
	{
		for(int col = 0; col < m_field->m_field_size.x; ++col)
		{
			switch (m_field->get({row, col}))
			{
				case Object::wall_horizontal:
					mvwaddch(m_win, row + FIELD_BEGIN_ROW, col, '-');
					break;
				case Object::wall_vertical:
					mvwaddch(m_win, row + FIELD_BEGIN_ROW, col, '|');
					break;
				case Object::corner:
					mvwaddch(m_win, row + FIELD_BEGIN_ROW, col, '+');
					break;
				default:
					break;
			}
		}
	}

	refresh();
}

void GameUI::update(int score)
{
	mvwprintw(m_win, 0, 0, "Score: %d", score);
	update_field();
	refresh();
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
					mvwaddch(m_win, row + FIELD_BEGIN_ROW, col, ' ');
					break;
				case Object::player:
					mvwaddch(m_win, row + FIELD_BEGIN_ROW, col, '*');
					break;
				case Object::food:
					mvwaddch(m_win, row + FIELD_BEGIN_ROW, col, '$');
					break;
				default:
					break;
			}
		}
	}
}

Facing GameUI::get_input()
{
	int input = wgetch(m_win);
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
	}

	return Facing::null;
}