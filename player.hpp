#pragma once

#include <vector>
#include "field.hpp"

enum class Facing { up, right, down, left, null};

class Player
{
    private:
        std::vector<point> position {{0, 1}};
    public:
        Facing facing = Facing::right;
        void move();

        point get() { return position[0]; }
};