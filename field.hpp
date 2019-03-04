#pragma once

//#include "player.hpp"
class Player;

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

enum class Object { empty, player, food, wall };

class Field
{
	private:
		Object **m_field;
	public:
		Field(point p_field_size);
		~Field();
		const point m_field_size;

		Object get(point p_point) const {    return m_field[p_point.y][p_point.x]; }
		void set(point p_point, Object p_object) {  m_field[p_point.y][p_point.x] = p_object;    }

		void place_food();
		void add_walls();
		void update_player(Player *p_player);
};