#pragma once

struct point
{
    int y;
    int x;
};

class Field
{
    private:
        int **field;
    public:
        Field(int pField_size);
        ~Field();
        const int field_size;

        // TODO: implement value checking in set()
        int get(point pPoint) const {    return field[pPoint.y][pPoint.x]; }
        void set(point pPoint, int value) {  field[pPoint.y][pPoint.x] = value;    }
};