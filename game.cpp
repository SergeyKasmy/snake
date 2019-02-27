#include <cstdio>
#include "game.hpp"

Game::Game()
{
    field = new int*[field_size];
    for(int row = 0; row < field_size; row++)
    {
        field[row] = new int[field_size];
    }

    ui.display_field(field, field_size);
}

Game::~Game()
{
    for(int row = 0; row < field_size; row++) delete [] field[row];
    delete [] field;
}