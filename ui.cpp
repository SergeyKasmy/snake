#include "game.hpp"
#include "ui.hpp"

namespace MenuItem
{
	const static menu_item_t new_game = 0;
	const static menu_item_t exit = 1;

	const static char* const new_game_str = "New Game";
	const static char* const exit_srt = "Exit";

	const static int new_game_str_length = 8;
	const static int exit_str_length = 4;
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
		Point item_new_game = {m_size_rows / 2, (int) (m_size_cols - MenuItem::new_game_str_length) / 2};
		Point item_exit = {m_size_rows / 2 + 1, (int) (m_size_cols - MenuItem::exit_str_length) / 2};
		menu_item_t selected_item = MenuItem::new_game;

		// holds the char input from the user
		int ch;

		while(true)
		{
			mvprintw(item_new_game.y, item_new_game.x, MenuItem::new_game_str);
			mvprintw(item_exit.y, item_exit.x, MenuItem::exit_srt);

			// make the currently selected item bold
			switch(selected_item)
			{
				case MenuItem::new_game:
					mvchgat(item_new_game.y, item_new_game.x, MenuItem::new_game_str_length, A_BOLD, 0, NULL);
					break;
				case MenuItem::exit:
					mvchgat(item_exit.y, item_exit.x, MenuItem::exit_str_length, A_BOLD, 0, NULL);
					break;
			}
			refresh();

			switch(ch = getch())
			{
				case KEY_UP:
					selected_item = MenuItem::new_game;
					break;
				case KEY_DOWN:
					selected_item = MenuItem::exit;
					break;
				case '\n':
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
		case MenuItem::new_game:
			new_game();
			break;
		case MenuItem::exit:
			throw GameExit();
	}
}

void MainMenu::new_game()
{
	WINDOW *game_win = newwin(m_size_rows, m_size_cols, 0, 0);
	GameUI *game_ui = new GameUI(game_win);

	Game game(game_ui);
	game.start();

	delwin(game_win);
	delete game_ui;
}

GameUI::GameUI(WINDOW *p_win) : m_win(p_win)
{
	keypad(m_win, true);
	nodelay(m_win, true);
}


void GameUI::display_field(Field *p_field)
{
	wmove(m_win, 0, 0);

	for(int row = 0; row < p_field->m_field_size.y; row++)
	{
		for(int column = 0; column < p_field->m_field_size.x; column++)
		{
			switch(p_field->get({row, column}))
			{
				case Object::empty:
					mvwaddch(m_win, row, column, ' ');
					break;
				case Object::player:
					mvwaddch(m_win, row, column, 'p');
					break;
				case Object::food:
					mvwaddch(m_win, row, column, 'f');
					break;
				case Object::wall:
					mvwaddch(m_win, row, column, 'w');
					break;
			}
		}
		
		wmove(m_win, row+1, 0);
	}
	refresh();
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