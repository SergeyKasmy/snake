#include <chrono>
#include <random>
#include "game.hpp"

#include <ncurses.h>

void Game::tick()
{
    const static std::chrono::seconds TICK_DURATION(1);
    auto last_tick = std::chrono::high_resolution_clock::now();
    Facing input;

    while(true)
    {
        // true if the time of the next tick(last tick + tick duration) is in the past
        if((last_tick + TICK_DURATION) < std::chrono::high_resolution_clock::now())
        {
            update();
            last_tick += TICK_DURATION;
        }


        if((input = ui.get_input()) != Facing::null) player->facing = input;
    }
}

void Game::update()
{
    /*
    // pseudo-random number generator
    std::mt19937 rng;
    // generate a seed from a random device in the system
    rng.seed(std::random_device()());
    // make a class to distribute the random numbers
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, field->field_size - 1);

    field->set({(int) dist(rng), (int) dist(rng)}, 1);
    */

    player->move();  
    ui.display_field(field, player);
}

Game::Game(int pField_size)
{
    field = new Field(pField_size);
    player = new Player();
    tick();
}

Game::~Game()
{
    delete field;
    delete player;
}