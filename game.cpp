#include <chrono>
#include <cstdio>
#include "game.hpp"

void Game::tick()
{
    const static std::chrono::seconds TICK_DURATION(1);
    auto last_tick = std::chrono::high_resolution_clock::now();

    while(true)
    {
        if((last_tick + TICK_DURATION) < std::chrono::high_resolution_clock::now())
        {
            // TODO: IMPLEMENT

            last_tick += TICK_DURATION;
        }
    }
}

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