#include <random>
#include "field.hpp"

Field::Field(int pField_size) : field_size(pField_size)
{
    field = new Object*[field_size];
    for(int row = 0; row < field_size; row++)
    {
        field[row] = new Object[field_size];
    }
}

Field::~Field()
{
    for(int row = 0; row < field_size; row++) delete [] field[row];
    delete [] field;
}

void Field::place_food()
{
    // pseudo-random number generator
    static std::mt19937 rng;
    // generate a seed from a random device in the system
    rng.seed(std::random_device()());
    // make a class to distribute the random numbers
    static std::uniform_int_distribution<std::mt19937::result_type> dist(0, field_size - 1);

    field[(int) dist(rng)][(int) dist(rng)] = Object::food;
}

void Field::add_walls()
{
    for(int i = 0; i < field_size; i++)
    {
        field[0][i] = Object::wall;
        field[field_size - 1][i] = Object::wall;
        field[i][0] = Object::wall;
        field[i][field_size - 1] = Object::wall;
    }
}