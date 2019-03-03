#include <ncurses.h>
#include "ui.hpp"

UI::UI()
{
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, true);
    keypad(stdscr, true);
}

UI::~UI()
{
    getch();
    endwin();
}

void UI::display_field(Field *field, Player *player)
{
    move(0, 0);

    for(int row = 0; row < field->field_size; row++)
    {
        for(int column = 0; column < field->field_size; column++)
        {
            printw("%d", field->get({row, column}));
        }
        
        move(row+1, 0);
    }
    
    mvaddch(player->get().y, player->get().x, '2');
    refresh();
}

Facing UI::get_input()
{
    int input = getch();
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