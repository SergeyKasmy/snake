#pragma once

#include "point.hpp"

class Player;

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
		Field();
		~Field();
		const Point m_field_size;

		Object get(const Point& p_point) const {    return m_field[p_point.y][p_point.x]; }
		void set(const Point& p_point, Object p_object) {  m_field[p_point.y][p_point.x] = p_object;    }

		void place_food();
		void add_walls();
		void update_player(Player *p_player);
};