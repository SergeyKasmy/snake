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

GameUI::GameUI(WINDOW *pWin) : mWin(pWin)
{
    curs_set(0);
    nodelay(mWin, true);
    keypad(mWin, true);
}

GameUI::~GameUI()
{
    curs_set(1);
}

void GameUI::display_field(Field *field)
{
    wmove(mWin, 0, 0);

    for(int row = 0; row < field->field_size.y; row++)
    {
        for(int column = 0; column < field->field_size.x; column++)
        {
            switch(field->get({row, column}))
            {
                case Object::empty:
                    mvwaddch(mWin, row, column, ' ');
                    break;
                case Object::player:
                    mvwaddch(mWin, row, column, 'p');
                    break;
                case Object::food:
                    mvwaddch(mWin, row, column, 'f');
                    break;
                case Object::wall:
                    mvwaddch(mWin, row, column, 'w');
                    break;
            }
        }
        
        wmove(mWin, row+1, 0);
    }
    refresh();
}

Facing GameUI::get_input()
{
    int input = wgetch(mWin);
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