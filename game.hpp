#pragma once

#include "field.hpp"
#include "player.hpp"
#include "ui.hpp"

struct GameEnd : std::exception {};

class Game
{
    private:
        GameUI *ui;
        Field *field;
        Player *player;

        void tick();
        void update();
    public:
        Game(GameUI *pUi, point pField_size = {15, 25});
        ~Game();

        int start();
};