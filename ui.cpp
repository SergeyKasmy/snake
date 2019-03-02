#include <ncurses.h>
#include "ui.hpp"

UI::UI()
{
    initscr();
    cbreak();
    noecho();
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