#pragma once

struct point
{
    int y;
    int x;
};

class Field
{
    public:
        int field_size;
        int** field;
        Field(int pField_size);
        ~Field();
};