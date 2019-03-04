#include <chrono>
#include <stdexcept>
#include "game.hpp"

void Game::tick()
{
    const static std::chrono::milliseconds TICK_DURATION(350);
    auto last_tick = std::chrono::high_resolution_clock::now();
    Facing input;

    while(true)
    {
        // true if the time of the next tick(last tick + tick duration) is in the past
        while((last_tick + TICK_DURATION) < std::chrono::high_resolution_clock::now())
        {
            update();
            last_tick += TICK_DURATION;
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
        case Object::player:
        {
            throw GameEnd();
            break;
        }
        default:
            break;
    }
    
    field->update_player(player);
    player->move(field->field_size);
    ui.display_field(field);
}


Game::Game(point pField_size)
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
    field->add_walls();
    field->place_food();

    try
    {
        tick();
    }
    catch(const GameEnd &)
    {
        return 1;
    }

    return 0;
}