#include "player.hpp"
#include <ncurses.h>

void Player::move(int field_size)
{
    switch (facing)
    {
        case Facing::right:
        {
            if(position[0].x + 1 == field_size)
                position.insert(position.begin(), { position.front().y, 0 });
            else
                position.insert(position.begin(), { position.front().y, position.front().x + 1 });
            break;
        }
        case Facing::down:
        {
            if(position[0].y + 1 == field_size)
                position.insert(position.begin(), { 0, position.front().x });
            else
                position.insert(position.begin(), { position.front().y + 1, position.front().x });
            break;
        }
        case Facing::left:
        {
            if(position[0].x - 1 == -1)
                position.insert(position.begin(), { position.front().y, field_size - 1 });
            else
                position.insert(position.begin(), { position.front().y, position.front().x - 1 });
            break;
        }
        case Facing::up:
        {
            if(position[0].y - 1 == -1)
                position.insert(position.begin(), { field_size - 1, position.front().x });
            else
                position.insert(position.begin(), { position.front().y - 1, position.front().x });
            break;
        }
    }

    if(position.size() == length) position.pop_back();
}