#include <ncurses.h>
#include "ui.hpp"

UI::UI()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, true);
    keypad(stdscr, true);
}

UI::~UI()
{
    getch();
    endwin();
}

void UI::display_field(Field *field)
{
    move(0, 0);

    for(int row = 0; row < field->field_size.y; row++)
    {
        for(int column = 0; column < field->field_size.x; column++)
        {
            switch(field->get({row, column}))
            {
                case Object::empty:
                    mvaddch(row, column, ' ');
                    break;
                case Object::player:
                    mvaddch(row, column, 'p');
                    break;
                case Object::food:
                    mvaddch(row, column, 'f');
                    break;
                case Object::wall:
                    mvaddch(row, column, 'w');
                    break;
            }
        }
        
        move(row+1, 0);
    }
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