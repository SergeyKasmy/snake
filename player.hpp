#pragma once

#include <vector>
#include "field.hpp"

enum class Facing { right, down, left, up, null };

class Player
{
	private:
		std::vector<Point> m_position {{5, 5}};
		unsigned int m_length = 1;
		Facing m_facing = Facing::right;
	public:
		void move(Point p_field_size);
		void lengthen() { m_length++; };
		Point get(unsigned int p_at = 0) { return m_position.at(p_at); }

		Facing get_facing() { return m_facing; }
		void set_facing(Facing p_facing);

		// returns the amount of Points the player occupies (costly!)
		int size() { return m_position.size(); }

		// returns the player's length. size() may have not been updated to it yet
		unsigned int length() { return m_length; }
};