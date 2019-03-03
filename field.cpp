#include <random>
#include "field.hpp"

Field::Field(point pField_size) : field_size(pField_size)
{
    field = new Object*[field_size.y];
    for(int row = 0; row < field_size.y; row++)
    {
        field[row] = new Object[field_size.x];
    }
}

Field::~Field()
{
    for(int row = 0; row < field_size.y; row++) delete [] field[row];
    delete [] field;
}

void Field::place_food()
{
    bool occupied = true;
    while(occupied)
    {  
        // pseudo-random number generator
        static std::mt19937 rng;
        // generate a seed from a random device in the system
        rng.seed(std::random_device()());
        // make a class to distribute the random numbers
        static std::uniform_int_distribution<std::mt19937::result_type> disty(0, field_size.y - 1);
        static std::uniform_int_distribution<std::mt19937::result_type> distx(0, field_size.x - 1);

        point new_food = {(int) disty(rng), (int) distx(rng)};
        if(field[new_food.y][new_food.x] == Object::empty)
        {
            field[new_food.y][new_food.x] = Object::food;
            occupied = false;
        }
    }
}

void Field::add_walls()
{
    for(int y = 0; y < field_size.y; y++)
    {
        field[y][0] = Object::wall;
        field[y][field_size.x - 1] = Object::wall;
    }

    for(int x = 0; x < field_size.x; x++)
    {
        field[0][x] = Object::wall;
        field[field_size.y - 1][x] = Object::wall;
    }
}