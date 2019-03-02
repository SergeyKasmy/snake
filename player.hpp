#pragma once

#include <vector>
#include "field.hpp"

enum class Facing { up, right, down, left };

class Player
{
    private:
        std::vector<point> position {{0, 1}};
    public:
        Facing facing;
        void move();
};