#pragma once

struct point
{
    int y;
    int x;
};

enum class FieldObject { empty, food };

class Field
{
    private:
        FieldObject **field;
    public:
        Field(int pField_size);
        ~Field();
        const int field_size;

        // TODO: implement value checking in set()
        FieldObject get(point pPoint) const {    return field[pPoint.y][pPoint.x]; }
        void set(point pPoint, FieldObject object) {  field[pPoint.y][pPoint.x] = object;    }
};