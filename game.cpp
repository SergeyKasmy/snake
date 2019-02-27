#include <chrono>
#include <random>
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
    // pseudo-random number generator
    std::mt19937 rng;
    // generate a seed from a random device in the system
    rng.seed(std::random_device()());
    // make a class to distribute the random numbers
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, field_size - 1);

    field[dist(rng)][dist(rng)] = 1;

    ui.display_field(field, field_size);
}

Game::Game(int pField_size)
{
    field_size = pField_size;
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