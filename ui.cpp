#include "ui.hpp"

#include "game.hpp"
#include "player.hpp"
#include "settings.hpp"

// MainMenuItem
namespace MMItem
{
	const static menu_item_t new_game = 0;
	const static menu_item_t settings = 1;
	const static menu_item_t exit = 2;

	const static char* const new_game_str = "New Game";
	const static char* const settings_str = "Settings";
	const static char* const exit_srt = "Exit";

	const static int new_game_str_length = 8;
	const static int settings_str_length = 8;
	const static int exit_str_length = 4;
}

// SettingsItem
namespace SItem
{
	const static menu_item_t enable_walls = 0;

	const static char* const enable_walls_str = "Enable walls";

	const static int enable_walls_str_length = 12;
}

struct GameExit : std::exception {};

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

// shows the main menu
void MainMenu::show()
{
	try
	{
		Point item_new_game = {m_size_rows / 2, (m_size_cols - MMItem::new_game_str_length) / 2};
		Point item_settings = {m_size_rows / 2 + 1, (m_size_cols - MMItem::settings_str_length) / 2};
		Point item_exit = {m_size_rows / 2 + 2, (m_size_cols - MMItem::exit_str_length) / 2};

		menu_item_t selected_item = MMItem::new_game;
		// holds the char input from the user
		int ch;

		while(true)
		{
			mvprintw(m_size_rows / 4, (m_size_cols - 5) / 2, "Snake");

			mvprintw(item_new_game.y, item_new_game.x, MMItem::new_game_str);
			mvprintw(item_settings.y, item_settings.x, MMItem::settings_str);
			mvprintw(item_exit.y, item_exit.x, MMItem::exit_srt);

			// make the currently selected item bold
			switch(selected_item)
			{
				case MMItem::new_game:
					mvchgat(item_new_game.y, item_new_game.x, MMItem::new_game_str_length, A_BOLD, 0, NULL);
					break;
				case MMItem::settings:
					mvchgat(item_settings.y, item_settings.x, MMItem::settings_str_length, A_BOLD, 0, NULL);
					break;
				case MMItem::exit:
					mvchgat(item_exit.y, item_exit.x, MMItem::exit_str_length, A_BOLD, 0, NULL);
					break;
			}
			refresh();

			switch(ch = getch())
			{
				case KEY_UP:
					selected_item = selected_item != MMItem::new_game ? selected_item - 1 : MMItem::exit;
					break;
				case KEY_DOWN:
					selected_item = selected_item != MMItem::exit ? selected_item + 1 : MMItem::new_game;
					break;
				case '\n':
					erase();
					select(selected_item);
					erase();
					break;
			}
		}
	}
	// exit the game, if it's called for an exit
	catch(const GameExit &) {}
}

void MainMenu::select(menu_item_t p_selected_item)
{
	switch (p_selected_item)
	{
		case MMItem::new_game:
			new_game();
			break;
		case MMItem::settings:
			show_settings();
			break;
		case MMItem::exit:
			throw GameExit();
	}
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

// TODO: use a single fucniton to display both main and settings menus to avoid code dublication
// TODO: implement the ability to edit game settings
// TODO: implement the ability to enter field size as numbers or with arrows
void MainMenu::show_settings()
{
	Point item_enable_walls = {m_size_rows / 2, (m_size_cols - SItem::enable_walls_str_length) / 2};

	menu_item_t selected_item = SItem::enable_walls;
	int ch;

	while(true)
	{
		mvprintw(item_enable_walls.y, item_enable_walls.x, SItem::enable_walls_str);
		refresh();

		switch(selected_item)
		{
			case SItem::enable_walls:
				mvchgat(item_enable_walls.y, item_enable_walls.x, SItem::enable_walls_str_length, A_BOLD, 0, NULL);
				break;
		}
		refresh();

			switch(ch = getch())
			{
				case KEY_UP:
					selected_item = selected_item != SItem::enable_walls ? selected_item - 1 : SItem::enable_walls;
					break;
				case KEY_DOWN:
					selected_item = selected_item != SItem::enable_walls ? selected_item + 1 : SItem::enable_walls;
					break;
				case '\n':
					//erase();
					//select(selected_item);
					//erase();
					break;
				case 'q':
				// ESC
				case 27:
					goto endloop;
			}
	}
	endloop:
	return;
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