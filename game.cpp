#include <chrono>
#include <stdexcept>
#include "game.hpp"

#include <ncurses.h>

void Game::tick()
{
    const static std::chrono::milliseconds TICK_DURATION(500);
    auto last_tick = std::chrono::high_resolution_clock::now();
    Facing input;

    while(true)
    {
        // true if the time of the next tick(last tick + tick duration) is in the past
        if((last_tick + TICK_DURATION) < std::chrono::high_resolution_clock::now())
        {
            update();
            last_tick = std::chrono::high_resolution_clock::now();
        }


        if((input = ui.get_input()) != Facing::null) player->facing = input;
    }
}

void Game::update()
{
    point player_head = player->get();
    switch(field->get(player_head))
    {
        case Object::food:
        {
            field->set(player_head, Object::empty);
            field->place_food();
            player->lengthen();
            break;
        }
        case Object::wall:
        {
            throw GameEnded();
            break;
        }
        default:
            break;
    }
    
    player->move(field->field_size);
    ui.display(field, player);
}


Game::Game(int pField_size)
{
    field = new Field(pField_size);
    player = new Player();
}

Game::~Game()
{
    delete field;
    delete player;
}

int Game::start()
{
    field->place_food();
    field->add_walls();

    try
    {
        tick();
    }
    catch(const GameEnded &)
    {
        return 1;
    }

    return 0;
}