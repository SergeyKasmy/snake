#pragma once

#include <vector>
#include "field.hpp"

enum class Facing { right, down, left, up, null};

class Player
{
    private:
        std::vector<point> position {{0, 1}};
        unsigned int length = 1;
    public:
        Facing facing = Facing::right;
        void move(int field_size);
        void lengthen() { length++; };
        point get(int at) { return position.at(at); }
        int get_size() { return position.size(); }
};