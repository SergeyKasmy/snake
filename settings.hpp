#pragma once

#include "point.h"

class Settings
{
    private:
        Settings() {};
    public:
        static Point field_size;
        static bool enable_walls;
};
