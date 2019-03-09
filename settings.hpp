#pragma once

#include "point.hpp"

class Settings
{
    private:
        Settings() {};
    public:
        static Point field_size;
        static bool enable_walls;
};
