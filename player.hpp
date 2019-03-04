#pragma once

#include <vector>
#include "field.hpp"

enum class Facing { right, down, left, up, null};

class Player
{
	private:
		std::vector<point> m_position {{5, 5}};
		unsigned int m_length = 1;
	public:
		Facing facing = Facing::right;
		void move(point p_field_size);
		void lengthen() { m_length++; };
		point get(int p_at = 0) { return m_position.at(p_at); }
		int size() { return m_position.size(); }
};