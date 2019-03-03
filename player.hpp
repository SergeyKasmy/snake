#pragma once

#include <vector>
#include "field.hpp"

enum class Facing { right, down, left, up, null};

class Player
{
    private:
        std::vector<point> position {{5, 5}};
        unsigned int length = 1;
    public:
        Facing facing = Facing::right;
        void move(point field_size);
        void lengthen() { length++; };
        point get(int at = 0) { return position.at(at); }
        int size() { return position.size(); }
};