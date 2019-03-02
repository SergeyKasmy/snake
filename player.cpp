#include "player.hpp"
#include <ncurses.h>

void Player::move()
{
    switch (facing)
    {
        case Facing::up:
            position[0].y--;
            break;
        case Facing::right:
            position[0].x++;
            break;
        case Facing::down:
            position[0].y++;
            break;
        case Facing::left:
            position[0].x--;
            break;
    }
}