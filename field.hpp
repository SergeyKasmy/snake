#pragma once

class Player;

struct Point
{
	int y;
	int x;
};

inline bool operator==(const Point& left, const Point& right)
{
	return left.y == right.y &&
		   left.x == right.x;
}

enum class Object { empty, player, food, wall };

class Field
{
	private:
		Object **m_field;
	public:
		Field(Point p_field_size);
		~Field();
		const Point m_field_size;

		Object get(Point p_point) const {    return m_field[p_point.y][p_point.x]; }
		void set(Point p_point, Object p_object) {  m_field[p_point.y][p_point.x] = p_object;    }

		void place_food();
		void add_walls();
		void update_player(Player *p_player);
};