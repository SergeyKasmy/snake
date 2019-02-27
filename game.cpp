#include <chrono>
#include "game.hpp"

void Game::tick()
{
    const static std::chrono::seconds TICK_DURATION(1);
    auto last_tick = std::chrono::high_resolution_clock::now();

    while(true)
    {
        if((last_tick + TICK_DURATION) < std::chrono::high_resolution_clock::now())
        {
            update();
            last_tick += TICK_DURATION;
        }
    }
}

void Game::update()
{
    ui.display_field(field, field_size);
}

Game::Game()
{
    field = new int*[field_size];
    for(int row = 0; row < field_size; row++)
    {
        field[row] = new int[field_size];
    }

    tick();
}

Game::~Game()
{
    for(int row = 0; row < field_size; row++) delete [] field[row];
    delete [] field;
}