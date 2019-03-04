#include <string.h>
#include "game.hpp"
#include "ui.hpp"

MainMenu::MainMenu()
{
	initscr();
	cbreak();
	noecho();
}

MainMenu::~MainMenu()
{
	getch();
	endwin();
}

void MainMenu::show()
{
	int row, col;
	getmaxyx(stdscr, row, col);
	mvprintw(row/2, (col-strlen("New Game"))/2, "New Game");
	mvprintw(row/2+1, (col-strlen("Exit"))/2, "Exit");

	getch();
	WINDOW *game_win = newwin(row, col, 0, 0);
	GameUI *game_ui = new GameUI(game_win);
	Game game(game_ui);
	game.start();
	delwin(game_win);
	delete game_ui;
}

GameUI::GameUI(WINDOW *p_win) : m_win(p_win)
{
    curs_set(0);
	nodelay(m_win, true);
	keypad(m_win, true);
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