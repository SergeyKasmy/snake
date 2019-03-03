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