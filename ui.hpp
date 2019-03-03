#pragma once

#include "field.hpp"
#include "player.hpp"

class UI
{
    public:
        UI();
        ~UI();
        void display_field(Field *field, Player *player);
        Facing get_input();
};