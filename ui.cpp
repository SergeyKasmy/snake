#include <string.h>
#include "game.hpp"
#include "ui.hpp"

MainMenu::MainMenu()
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);
	getmaxyx(stdscr, m_size_rows, m_size_cols);
}

MainMenu::~MainMenu()
{
	endwin();
}

void MainMenu::show()
{
	Point item_new_game = {m_size_rows / 2, (int) (m_size_cols - strlen("New Game")) / 2};
	Point item_exit = {m_size_rows / 2 + 1, (int) (m_size_cols - strlen("Exit")) / 2};

	MenuItem selected_item = MenuItem::new_game;

	try
	{
		while(true)
		{
			mvprintw(item_new_game.y, item_new_game.x, "New Game");
			mvprintw(item_exit.y, item_exit.x, "Exit");

			switch(selected_item)
			{
				case MenuItem::new_game:
					move(item_new_game.y, item_new_game.x);
					break;
				case MenuItem::exit:
					move(item_exit.y, item_exit.x);
					break;
			}
			refresh();
			int ch = getch();
			switch(ch)
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
	catch(const GameExit &) {}
}

void MainMenu::select(MenuItem p_selected_item)
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
    curs_set(0);
	keypad(m_win, true);
	nodelay(m_win, true);
}

GameUI::~GameUI()
{
	curs_set(1);
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