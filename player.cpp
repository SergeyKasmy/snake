#include "player.hpp"
#include <ncurses.h>

void Player::move()
{
    switch (facing)
    {
        case Facing::right:
        {
            position.insert(position.begin(), { position.front().y, position.front().x + 1 });
            break;
        }
        case Facing::down:
        {
            position.insert(position.begin(), { position.front().y + 1, position.front().x });
            break;
        }
        case Facing::left:
        {
            position.insert(position.begin(), { position.front().y, position.front().x - 1 });
            break;
        }
        case Facing::up:
        {
            position.insert(position.begin(), { position.front().y - 1, position.front().x });
            break;
        }
    }

    if(position.size() == length) position.pop_back();
}