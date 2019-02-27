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

void UI::display_field(int** field, int field_size)
{
    for(int row = 0; row < field_size; row++)
    {
        for(int column = 0; column < field_size; column++)
        {
            printw("%d", field[row][column]);
        }
        
        printw("\n");
    }

    refresh();
}