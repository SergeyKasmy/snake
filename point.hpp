#pragma once

struct Point
{
    int y;
    int x;

    bool operator==(const Point& other)
    {
        return this->y == other.y &&
                this->x == other.x;
    }
};