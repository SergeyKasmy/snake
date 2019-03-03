#pragma once

struct point
{
    int y;
    int x;
};

inline bool operator==(const point& left, const point& right)
{
    return left.y == right.y &&
           left.x == right.x;
}

enum class Object { empty, food, wall };

class Field
{
    private:
        Object **field;
    public:
        Field(int pField_size);
        ~Field();
        const int field_size;

        // TODO: implement value checking in set()
        Object get(point pPoint) const {    return field[pPoint.y][pPoint.x]; }
        void set(point pPoint, Object object) {  field[pPoint.y][pPoint.x] = object;    }
};