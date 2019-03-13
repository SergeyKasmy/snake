#pragma once

class Point;

class Settings
{
    private:
        Settings() {};
    public:
        static Point field_size;
        static bool enable_walls;
};
