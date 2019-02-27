#pragma once

class Game
{
    private:
        int field_size = 15;
        int** field;
    public:
        Game();
        ~Game();
};