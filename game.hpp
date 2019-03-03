#pragma once

#include "field.hpp"
#include "ui.hpp"
#include "player.hpp"

struct GameEnded : std::exception {};

class Game
{
    private:
        UI ui;
        Field *field;
        Player *player;

        void tick();
        void update();
    public:
        Game(point pField_size = {15, 25});
        ~Game();

        int start();
};